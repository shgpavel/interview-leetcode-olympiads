#include <stdio.h>
#include <string.h>

int main() {
  size_t r, c;
  scanf("%zu%zu", &r, &c);

  char sdwd[400];
  memset(sdwd, '\0', sizeof(sdwd));

  for (size_t i = 0; i < r; ++i) {
    for (size_t j = 0; j < c;) {
      char push_c;
      scanf("%c", &push_c);

      if (push_c == '\n') continue;

      sdwd[j + i * c] = push_c;
      ++j;
    }
  }

	char min_row[20], cur_word[20];
  memset(min_row, 'z' + 1, sizeof(min_row));
  for (size_t i = 0, k = 0; i < r; ++i) {
    for (size_t j = 0; j < c; ++j) {
      if (sdwd[j + i * c] == '#' || j == c - 1) {
        if (!strcmp(min_row, cur_word)) {
          memcpy(cur_word, min_row, sizeof(cur_word));
        }
        k = 0;
        memset(cur_word, 'z' + 1, sizeof(cur_word));
      } else {
        cur_word[k] = sdwd[j + i * c];
        ++k;
      }
    }
  }

  printf("%s\n", min_row);
	
  return 0;
}
