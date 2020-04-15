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

using namespace std;

#define DEBUG 1
#define MOD 1000000007
#define MAX_N 50

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int q;
#if DEBUG
    inFile >> q;
#else
    cin >> q;
#endif

    for (size_t i_q = 0; i_q < q; i_q++)
    {
        int n;
#if DEBUG
        inFile >> n;
#else
        cin >> n;
#endif

        vector<string> a(n);
        for (size_t i_n = 0; i_n < n; i_n++)
        {
#if DEBUG
            inFile >> a[i_n];
#else
            cin >> a[i_n];
#endif
        }

        // dp[i][j][idx_i][idx_j]
        vector<vector<vector<vector<int> > > > dp(n, vector<vector<vector<int> > >(n));
        for (size_t l = 0; l <= n - 1; l++)
        {
            for (size_t i = 0; i < n; i++)
            {
                if (0 == l)
                {
                    int len = a[i].size();

                    dp[i][i].resize(len + 1);
                    for (size_t p = 0; p <= len; p++)
                    {
                        dp[i][i][p].resize(len + 1);
                    }

                    for (size_t j = 0; j < len; j++)
                    {
                        for (size_t k = 1; k <= len; k++)
                        {
                            int m = k + j;
                            if (len < m)
                            {
                                break;
                            }

                            if (0 == j)
                            {
                                dp[i][i][k][k] = 1;
                            }
                            else if (1 == l)
                            {
                                if (a[i][k - 1] == a[i][m - 1])
                                {
                                    dp[i][i][k][m] = 1;
                                }

                                dp[i][i][k][m] += 2;
                            }
                            else
                            {
                                if (a[i][k - 1] == a[i][m - 1])
                                {
                                    dp[i][i][k][m] = dp[i][i][k + 1][m] + dp[i][i][k][m - 1] + 1;
                                }
                                else
                                {
                                    dp[i][i][k][m] = dp[i][i][k + 1][m] + dp[i][i][k][m - 1] - dp[i][i][k + 1][m - 1];
                                }
                            }
                        }
                    }
                }
                else
                {
                    int j = i + l;
                    if (n <= j)
                    {
                        break;
                    }

                    int len_i = a[i].size();
                    int len_j = a[j].size();

                    dp[i][j].resize(len_i + 1);
                    for (size_t p = 0; p <= len_i; p++)
                    {
                        dp[i][j][p].resize(len_j + 1);
                    }

                    // idx_i, idx_j start from 1
                    // idx_i : 1 -- len_i
                    // idx_j : 1 -- len_j
                    for (size_t idx_i = len_i; idx_i >= 1; idx_i--)
                    {
                        for (size_t idx_j = 1; idx_j <= len_j; idx_j++)
                        {
                            long long tmp = 0;
                            if (a[i][idx_i - 1] == a[j][idx_j - 1])
                            {
                                tmp = 1;

                                if (idx_i < len_i && 1 < idx_j)
                                {
                                    tmp += dp[i][j][idx_i + 1][idx_j - 1];
                                }

                                if (1 < l)
                                {
                                    tmp += dp[i + 1][j - 1][1][a[j - 1].size()];
                                }

                                if (idx_i < len_i)
                                {
                                    tmp += dp[i][j - 1][idx_i + 1][a[j - 1].size()];
                                }

                                if (1 < idx_j)
                                {
                                    tmp += dp[i + 1][j][1][idx_j - 1];
                                }

                                tmp %= MOD;
                            }

                            // 更新 dp
                            if (len_i > idx_i)
                            {
                                tmp += (long long)dp[i][j][idx_i + 1][idx_j];
                            }

                            if (1 < idx_j)
                            {
                                tmp += (long long)dp[i][j][idx_i][idx_j - 1];
                            }

                            if (len_i > idx_i && 1 < idx_j)
                            {
                                tmp += MOD;
                                tmp -= (long long)dp[i][j][idx_i + 1][idx_j - 1];
                            }

                            tmp %= MOD;

                            dp[i][j][idx_i][idx_j] = tmp;
                        }
                    }
                }
            }
        }

        int len = a[n - 1].size();
        cout << dp[0][n - 1][1][len] << endl;
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
