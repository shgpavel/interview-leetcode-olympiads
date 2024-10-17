#include <stdio.h>
#include <string.h>

int main() {
  size_t r, c;
  scanf("%zu%zu", &r, &c);

  char scanwd[400];
  memset(scanwd, '\0', sizeof(scanwd));

  for (size_t i = 0; i < r; ++i) {
    for (size_t j = 0; j < c;) {
      char c_push;
      scanf("%c", &c_push);

      if (c_push == '\n') continue;

      scanwd[i * c + j] = c_push;
      ++j;
    }
  }
	
	char min_row[32], cur_word[32];
  memset(min_row, 'z' + 1, sizeof(min_row) - 2);
	min_row[sizeof(min_row) - 1] = '\0';
  for (size_t i = 0, k = 0; i < r; ++i) {
    for (size_t j = 0; j < c; ++j) {
			cur_word[k] = scanwd[i * c + j];
			++k;
			printf("%s\n", cur_word);

      if (scanwd[i * c + j] == '#' || j == c - 1) {

				if (
						strcmp(min_row, cur_word) > 0
						&& strlen(cur_word) > 1
						&& strstr(cur_word, "#") == NULL
						) {
					memcpy(min_row, cur_word, sizeof(cur_word));
				}
				k = 0;
        memset(cur_word, '\0', sizeof(cur_word));
      }
    }
  }
	

  return 0;
}


/*
	for (size_t i = 0; i < r; ++i) {
		for (size_t j = 0; j < c; ++j) {
			printf("%c", sdwd[i * c + j]);
		}
		printf("\n");
	}
*/
