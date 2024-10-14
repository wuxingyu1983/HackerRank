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

#define MOD 1000000007
#define MAX_N 100001
#define MAX_M 20
#define MAX_2M 1048576

int dp[MAX_2M];
int pw[MAX_N];      // power array

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    pw[0] = 1;
    
    for (size_t i = 1; i <= n; i++)
    {
        int tmp = 0;

        for (size_t j = 0; j < m; j++)
        {
            char c;
            cin >> c;

            tmp <<= 1;
            if ('1' == c)
            {
                tmp += 1;
            }
        }
        
        dp[tmp] ++;

        pw[i] = (pw[i - 1] << 1) % MOD;
    }

    int target = 0;

    for (size_t j = 0; j < m; j++)
    {
        char c;
        cin >> c;

        target <<= 1;
        if ('1' == c)
        {
            target += 1;
        }
    }

    

    return 0;
}
