// SOS DP
// http://codeforces.com/blog/entry/45223
#include <cmath>
#include <cstdio>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <limits.h>

#define DEBUG 0
#define MOD 1000000007
#define MAX_N 100000
#define MAX_BITS 20
#define MAX_PB 1048576

long long p[MAX_N + 1];     // power
int bits[MAX_PB + 1];
int dp[21][MAX_PB + 1];
int raw[MAX_N];

using namespace std;

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int n, m;
#if DEBUG
    inFile >> n >> m;
#else
    cin >> n >> m;
#endif

    p[0] = 1;
    for (size_t i = 1; i <= n; i++)
    {
        p[i] = (p[i - 1] * 2) % MOD;

        int tmp = 0;
        for (size_t j = 0; j < m; j++)
        {
            char c;
#if DEBUG
            inFile >> c;
#else
            cin >> c;
#endif

            tmp <<= 1;
            if ('1' == c)
            {
                tmp += 1;
            }
        }

        raw[i - 1] = tmp;
    }

    int target = 0;
    for (size_t j = 0; j < m; j++)
    {
        char c;
#if DEBUG
        inFile >> c;
#else
        cin >> c;
#endif

        target <<= 1;
        if ('1' == c)
        {
            target += 1;
        }
    }

    int n_cnt = 0;
    for (size_t i = 0; i < n; i++)
    {
        if ((raw[i] | target) != target)
        {
            continue;
        }
        n_cnt ++;
        int tmp = 0;
        for (size_t j = 0, mask = 1, nmask = 1; j < m; j++, mask <<= 1)
        {
            if (target & mask)
            {
                if (!(raw[i] & mask))
                {
                    tmp |= nmask;
                }

                nmask <<= 1;
            }
        }

        dp[0][tmp] ++;
    }

    n = n_cnt;
    long long ret = 0;
    if (n) {
    int pw = p[m];
    for (size_t mask = 1, b = 0; b < m; mask <<= 1, b ++)
    {
        for (size_t i = 1; i < pw; i++)
        {
            if (i & mask)
            {
                bits[i] ++;
            }
        }
    }

    for (size_t b = 1; b <= m; b++)
    {
        for (size_t i = 0; i < pw; i++)
        {
            if (i & (1 << (b - 1)))
            {
                // 1
                dp[b][i] = dp[b - 1][i];
            }
            else
            {
                // 0
                dp[b][i] = dp[b - 1][i];
                if ((i | (1 << (b - 1))) < pw)
                {
                    dp[b][i] += dp[b - 1][i | (1 << (b - 1))];
                    dp[b][i] %= MOD;
                }
            }
        }
    }

    ret = p[n] - 1;

    for (size_t i = 1; i < pw; i++)
    {
        if (1 & bits[i])
        {
            ret -= (p[dp[m][i]] - 1);
            ret += MOD;
            ret %= MOD;
        }
        else
        {
            ret += (p[dp[m][i]] - 1);
            ret %= MOD;
        }
    }
    }

    cout << ret << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
