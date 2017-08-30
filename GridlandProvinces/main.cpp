#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;

#define DEBUG		0

#define MAX			606
#define SEED		131
#define MOD			2078526727	

long long _pow[2 * MAX];

void init() {
	long long tmp = 1;
	_pow[0] = 1;
	for (int i = 1; i < 2 * MAX; i ++) {
		tmp *= SEED;
		tmp = tmp % MOD;
		_pow[i] = tmp;
	}
}

int solve(int n, char *s1, char *s2) {
	int ret = 0;
	vector<long long> str_hash;
	long long ltr[2][MAX];
	long long rtl[2][MAX];

	// init
	// row 0, from left to right
	{
		long long hash = 0;
		for (int i = n - 1; i >= 0; i --) {
			hash = (s1[i] * _pow[2 * (n - 1 - i) + 1] + hash * SEED + s2[i]) % MOD;
			ltr[0][i] = hash;
		}
	}

	// row 1, from left to right
	{
		long long hash = 0;
		for (int i = n - 1; i >= 0; i --) {
			hash = (s2[i] * _pow[2 * (n - 1 - i) + 1] + hash * SEED + s1[i]) % MOD;
			ltr[1][i] = hash;
		}
	}

	// row 0, from right to left
	{
		long long hash = 0;
		for (int i = 0; i < n; i ++) {
			hash = (s1[i] * _pow[2 * i + 1] + hash * SEED + s2[i]) % MOD;
			rtl[0][i] = hash;
		}
	}

	// row 1, from right to left
	{
		long long hash = 0;
		for (int i = 0; i < n; i ++) {
			hash = (s2[i] * _pow[2 * i + 1] + hash * SEED + s1[i]) % MOD;
			rtl[1][i] = hash;
		}
	}

	// solve
	// row 0
	// left to right
	{
		long long sum;
		for (int i = 0; i < n; i ++) {
			int start = 1;
			sum = ltr[0][i] * _pow[2 * i] % MOD;
			if (0 == i) {
				str_hash.push_back(sum);
			}
			else {
				for (int j = i - 1; j >= 0; j --) {
					if (1 == start) {
						sum += (s2[j] * SEED + s1[j]) * _pow[2 * j] % MOD;
						if (0 == j) {
							str_hash.push_back(sum % MOD);
						}
						else {
							str_hash.push_back((sum + rtl[0][j - 1]) % MOD);
						}
					}
					else {
						sum += (s1[j] * SEED + s2[j]) * _pow[2 * j] % MOD;
						if (0 == j) {
							str_hash.push_back(sum % MOD);
						}
						else {
							str_hash.push_back((sum + rtl[1][j - 1]) % MOD);
						}
					}

					start = 1 - start;
				}
			}
		}	
	}

	// right to left
	{
		long long sum;
		for (int i = n - 1; i >= 0; i --) {
			int start = 1;
			sum = rtl[0][i] * _pow[2 * (n - 1 - i)] % MOD;
			if (n - 1 == i) {
				str_hash.push_back(sum);
			}
			else {
				for (int j = i + 1; j < n; j ++) {
					if (1 == start) {
						sum += (s2[j] * SEED + s1[j]) * _pow[2 * (n - 1 - j)] % MOD;
						if (n - 1 == j) {
							str_hash.push_back(sum % MOD);
						}
						else {
							str_hash.push_back((sum + ltr[0][j + 1]) % MOD);
						}
					}
					else {
						sum += (s1[j] * SEED + s2[j]) * _pow[2 * (n - 1 - j)] % MOD;
						if (n - 1 == j) {
							str_hash.push_back(sum % MOD);
						}
						else {
							str_hash.push_back((sum + ltr[1][j + 1]) % MOD);
						}

					}

					start = 1 - start;
				}
			}
		}
	}

	// row 1
	// left to right
	{
		long long sum;
		for (int i = 0; i < n; i ++) {
			int start = 0;
			sum = ltr[1][i] * _pow[2 * i] % MOD;
			if (0 == i) {
				str_hash.push_back(sum);
			}
			else {
				for (int j = i - 1; j >= 0; j --) {
					if (0 == start) {
						sum += (s1[j] * SEED + s2[j]) * _pow[2 * j] % MOD;
						if (0 == j) {
							str_hash.push_back(sum % MOD);
						}
						else {
							str_hash.push_back((sum + rtl[1][j - 1]) % MOD);
						}
					}
					else {
						sum += (s2[j] * SEED + s1[j]) * _pow[2 * j] % MOD;
						if (0 == j) {
							str_hash.push_back(sum % MOD);
						}
						else {
							str_hash.push_back((sum + rtl[0][j - 1]) % MOD);
						}

					}

					start = 1 - start;
				}
			}
		}
	}

	// right to left
	{
		long long sum;
		for (int i = n - 1; i >= 0; i --) {
			int start = 0;
			sum = rtl[1][i] * _pow[2 * (n - 1 - i)] % MOD;
			if (n - 1 == i) {
				str_hash.push_back(sum);
			}
			else {
				for (int j = i + 1; j < n; j ++) {
					if (0 == start) {
						sum += (s1[j] * SEED + s2[j]) * _pow[2 * (n - 1 - j)] % MOD;
						if (n - 1 == j) {
							str_hash.push_back(sum % MOD);
						}
						else {
							str_hash.push_back((sum + ltr[1][j + 1]) % MOD);
						}
					}
					else {
						sum += (s2[j] * SEED + s1[j]) * _pow[2 * (n - 1 - j)] % MOD;
						if (n - 1 == j) {
							str_hash.push_back(sum % MOD);
						}
						else {
							str_hash.push_back((sum + ltr[0][j + 1]) % MOD);
						}
					}

					start = 1 - start;
				}
			}
		}
	}

	sort(str_hash.begin(), str_hash.end());
    str_hash.erase(unique(str_hash.begin(), str_hash.end()), str_hash.end());
	ret = str_hash.size();

	return ret;
}

int main() {
	int p;
	int output[15];

#if DEBUG
	FILE * fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &p);
	FILE * fp_out = fopen("output.txt", "w");
#else
	scanf("%d", &p);
#endif

	init();

	char s1[601];
	char s2[601];
	for (size_t i = 0; i < p; i++) {
		int n;
		memset(s1, 0, sizeof(s1));
		memset(s2, 0, sizeof(s1));
#if DEBUG
		fscanf(fp, "%d", &n);
		fscanf(fp, "%s", s1);
		fscanf(fp, "%s", s2);
#else
		scanf("%d", &n);
		scanf("%s", s1);
		scanf("%s", s2);
#endif

		output[i] = solve(n, s1, s2);
	}

	for (int i = 0; i < p; i ++) {
		printf("%d\n", output[i]);
	}

#if DEBUG
	fclose(fp);
	fclose(fp_out);
#endif

	system("pause");

	return 0;
}
