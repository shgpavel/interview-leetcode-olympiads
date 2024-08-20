#include <stdio.h>
#include <string.h>

int main() {
	size_t test_c;
	scanf("%zu", &test_c);

	int res[10001];
	memset(res, -1, sizeof(res));
	
	for (size_t i = 0; i < test_c; ++i) {
		size_t seats, curr, v_flg = 1, to_discard = 0, dummy;
		scanf("%zu", &seats);
		size_t a[seats + 2];
		memset(a, 0, (seats + 2) * sizeof(size_t));
		
		for (size_t j = 0; j < seats; ++j) {
			scanf("%zu", &curr);
			if (((a[curr - 1] == 1)
					 || (a[curr + 1] == 1))
					&& (j != 0)) {
				v_flg = 1;
			} else if (j != 0) {
				v_flg = 0;
				to_discard = j + 1;
				break;
			}
			a[curr] = 1;
		}
				
		if (!v_flg) {
			res[i] = 0;
			for (size_t j = to_discard; j < seats; ++j) {
				scanf("%zu", &dummy);
			}
		}
		else res[i] = 1;
	}

	for (size_t i = 0; res[i] != -1; ++i) {
		if (res[i]) printf("yes\n");
		else printf("no\n");
	}
	return 0;
}
