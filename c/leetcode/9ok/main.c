#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

bool isPalindrome(int x) {
  if (x < 0) return false;
  int ld = 0, ldd = 0, x_copy = x;
  int64_t reversed = 0;
  for (; x > 0;) {
    ld = x % 10;
    x /= 10;
    reversed = reversed * 10 + ld;
  }

  for (; reversed > 0;) {
    ld = x_copy % 10;
    x_copy /= 10;

    ldd = (int)(reversed % 10);
    reversed /= 10;
    // printf("ld = %d, ldd = %d\n %d %ld\n", ld, ldd, x_copy, reversed);

    if (ld != ldd) return false;
  }
  return true;
}

int main() {
  int a;
  scanf("%d", &a);
  printf("%d\n", isPalindrome(a));
}
