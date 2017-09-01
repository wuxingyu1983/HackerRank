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
#define SEED1		131
#define SEED2		131131	
#define MOD1		1000000009	
#define MOD2		1000000007

long long _pow1[2 * MAX];
long long _pow2[2 * MAX];

void init(long long *_pow, long long seed, long long mod) {
	long long tmp = 1;
	_pow[0] = 1;
	for (int i = 1; i < 2 * MAX; i ++) {
		tmp *= seed;
		tmp = tmp % mod;
		_pow[i] = tmp;
	}
}

void solve_priv(int n, char *s1, char *s2, long long seed, long long mod, vector<long long>& str_hash, long long *_pow) {
	long long ltr[2][MAX];
	long long rtl[2][MAX];

	// init
	// row 0, from left to right
	{
		long long hash = 0;
		for (int i = n - 1; i >= 0; i --) {
			hash = ((long long)s1[i] * _pow[2 * (n - 1 - i) + 1] + hash * seed + s2[i]) % mod;
			ltr[0][i] = hash;
		}
	}

	// row 1, from left to right
	{
		long long hash = 0;
		for (int i = n - 1; i >= 0; i --) {
			hash = ((long long)s2[i] * _pow[2 * (n - 1 - i) + 1] + hash * seed + s1[i]) % mod;
			ltr[1][i] = hash;
		}
	}

	// row 0, from right to left
	{
		long long hash = 0;
		for (int i = 0; i < n; i ++) {
			hash = ((long long)s1[i] * _pow[2 * i + 1] + hash * seed + s2[i]) % mod;
			rtl[0][i] = hash;
		}
	}

	// row 1, from right to left
	{
		long long hash = 0;
		for (int i = 0; i < n; i ++) {
			hash = ((long long)s2[i] * _pow[2 * i + 1] + hash * seed + s1[i]) % mod;
			rtl[1][i] = hash;
		}
	}

	// row 0
	// right to left
	{
		unsigned long long sum;
		for (int i = n - 1; i >= 0; i --) {
			int start = 1;
			sum = rtl[0][i] * _pow[2 * (n - 1 - i)] % mod;
			if (n - 1 == i) {
				str_hash.push_back(sum);
			}
			else {
				start = 1;
				for (int j = i + 1; j < n; j ++) {
					if (1 == start) {
						str_hash.push_back((sum + ltr[1][j]) % mod);
						sum += ((long long)s2[j] * seed + s1[j]) * _pow[2 * (n - 1 - j)] % mod;
					}
					else {
						str_hash.push_back((sum + ltr[0][j]) % mod);
						sum += ((long long)s1[j] * seed + s2[j]) * _pow[2 * (n - 1 - j)] % mod;
					}

					start = 1 - start;
				}
			}
		}
	}

	// row 1
	// right to left
	{
		unsigned long long sum;
		for (int i = n - 1; i >= 0; i --) {
			int start = 0;
			sum = rtl[1][i] * _pow[2 * (n - 1 - i)] % mod;
			if (n - 1 == i) {
				str_hash.push_back(sum);
			}
			else {
				for (int j = i + 1; j < n; j ++) {
					if (0 == start) {
						str_hash.push_back((sum + ltr[0][j]) % mod);
						sum += ((long long)s1[j] * seed + s2[j]) * _pow[2 * (n - 1 - j)] % mod;
					}
					else {
						str_hash.push_back((sum + ltr[1][j]) % mod);
						sum += ((long long)s2[j] * seed + s1[j]) * _pow[2 * (n - 1 - j)] % mod;
					}

					start = 1 - start;
				}
			}
		}
	}

	// row 0
	// left to right
	{
		unsigned long long sum;
		for (int i = 0; i < n; i ++) {
			int start = 1;
			sum = ltr[0][i] * _pow[2 * i] % mod;
			if (0 == i) {
				str_hash.push_back(sum);
			}
			else {
				for (int j = i - 1; j >= 0; j --) {
					if (1 == start) {
						str_hash.push_back((sum + rtl[1][j]) % mod);
						sum += ((long long)s2[j] * seed + s1[j]) * _pow[2 * j] % mod;
					}
					else {
						str_hash.push_back((sum + rtl[0][j]) % mod);
						sum += ((long long)s1[j] * seed + s2[j]) * _pow[2 * j] % mod;
					}

					start = 1 - start;
				}
			}
		}	
	}

	// row 1
	// left to right
	{
		unsigned long long sum;
		for (int i = 0; i < n; i ++) {
			int start = 0;
			sum = ltr[1][i] * _pow[2 * i] % mod;
			if (0 == i) {
				str_hash.push_back(sum);
			}
			else {
				for (int j = i - 1; j >= 0; j --) {
					if (0 == start) {
						str_hash.push_back((sum + rtl[0][j]) % mod);
						sum += ((long long)s1[j] * seed + s2[j]) * _pow[2 * j] % mod;
					}
					else {
						str_hash.push_back((sum + rtl[1][j]) % mod);
						sum += ((long long)s2[j] * seed + s1[j]) * _pow[2 * j] % mod;
					}

					start = 1 - start;
				}
			}
		}
	}
	
}

int solve(int n, char *s1, char *s2) {
	int ret = 0;

	vector<long long> str_hash1;
	vector<long long> str_hash2;
	
	solve_priv(n, s1, s2, SEED1, MOD1, str_hash1, _pow1);
	solve_priv(n, s1, s2, SEED2, MOD2, str_hash2, _pow2); 

	vector<long long> str_final;
	for (int i = 0; i < str_hash1.size(); i ++) {
		str_final.push_back(str_hash1[i] << 32 | str_hash2[i]);
	}

	sort(str_final.begin(), str_final.end());
    str_final.erase(unique(str_final.begin(), str_final.end()), str_final.end());
	ret = str_final.size();

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

	init(_pow1, SEED1, MOD1);
	init(_pow2, SEED2, MOD2);

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
