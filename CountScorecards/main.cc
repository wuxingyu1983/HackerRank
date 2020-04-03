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
#define MAX_T 20
#define MAX_N 40

int dp[MAX_T][MAX_N + 1][MAX_N + 1][MAX_N * (MAX_N - 1) / 2 + 1];

// combination
int C[MAX_N + 1][MAX_N + 1];

int main()
{
    // init combination
    C[0][0] = 1;
    for (int n = 1; n <= MAX_N; n++)
    {
        C[n][0] = 1;

        for (int m = 1; m <= n; m++)
        {
            // C(n,m)=C(n-1,m)+C(n-1,m-1)
            C[n][m] = C[n - 1][m] + C[n - 1][m - 1];
            C[n][m] %= MOD;
        }
    }

#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int t;
#if DEBUG
    inFile >> t;
#else
    cin >> t;
#endif

    for (size_t i_t = 0; i_t < t; i_t++)
    {
        int n;
#if DEBUG
        inFile >> n;
#else
        cin >> n;
#endif

        int sumOfNoErased = 0;
        vector<int> a;
        a.reserve(n);

        for (size_t i_n = 0; i_n < n; i_n++)
        {
            int score;
#if DEBUG
            inFile >> score;
#else
            cin >> score;
#endif

            if (0 <= score)
            {
                sumOfNoErased += score;
                a.push_back(score);
            }
        }

        if ((n * (n - 1) / 2) < sumOfNoErased)
        {
            cout << 0 << endl;
        }
        else
        {
            if (1 == n)
            {
                cout << 1 << endl;
            }
            else
            {
                int cnt_no_erased = a.size();
                int cnt_erased = n - cnt_no_erased;

                sort(a.begin(), a.end());

                long long ans = 0;
                // check no erased
                int tmp = a[0];
                for (size_t i = 1; i < cnt_no_erased; i++)
                {
                    tmp += a[i];

                    if (tmp < (i * (i + 1) / 2))
                    {
                        ans = -1;
                        break;
                    }
                }

                if (0 > ans)
                {
                    cout << 0 << endl;
                }
                else
                {
                    if (0 == cnt_erased)
                    {
                        cout << 1 << endl;
                    }
                    else
                    {
                        vector<int> exceed(cnt_erased + 1);

                        for (size_t k = 1; k <= cnt_erased; k++)
                        {
                            int min = n * n;
                            int e = 0;
                            for (size_t l = 0; l < cnt_no_erased; l++)
                            {
                                e += a[l] - (k + l);
                                if (e < min)
                                {
                                    min = e;
                                }
                            }

                            exceed[k] = min;
                        }

                        for (size_t i = 0; i < n; i++)
                        {
                            dp[i_t][0][i][0] = 1;
                        }

                        int sumOfErased = n * (n - 1) / 2 - sumOfNoErased;
                        for (int k = 1; k <= cnt_erased; k++)
                        {
                            int sum_begin = k * (k - 1) / 2 - exceed[k];
                            if (sum_begin < k * (k - 1) / 2)
                            {
                                sum_begin = k * (k - 1) / 2;
                            }
                            if (sum_begin < 0)
                            {
                                sum_begin = 0;
                            }

                            for (int score = 0; score < n; score++)
                            {
                                for (int sum = sum_begin; sum <= sumOfErased; sum++)
                                {
                                    if (0 < score)
                                    {
                                        dp[i_t][k][score][sum] += dp[i_t][k][score - 1][sum];
                                    }
                                    for (int i = 1; i <= k; i++)
                                    {
                                        if (0 > sum - i * score)
                                        {
                                            break;
                                        }

                                        long long tmp = 0;
                                        if (0 < score)
                                        {
                                            tmp = (long long)C[cnt_erased - (k - i)][i] * (long long)dp[i_t][k - i][score - 1][sum - i * score];
                                            tmp %= MOD;
                                        }
                                        else
                                        {
                                            // 0 == score
                                            if (0 == sum)
                                            {
                                                tmp = (long long)C[cnt_erased - (k - i)][i];
                                            }
                                        }

                                        dp[i_t][k][score][sum] += tmp;
                                        dp[i_t][k][score][sum] %= MOD;

                                        if (k == cnt_erased && sum == sumOfErased)
                                        {
                                            ans += tmp;
                                            ans %= MOD;
                                        }
                                    }
                                }
                            }
                        }

                        cout << ans << endl;
                    }
                }
            }
        }
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
