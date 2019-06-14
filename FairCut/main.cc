#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <map>
#include <limits>

using namespace std;

#define DEBUG   0
#define MAX_NK  3001

long long dp[MAX_NK][MAX_NK];   // dp[i][j]

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int n, k;
#if DEBUG
    inFile >> n >> k;
#else
    cin >> n >> k;
#endif

    vector<long long> a;
    for (size_t i = 0; i < n; i++)
    {
        long long tmp;
#if DEBUG
        inFile >> tmp;
#else
        cin >> tmp;
#endif
        a.push_back(tmp);
    }

    sort(a.begin(), a.end());

    for (size_t i = 0; i <= n; i++)
    {
        for (size_t j = 0; j <= k; j++)
        {
            dp[i][j] = LONG_MAX;
        }
    }

    dp[0][0] = 0;

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j <= i; j++)
        {
            if (j > k || i - j > n - k)
            {
                continue;
            }

            long long li = dp[i][j] + ((long long)(i - j)) * a[i] - ((long long)(n - k - (i - j))) * a[i];
            if (dp[i + 1][j + 1] > li)
            {
                dp[i + 1][j + 1] = li;
            }

            long long lu = dp[i][j] + ((long long)j) * a[i] - ((long long)(k - j)) * a[i];
            if (dp[i + 1][j] > lu)
            {
                dp[i + 1][j] = lu;
            }
        }
    }

    cout << dp[n][k] << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
