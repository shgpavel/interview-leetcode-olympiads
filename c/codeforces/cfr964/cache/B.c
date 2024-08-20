#include <stdio.h>
#include <string.h>

int f(int a, int b) {
	if (a > b) return 1;
	if (a == b) return 0;
	if (a < b) return -1;
}

int main() {
	size_t test_c;
	scanf("%zu", &test_c);

	int res[10001];
	memset(res, -1, sizeof(res));
	
	for (size_t i = 0; i < test_c; ++i) {
		int suneet, suneet_1, slavik, slavik_1;
		scanf("%d%d%d%d", &suneet, &suneet_1, &slavik, &slavik_1);
		res[i] = 0;
		
		if (f(suneet, slavik)
				+ f(suneet_1, slavik_1) > 0) {	
			res[i] += 1;
		}
		
		if (f(suneet, slavik_1)
			  + f(suneet_1, slavik) > 0) {
			res[i] += 1;
		}
		
		if (f(suneet_1, slavik)
				+ f(suneet, slavik_1) > 0) {
			res[i] += 1;
		}

		if (f(suneet_1, slavik_1)
				+ f(suneet, slavik) > 0) {
			res[i] += 1;
		}
	}

	for (size_t i = 0; res[i] != -1; ++i) {
		printf("%d\n", res[i]);
	}
	
	return 0;
}
