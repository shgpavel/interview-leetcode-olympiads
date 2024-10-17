// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2024 Pavel Shago <shgpavel@yandex.ru>
 *
 * This file is released under the GPL.
 */

#include <linux/device-mapper.h>

#include <linux/bio.h>
#include <linux/blk_types.h>
#include <linux/bvec.h>
#include <linux/gfp_types.h>
#include <linux/init.h>
#include <linux/kobject.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/sysfs.h>
#include <linux/types.h>

#define DM_MSG_PREFIX "dmp"

struct proxier {
  struct dm_dev *dev;
  sector_t start_block;
};

struct proxy_data {
  unsigned int read_calls;
  unsigned int write_calls;

  unsigned int read_bytes;
  unsigned int write_bytes;
};

static struct proxy_data proxy_info = { 0 };
static struct kobject *stats_kobj;

static ssize_t
volumes_show
(struct kobject *kobj, struct kobj_attribute *attr, char *buffer)
{
  return sysfs_emit(
      buffer,
      "read:\nreqs: %u\navg size: %u\n"
      "write:\nreqs: %u\navg size: %u\n"
      "total:\nreqs: %u\navg size: %u\n",
      proxy_info.read_calls, proxy_info.read_bytes / proxy_info.read_calls,
      proxy_info.write_calls, proxy_info.write_bytes / proxy_info.write_calls,
      (proxy_info.read_calls + proxy_info.write_calls),
      proxy_info.write_bytes + proxy_info.read_bytes
      / (proxy_info.read_calls + proxy_info.write_calls));
}
static struct kobj_attribute stats_kobj_attribute = __ATTR_RO(volumes);

static int proxy_ctr(struct dm_target *ti, unsigned int argc, char **argv)
{
  struct proxier *meta;
  int ret;

  if (argc != 1) {
    ti->error = "Invalid argument count (expected 1)";
    DMERR("dm-proxy: %s", ti->error);
    return -EINVAL;
  }

  meta = kmalloc(sizeof(*meta), GFP_KERNEL);
  if (!meta) {
    ti->error = "Failed to allocate memory (for meta info)";
    DMERR("dm-proxy: %s", ti->error);
    return -ENOMEM;
  }

  ret = dm_get_device(ti, argv[0], dm_table_get_mode(ti->table), &meta->dev);
  if (ret) {
    ti->error = "Failed to get the device";
    DMERR("dm-proxy: %s", ti->error);
    kfree(meta);
    return ret;
  }

  stats_kobj = kobject_create_and_add("stat", &THIS_MODULE->mkobj.kobj);
  if (!stats_kobj) {
    ti->error = "Failed to create statistical kobj";
    DMERR("dm-proxy: %s", ti->error);
    return -ENOMEM;
  }

  ret = sysfs_create_file(stats_kobj, &stats_kobj_attribute.attr);
  if (ret) {
    ti->error = "Failed to create sysfs file";
    DMERR("dm-proxy: %s", ti->error);
    kfree(meta);
    kobject_put(stats_kobj);
    return ret;
  }

  ti->private = meta;

  return 0;
}

static void proxy_dtr(struct dm_target *ti)
{
  struct proxier *meta = ti->private;

  dm_put_device(ti, meta->dev);
  kobject_put(stats_kobj);
  kfree(meta);
}

static int proxy_map(struct dm_target *ti, struct bio *bio)
{
  struct proxier *meta = ti->private;
  unsigned int block_size = bio->bi_iter.bi_size;

  if (bio_op(bio) == REQ_OP_READ) {
    proxy_info.read_bytes += block_size;
    proxy_info.read_calls++;
  } else if (bio_op (bio) == REQ_OP_WRITE) {
    proxy_info.write_bytes += block_size;
    proxy_info.write_calls++;
  }

  bio_set_dev(bio, meta->dev->bdev);
  bio->bi_iter.bi_sector += meta->start_block;

  submit_bio(bio);
  return DM_MAPIO_SUBMITTED;
}

static struct target_type proxy_target = {
  .name = "dmp",
  .version = { 1, 0, 0 },
  .module = THIS_MODULE,
  .dtr = proxy_dtr,
  .ctr = proxy_ctr,
  .map = proxy_map,
};
module_dm(proxy);

MODULE_AUTHOR("Pavel Shago <shgpavel@yandex.ru>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(DM_NAME " target to collect disks statistics");
