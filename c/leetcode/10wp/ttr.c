#define _GNU_SOURCE
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sol.h"
#define n 100

int main() {
  FILE *f = fopen("test", "r");
  if (!f) exit(1);
  char *input = NULL;
  size_t len;

  char s[n][100] = {0};
  char p[n][100] = {0};

  int result[n];
  size_t j = 0, k = 0, h = 0;

  do {
    int64_t err = getline(&input, &len, f);
    if (err < 0) break;

    char *data, *saveptr;
    data = strtok_r(input, " ", &saveptr);
    for (size_t i = 1; data != NULL; ++i) {
      if (i % 2 == 0) {
        strcpy(p[k], data);
        ++k;
      } else if (i % 3 == 0) {
        result[h] = atoi(data);
        ++h;
      } else {
        strcpy(s[j], data);
        ++j;
      }

      data = strtok_r(NULL, " ", &saveptr);
    }
  } while (!strchr(input, EOF));

  for (size_t i = 0; i < h; ++i) {
    printf("%zu  %-*s%-*s\t%d", i, 20, s[i], 20, p[i], result[i]);
    int l = isMatch(s[i], p[i]);
    printf("  %d\t", l);

    if (l == result[i]) {
      printf("OK\n");
    } else {
      printf("FAILED\n");
    }
  }

  free(input);
  fclose(f);
  return 0;
}
