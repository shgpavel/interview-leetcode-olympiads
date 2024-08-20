#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

char *ints[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

int in_ints(char a) {
  for (size_t i = 0; i < sizeof(ints) / sizeof(ints[0]); ++i) {
    if (a == *ints[i]) return 1;
  }
  return 0;
}

int64_t convert_toi(char a) {
  if (in_ints(a)) return (a - '0');
  return -1;
}

int myAtoi(char *s) {
  int str_started = 0, non_zero = 0, already_signed = 0;
  int64_t pre_res = 0;
  char s_res[220];
  memset(s_res, '\0', sizeof(s_res));

  for (size_t i = 0, j = 0; i < strlen(s); ++i) {
    if (in_ints(s[i]) && !str_started) str_started = 1;
    if (in_ints(s[i]) && s[i] != '0') non_zero = 1;

    if (!str_started) {
      if ((s[i] != ' ' && s[i] != '+' && s[i] != '-') || already_signed > 0) {
        break;
      }

      if (s[i] == '+') {
        already_signed = 1;
      } else if (s[i] == '-') {
        already_signed = 2;
      }
    }

    if (str_started && !in_ints(s[i])) {
      if (!non_zero) str_started = 0;
      break;
    } else if (str_started && non_zero) {
      s_res[j] = s[i];
      ++j;
    }
  }

  int64_t k = 1, w = 0;
  for (size_t i = strlen(s_res); i > 0;) {
    --i;
    if ((w = convert_toi(s_res[i])) > 0) {
      pre_res += w * k;
    }
    if (already_signed == 2 && i == 0) pre_res -= pre_res * 2;

    if ((pre_res >= INT_MAX || pre_res <= INT_MIN) && already_signed == 2) {
      return INT_MIN;
    } else if (pre_res >= INT_MAX) {
      return INT_MAX;
    } else if (k > INT64_MAX / 10 && already_signed == 2) {
      return INT_MIN;
    } else if (k > INT64_MAX / 10) {
      return INT_MAX;
    } else {
      k *= 10;
    }
  }

  if (str_started == 0)
    return 0;
  else
    return (int)pre_res;
}

int main() {
  char a[1000];
  scanf("%s", a);
  printf("%d\n", myAtoi(a));
  return 0;
}
