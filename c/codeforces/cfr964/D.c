#include <stdio.h>
#include <string.h>

int main() {
	size_t test_c;
	scanf("%zu", &test_c);

	int res[10001];
	memset(res, -1, sizeof(res));
	
	for (size_t i = 0; i < test_c; ++i) {
		int a, fd, sd;
		scanf("%d", &a);
		fd = a / 10;
		sd = a % 10;
		res[i] = fd+sd;
	}

	for (size_t i = 0; res[i] != -1; ++i) {
		printf("%d\n", res[i]);
	}
 return 0;
}
