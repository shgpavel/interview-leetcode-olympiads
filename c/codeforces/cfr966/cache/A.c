#include <stdio.h>
#include <string.h>

int main() {
	size_t test_c;
	scanf("%zu", &test_c);

	int res[10001];
	memset(res, -1, sizeof(res));
	
	for (size_t i = 0; i < test_c; ++i) {
		int a, ld, flg_a = 0, flg_nn = 0;
		scanf("%d", &a);
		res[i] = 0;
		
		for (int mlt = 1; a > 0; mlt *= 10) {
			ld = a % 10;
			ld *= mlt;
			a /= 10;

			if (flg_nn && !flg_a && ld <= 0) flg_nn = 0;
			if (ld >= 2 && flg_a == 0) flg_nn = 1;
			if (a == 10) flg_a = 1;
		}
		if (flg_a && flg_nn) res[i] = 1;
	}

	for (size_t i = 0; res[i] != -1; ++i) {
		if (res[i] == 1) printf("yes\n");
		else printf("no\n");
	}
	return 0;
}
