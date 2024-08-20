#include <stdio.h>
#include <string.h>

int main() {
	size_t test_c;
	scanf("%zu", &test_c);

	int res[10001];
	memset(res, -1, sizeof(res));

	for (size_t i = 0; i < test_c; ++i) {
		size_t n, s, m;
		scanf("%zu%zu%zu", &n, &s, &m);
		int t_len[n * 2];
		for (size_t j = 0; j < 2 * n; j += 2) {
			scanf("%d%d", &t_len[j], &t_len[j + 1]);
		}
	
		for (size_t j = 0, k = 0; j < 2 * n && k <= m; j += 2) {
			//printf("%d %d -- %d %d\n", t_len[j], t_len[j+1], (int)k, t_len[j] - (int)k);
			if (t_len[j] - (int)k >= (int)s
					|| (int)m - t_len[2 * n - 1] >= (int)s) {
				res[i] = 1;
				break;
			}
			k = (size_t)t_len[j+1];
		}
		if (res[i] == -1) res[i] = 0;
	}

	for (size_t i = 0; res[i] != -1; ++i) {
		if (res[i] == 1) printf("yes\n");
		else printf("no\n");
	}
	return 0;
}
