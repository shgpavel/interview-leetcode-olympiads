#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *convert(char *s, int numRows) {
  if (numRows == 1) {
    /*
            If I allocate here "s[0]\0" str
            leetcode asan gives and error lol
    */
    return s;
  }

  char *out = (char *)malloc(strlen(s) + 1);
  char *inC = (char *)malloc(strlen(s) + 1);
  char *bet = (char *)malloc(strlen(s) + 1);

  memset(inC, '\0', strlen(s) + 1);
  memset(bet, '\0', strlen(s) + 1);
  memset(out, '\0', strlen(s) + 1);

  size_t numCols_ =
      (size_t)ceil((double)strlen(s) / (2 * ((double)numRows - 1)));
  size_t numRows_ = (size_t)numRows;
  size_t toNext = 2 * (numRows_ - 1);

  for (size_t i = 0; i < numRows_; ++i) {
    for (size_t j = 0; j < numCols_; ++j) {
      size_t inCol = i + j * toNext;
      size_t between = (j + 1) * toNext - i - 1;

      if (inCol < strlen(s)) {
        inC[strlen(inC)] = s[inCol];
      }
      if (between < strlen(s)) {
        bet[strlen(bet)] = s[between];
      }
    }
  }

  size_t flg = 0, nl_flg;
  for (size_t i = 0, j = 0, k = 0; i <= strlen(s); ++i) {
    nl_flg = (size_t)((j + 1) % numCols_ == 0);
    if (i < numCols_) {
      out[i] = inC[i];
      j = i + 1;
    } else {
      if (flg == 0) {
        out[i] = inC[j];
        if (!nl_flg && i < strlen(s) - numCols_) flg = 1;
        ++j;
      } else {
        if (bet[k] != '\0') out[i] = bet[k];
        ++k;
        flg = 0;
      }
    }
  }

  /* bad n quick fix */
  size_t bet_s = strlen(s) - strlen(inC);
  if (numCols_ == 1 && bet_s != 0) {
    out[0] = inC[0];
    char *s_copy = (char *)malloc(sizeof(s) * 2);
    memcpy(s_copy, s, strlen(s));
    memset(s_copy + strlen(s), '\0', sizeof(s_copy) - strlen(s));
    size_t prev = 0;
    for (size_t i = 1, k = 1, j = 0; i < strlen(s); ++i) {
      if (prev != 1) {
        out[i] = inC[k];
        // printf("inC[k] = %c, i = %zu\n", inC[k], i);
        ++k;
        prev = 1;
      } else if (prev == 1) {
        if (bet_s != 0 && s_copy[2 * (numRows_ - 1) - j - 1] != '\0') {
          out[i] = s_copy[2 * (numRows_ - 1) - j - 1];
          // printf("s[j] = %c, i = %zu\n", s[2 * (numRows_ - 1) - j - 1], i);
          ++j;
        } else {
          ++j;
          --i;
        }
        prev = 0;
      }
    }
    free(s_copy);
  }

  //printf("%s\n", inC);
  //printf("%s\n", bet);
  //printf("%s\n", out);

  free(inC);
  free(bet);
  return out;
}

int main() {
  char *test_case_1 = "PAYPALISHIRING";
  char *test_case_3 = "A";
  char *test_case_4 = "ABCD";
  char *test_case_5 = "ABCDEFHK";
  char *test_case_7 = "ABCDE";
  char *test_case_8 = "ABCDEF";

  printf("  test_1: \n");
  char *test_1 = convert(test_case_1, 3);
  if (!strcmp(test_1, "PAHNAPLSIIGYIR")) {
    printf("TEST -- OK\n");
  } else
    printf("TEST -- FAILED\n");

  printf("  test_2: \n");
  char *test_2 = convert(test_case_1, 4);
  if (!strcmp(test_2, "PINALSIGYAHRPI")) {
    printf("TEST -- OK\n");
  } else
    printf("TEST -- FAILED\n");

  printf("  test_3: \n");
  char *test_3 = convert(test_case_3, 1);
  if (!strcmp(test_3, "A")) {
    printf("TEST -- OK\n");
  } else
    printf("TEST -- FAILED\n");

  printf("  test_4: \n");
  char *test_4 = convert(test_case_4, 3);
  if (!strcmp(test_4, "ABDC")) {
    printf("TEST -- OK\n");
  } else
    printf("TEST -- FAILED\n");

  printf("  test_5: \n");
  char *test_5 = convert(test_case_5, 5);
  if (!strcmp(test_5, "ABKCHDFE")) {
    printf("TEST -- OK\n");
  } else
    printf("TEST -- FAILED\n");

  printf("  test_6: \n");
  char *test_6 = convert(test_case_4, 4);
  if (!strcmp(test_6, "ABCD")) {
    printf("TEST -- OK\n");
  } else
    printf("TEST -- FAILED\n");

  printf("  test_7: \n");
  char *test_7 = convert(test_case_7, 4);
  if (!strcmp(test_7, "ABCED")) {
    printf("TEST -- OK\n");
  } else
    printf("TEST -- FAILED\n");

  printf("  test_8: \n");
  char *test_8 = convert(test_case_8, 5);
  if (!strcmp(test_8, "ABCDFE")) {
    printf("TEST -- OK\n");
  } else
    printf("TEST -- FAILED\n");

  free(test_1);
  free(test_2);
  free(test_4);
  free(test_5);
  free(test_6);
  free(test_8);
}
