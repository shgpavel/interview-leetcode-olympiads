#include <stdio.h>
#include <string.h>

int main() {
	size_t test_c;
	scanf("%zu", &test_c);

	int res[100];
	memset(res, -1, sizeof(res));
	
	for (size_t i = 0; i < test_c; ++i) {
	}

	for (size_t i = 0; res[i] != -1; ++i) {
		printf("%d\n", res[i]);
	}
	return 0;
}
