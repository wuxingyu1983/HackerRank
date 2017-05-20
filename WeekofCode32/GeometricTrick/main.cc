#include <vector>
#include <stack>
#include <map>
#include <queue>
#include <set>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

#define LL long long
#define FOR(i, n) for (int i = 0; i < (n); i++)

const int MAX_N = 500000;
char S[MAX_N + 2];
int n;

int factor[10];
int expo[10];
int factorN;

bool isprime[MAX_N+1];
vector<int> primes;

void decompose(int x) {
	factorN = 0;
	for (int p : primes) {
		if (x % p == 0) {
			factor[factorN] = p;
			expo[factorN] = 0;
			while (x % p == 0) {
				x /= p;
				expo[factorN]++;
			}
			factorN++;
		}
		if (x == 1) return;
	}
}

void calPrimes() {
	fill(isprime, isprime + MAX_N+1, true);
	isprime[2] = true;
	for (int i = 2; i < MAX_N/2+2; i++) if (isprime[i]) {
		for (int j = i + i; j <= MAX_N; j += i) {
			isprime[j] = false;
		}
	}
	for (int i = 2; i <= MAX_N; i++) if (isprime[i]) {
		primes.push_back(i);
	}
}

int result;

void dfsFactor(LL j, LL i, LL r) {
	if (i == factorN) {
		if (r > n || S[r] != 'a') return;
		LL k = j * j / r;
		if (k <= n && S[k] == 'c') result++;
		return;
	}
	for (int t = 0; t <= expo[i]; t++) {
		dfsFactor(j, i+1, r);
		r = r * factor[i];
		if (r > n) break;
	}
}

int solve() {
	calPrimes();
	result = 0;
	for (int j = 2; j <= n; j++) if (S[j] == 'b') {
		decompose(j);
		FOR(i, factorN) expo[i] *= 2;
		dfsFactor(j, 0, 1);
	}
	return result;
}

int main()
{
	scanf("%d", &n);
	scanf("%s", S+1);
	cout << solve() << endl;
}
