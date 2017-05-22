#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

#define DEBUG	0

struct ballInBall {
		int box_index;
		int earn;
		int origin_earn;
};

void quick_sort(struct ballInBall s[], int l, int r)
{
		if (l < r)
		{
				int i = l, j = r;
				struct ballInBall x = s[l];
				while (i < j)
				{
						while(i < j && s[j].earn <= x.earn)
								j--;
						if(i < j)
								s[i++] = s[j];

						while(i < j && s[i].earn > x.earn)
								i++;
						if(i < j)
								s[j--] = s[i];
				}
				s[i] = x;
				quick_sort(s, l, i - 1);
				quick_sort(s, i + 1, r);
		}
}

int main() {
		int n;
		int m;
		scanf("%d %d", &n, &m);
		int *A = malloc(sizeof(int) * n);
		for(int A_i = 0; A_i < n; A_i++){
				scanf("%d",&A[A_i]);
		}
		int *C = malloc(sizeof(int) * m);
		for(int C_i = 0; C_i < m; C_i++){
				scanf("%d",&C[C_i]);
		}

		int * curr = malloc(sizeof(int) * n);
		struct ballInBall b[n][m];
		for(int B_i = 0; B_i < n; B_i++){
				curr[B_i] = 0;
				for(int B_j = 0; B_j < m; B_j++){
						int earn;
						scanf("%d",&earn);

						b[B_i][B_j].box_index = B_j;
						b[B_i][B_j].origin_earn = earn;
						if (0 == C[B_j]) {
								b[B_i][B_j].earn = earn - 1;
						}
						else {
								b[B_i][B_j].earn = earn;
						}
				}

				// sort desc
				quick_sort(b[B_i], 0, m - 1);
		}
#if DEBUG
for (int i = 0; i < n; i++) {
	printf("the %d color is :\n", i);
	for (int j = 0; j < m; j++) {
		printf("  put in %d box earn %d\n", b[i][j].box_index, b[i][j].earn);
	}
}
#endif
		int result = 0;

		while (true) {
				int max = 0;
				int max_box = 0;
				int max_color = 0;
				for (size_t i = 0; i < n; i++) {
						if (A[i] && curr[i] < m && b[i][curr[i]].earn > max) {
								max = b[i][curr[i]].earn;
								max_box = b[i][curr[i]].box_index;
								max_color = i;
						}
				}

				if (max > 0) {
						result += max;
#if DEBUG
						printf("put %d color into box %d, result is %d\n", max_color, max_box, result);
#endif

						curr[max_color] ++;
						A[max_color] --;
						C[max_box] --;

						if (0 >= C[max_box]) {
								// recalc, sort
								for (int i = 0; i < n; i++) {
										if (A[i] && curr[i] < m) {
												size_t j = 0;
												for (j = curr[i]; j < m && b[i][j].earn > 0; j++) {
														if (b[i][j].box_index == max_box) {
																break;
														}
												}

												if (j < m && b[i][j].earn > 0) {
														// discard earn <= 0
														if (0 == C[max_box]) {
																b[i][j].earn = b[i][j].origin_earn - 1;
														}
														else {
																b[i][j].earn = b[i][j].origin_earn + (abs(C[max_box]) * abs(C[max_box])) - (abs(C[max_box] - 1) * abs(C[max_box] - 1));
														}

														quick_sort(b[i], j, m - 1);

														#if DEBUG
															printf("the %d color is :\n", i);
															for (int j = curr[i]; j < m; j++) {
																printf("  put in %d box earn %d\n", b[i][j].box_index, b[i][j].earn);
															}
														#endif
												}
										}
								}
						}
				}
				else {
						break;
				}
		}

		printf("%d\n", result);

		return 0;
}
