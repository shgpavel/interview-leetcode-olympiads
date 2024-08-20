#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool isMatch(char *s, char *p) {
  int skip = 0, skip_el = -1;
  for (size_t i = 0, j = 0; i < strlen(s) && j < strlen(p); ++i) {
    if (p[j] == '.') {
      ++j;
      continue;
    } else if (p[j] == '*') {
      skip = 1;
      if (j != 0 && p[j - 1] != '*') {
        skip_el = p[j - 1];
      }
			++j;
			continue;
		}

    if (s[i] != p[j] && !skip) {
      if ((j + 1 < strlen(p)) && p[j + 1] == '*') {
				++j;
				for (; j < strlen(p) && p[j] == '*'; ) {
					++j;
				}
				continue;
			}
      return false;
    }

    if (skip && s[i] == p[j]) {
      skip = 0;
			skip_el = -1;
			//printf("GAY: %c %c\n", s[i], p[i]);
    }
		
    if (skip && s[i] != skip_el && skip_el != -1) {
			//printf("NO SYNC: %c %c\n", s[i], p[j]);
			return false;
    }
    ++j;
  }
  return true;
}

/*
int main() {
	char s[100], p[100];
	scanf("%s%s", s, p);
	printf("%d\n", isMatch(s, p));
}
*/
