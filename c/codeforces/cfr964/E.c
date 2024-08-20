#include <stdio.h>
#include <string.h>

int main() {
	size_t test_c;
	scanf("%zu", &test_c);

	int res[10000];
	memset(res, -1, sizeof(res));
	
	for (size_t i = 0; i < test_c; ++i) {
		int l, r;
		scanf("%d%d", &l, &r);
		int some[r - l + 1];
		for (int j = l, k = 0; j <= r; ++j, ++k) {
			some[k] = j;
		}
		for (int k = 0; k < r - l + 1; ++k) {
			
		}
	}

	for (size_t i = 0; res[i] != -1; ++i) {
		printf("%d\n", res[i]);
	}
	return 0;
}
