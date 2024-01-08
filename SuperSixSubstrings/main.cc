// https://www.hackerrank.com/contests/hourrank-18/challenges/super-six-substrings/problem

#include <cmath>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <queue>
#include <stack>
#include <climits>
#include <cfloat>
#include <limits>
#include <bitset>

using namespace std;

#define DEBUG 0
#define MAX_LEN 100001

unsigned long long dp[MAX_LEN][6];

int main()
{
    unsigned long long ans = 0;

    string str;
    cin >> str;

    int len = str.length();
    int pre = 0, curr = 0;
    for (size_t i = 0; i < len; i++)
    {
        curr = str.at(i) - '0';
        dp[i][curr % 6] ++;

        if (0 < i)
        {
            // 0
            for (size_t j = 0; j < 6; j++)
            {
                dp[i][(10 * j + curr) % 6] += dp[i - 1][j];
            }

            if (0 == pre)
            {
                dp[i][curr % 6] --;
            }
        }

        ans += dp[i][0];

        pre = curr;
    }

    cout << ans << endl;

    return 0;
}
