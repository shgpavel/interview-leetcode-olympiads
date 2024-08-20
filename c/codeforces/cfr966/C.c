#include <stdio.h>
#include <string.h>

#define printS printf("yes\n")
#define printF printf("no\n")

int main() {
	size_t test_c;
	scanf("%zu", &test_c);

	for (size_t i = 0; i < test_c; ++i) {
		size_t n, m;
		char s[20001];
		
		scanf("%zu", n);
		int a[n];
		for (size_t j = 0; j < n; ++j) {
			scanf("%zu", &a[j]);
		}
		scanf("%zu", m);
		for (size_t j = 0; j < m; ++j) {
			memset(s, '\0', sizeof(s));
			scanf("%s", s);
			if (strlen(s) != n) {
				printF;
				break;
			}

			int freqS[256];
			int freqSIndex[];
			memset(freqS, 0, sizeof(freqS));
			for (size_t k = 0; s[k] != '\0'; ++k) {
				freqS[(unsigned char)str[k]]++;
			}

			for (size_t k = 0; k < 256; ++k) {
				if (freqS[k] > 1) {
					
				}
			}
			
		}
	}

	return 0;
}
