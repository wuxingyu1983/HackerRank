#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

#define MOD     1000000007

using namespace std;

unsigned char flags[8192];

int multiset_count(vector<int> &a) {
    long long ret = 0;

    int cnts[4501];
    memset(cnts, 0, sizeof(int) * 4501);

    for (size_t i = 0; i < a.size(); i++) {
        cnts[a[i]] ++;
    }

    int c[8192];
    memset(c, 0, sizeof(int) * 8192);

    c[0] = 1;

    for (size_t i = 3500; i <= 4500; i++) {
        if (cnts[i]) {
            int tmp_c[8192];
            memcpy(tmp_c, c, sizeof(int) * 8192);

            long long cnt0 = cnts[i] / 2;
            if (cnt0) {
                for (size_t j = 0; j < 8192; j++) {
                    if (c[j]) {
                        long long tmp = (long long)c[j] * cnt0;
                        tmp += c[j];
                        tmp_c[j] = tmp % MOD;
                    }
                }
            }

            long long cnti = (0 == cnts[i] % 2) ? (cnts[i] / 2) : (cnts[i] / 2 + 1);

            for (size_t j = 0; j < 8192; j++) {
                if (c[j]) {
                    int new_j = i ^ j;
                    long long tmp = (long long)c[j] * cnti + tmp_c[new_j];
                    tmp_c[new_j] = tmp % MOD;
                }
            }

            memcpy(c, tmp_c, sizeof(int) * 8192);
        }
    }

    for (size_t p = 2; p < 8192; p++) {
        if (0 == flags[p] && c[p]) {
            ret += c[p];
            ret %= MOD;
        }
    }

    return (int)ret;
}

int main()
{
    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // get primes from 1 to 8191
    flags[0] = 1;
    flags[1] = 1;
    for (size_t i = 2; i < 8192; i++) {
        if (0 == flags[i]) {
            for (size_t j = 2 * i; j < 8192; j+=i) {
                flags[j] = 1;
            }
        }
    }

    for (int t_itr = 0; t_itr < q; t_itr++)
    {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<int> A(n);

        for (int i = 0; i < n; i++)
        {
            cin >> A[i];
        }

        int result = multiset_count(A);

        cout << result << "\n";
    }

    return 0;
}
