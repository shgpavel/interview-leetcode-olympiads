double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int nums[nums1Size + nums2Size];

    int i = 0, j = 0, k = 0;
    while (i < nums1Size && j < nums2Size) {
        if (nums1[i] < nums2[j]) {
            nums[k++] = nums1[i++];
        } else {
            nums[k++] = nums2[j++];
        }
    }

    while (i < nums1Size) {
        nums[k++] = nums1[i++];
    }

    while (j < nums2Size) {
        nums[k++] = nums2[j++];
    }

    if ((nums1Size + nums2Size) % 2 != 0) {
        return nums[(nums1Size + nums2Size - 1) / 2];
    }
    return (nums[(nums1Size + nums2Size) / 2] + nums[((nums1Size + nums2Size) / 2) - 1]) / 2.0;
}
