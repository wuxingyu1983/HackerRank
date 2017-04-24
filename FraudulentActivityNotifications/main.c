#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
	int n, d;
	scanf("%d %d", &n, &d);

	int num[201];
	memset(num, 0, sizeof(int) * 201);

	int type;
	int half;
	if (0 == d % 2) {
		// two nums
		type = 2;
		half = d / 2 - 1;
	}
	else {
		// only one num
		type = 1;
		half = d / 2;
	}

	int cnt = 0;
	int * e = malloc(sizeof(int) * n);

	for (size_t i = 0; i < n; i ++) {
		scanf("%d", &e[i]);

		if (i >= d) {
			int remain = half;
			int j = 0;
			int median = 0;
			while (remain > 0 && j <= 200) {
				if (num[j]) {
					remain -= num[j];
				}
				j ++;
			}
			if (0 == remain) {
				if (1 == type) {
					for (j; j <= 200; j++) {
						if (num[j]) {
							median = j * 2;
							break;
						}
					}
				}
				else {
					while (remain > -2 && j <= 200) {
						if (num[j]) {
							remain -= num[j];
							if (-1 == remain) {
								median += j;
							}
							else {
								if (0 == median) {
									median = 2 * j;
								}
								else {
									median += j;
								}
								break;
							}
						}

						j ++;
					}
				}
			}
			else if (-1 == remain) {
				if (1 == type) {
					median = 2 * (j - 1);
				}
				else {
					median = j - 1;

					for (j; j <= 200; j++) {
						if (num[j]) {
							median += j;
							break;
						}
					}
				}
			}
			else {
				median = 2 * (j - 1);
			}

			if (e[i] >= median) {
				cnt ++;
			}

			num[e[i - d]] --;
		}

		num[e[i]] ++;
	}

	printf("%d\n", cnt);

	free(e);

	return 0;
}
