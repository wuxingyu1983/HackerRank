#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

#define MOD 1000000007
#define MAX_N   2500
#define MAX_K   2500

int a[MAX_N + 1][MAX_K + 1];
int sum[MAX_N + 1][MAX_K + 1];
int b[MAX_N + 1][MAX_K + 2];

using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;

    a[1][0] = 1;

    for (int j = 0; j <= k; j ++)
    {
        sum[1][j] = 1;
    }

    for (int i = 2; i <= n; i++)
    {
        for (int j = 0; j <= k; j ++)
        {
            if (j - i < 0) 
            {
                a[i][j] = sum[i - 1][j];
            }
            else 
            {
                a[i][j] = sum[i - 1][j] - sum[i - 1][j - i] + MOD;
            }

            a[i][j] %= MOD;
            if (0 < j)
            {
                sum[i][j] = sum[i][j - 1] + a[i][j];
            }
            else
            {
                sum[i][j] = a[i][j];
            }
            sum[i][j] %= MOD;
        }
    }

    int ret1 = 0, ret2 = 0;

    for (int i = k; i >= 0; i -= 2)
    {
        ret1 += a[n][i];
        ret1 %= MOD;
    }

    b[1][1] = 1;

    for (int i = 1; i < n; i ++)
    {
        for (int j = 1; j <= n; j ++)
        {
            b[i + 1][j + 1] += b[i][j];
            b[i + 1][j + 1] %= MOD;

            long long tmp = 0;
            tmp = (long long)i * (long long)b[i][j];
            tmp %= MOD;

            b[i + 1][j] += tmp;
            b[i + 1][j] %= MOD;
        }
    }

    for (int j = n; j > 0 && j >= n - k; j --)
    {
        ret2 += b[n][j];
        ret2 %= MOD;
    }

    cout << ret1 << " " << ret2 << "\n"; 

    return 0;
}
