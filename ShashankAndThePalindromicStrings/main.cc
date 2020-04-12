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

#define DEBUG   0
#define MOD     1000000007
#define MAX_N   50

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
        
        long long ans = 0;
        
        vector<string> a(n);
        vector< vector< vector<int> > > pc(n);
        for (size_t i_n = 0; i_n < n; i_n++)
        {
#if DEBUG
            inFile >> a[i_n];
#else
            cin >> a[i_n];
#endif
            
            // 计算该串中所有回文串的个数 Palindromic Count, pc[][]，index 从 1 开始
            // pc[0][index] 以 index 为右起点回文的个数，pc[index][0] 以 index 为左起点回文的个数
            int len = a[i_n].size();
            
            pc[i_n].resize(len + 1);
            
            for (size_t i = 0; i <= len; i++)
            {
                pc[i_n][i].resize(len + 1);
            }
            
            for (size_t l = 0; l < len; l++)
            {
                for (size_t i = 1; i <= len; i++)
                {
                    int j = i + l;
                    if (len < j)
                    {
                        break;
                    }
                    
                    if (0 == l)
                    {
                        pc[i_n][i][i] = 1;
                        pc[i_n][0][i]++;
                        pc[i_n][i][0]++;
                        pc[i_n][0][0]++;
                    }
                    else if (1 == l)
                    {
                        if (a[i_n][i - 1] == a[i_n][j - 1])
                        {
                            pc[i_n][i][j] = 1;
                            pc[i_n][i][0] += 1;
                            pc[i_n][0][j] += 1;
                            pc[i_n][0][0] += 1;
                        }

                        pc[i_n][i][i + l] += 2;
                    }
                    else
                    {
                        if (a[i_n][i - 1] == a[i_n][j - 1])
                        {
                            pc[i_n][i][j] = pc[i_n][i + 1][j - 1] + 1;
                            pc[i_n][i][0] += pc[i_n][i][j];
                            pc[i_n][0][i + l] += pc[i_n][i][j];
                            pc[i_n][0][0] += pc[i_n][i][j];

                            pc[i_n][i][j] = pc[i_n][i + 1][j] + pc[i_n][i][j - 1] + 1;
                        }
                        else
                        {
                            pc[i_n][i][j] = pc[i_n][i + 1][j] + pc[i_n][i][j - 1] - pc[i_n][i + 1][j - 1];
                        }
                    }
                }
            }
        }

        if (1 == n)
        {
            ans = pc[0][0][0];
        }
        else
        {
            vector< vector< vector< vector<int> > > > cnt(n, vector< vector< vector<int> > >(n));
            for (size_t l = n - 1; l >= 1; l--)
            {
                for (size_t i = 0; i < n; i++)
                {
                    int j = i + l;
                    if (n <= j)
                    {
                        break;
                    }

                    int len_i = a[i].size();
                    int len_j = a[j].size();

                    cnt[i][j].resize(len_i + 1);
                    for (size_t p = 0; p <= len_i; p++)
                    {
                        cnt[i][j][p].resize(len_j + 1);
                    }

                    for (size_t idx_i = 1; idx_i <= len_i; idx_i++)
                    {
                        for (size_t idx_j = len_j; idx_j >= 1; idx_j--)
                        {
                            if (a[i][idx_i - 1] == a[j][idx_j - 1])
                            {
                                cnt[i][j][idx_i][idx_j] = 1;

                                if (1 < idx_i && len_j > idx_j)
                                {
                                    cnt[i][j][idx_i][idx_j] += cnt[i][j][idx_i - 1][idx_j + 1];
                                    cnt[i][j][idx_i][idx_j] %= MOD;
                                }

                                if (0 < i && j < n - 1)
                                {
                                    cnt[i][j][idx_i][idx_j] += cnt[i - 1][j + 1][0][0];
                                    cnt[i][j][idx_i][idx_j] %= MOD;
                                }

                                if (0 < i && len_j > idx_j)
                                {
                                    cnt[i][j][idx_i][idx_j] += cnt[i - 1][j][0][idx_j + 1];
                                    cnt[i][j][idx_i][idx_j] %= MOD;
                                }

                                if (j < n - 1 && 1 < idx_i)
                                {
                                    cnt[i][j][idx_i][idx_j] += cnt[i][j + 1][idx_i - 1][0];
                                    cnt[i][j][idx_i][idx_j] %= MOD;
                                }

                                if (1 == l)
                                {
                                    ans += cnt[i][j][idx_i][idx_j];
                                    ans %= MOD;

                                    long long tmp = (long long)cnt[i][j][idx_i][idx_j] * (long long)pc[i][idx_i][0];
                                    tmp %= MOD;
                                    ans += tmp;
                                    ans %= MOD;

                                    tmp = (long long)cnt[i][j][idx_i][idx_j] * (long long)pc[j][0][idx_j];
                                    tmp %= MOD;
                                    ans += tmp;
                                    ans %= MOD;
                                }
                                else
                                {
                                    cnt[i][j][0][0] += cnt[i][j][idx_i][idx_j];
                                    cnt[i][j][0][0] %= MOD;
                                    cnt[i][j][idx_i][0] += cnt[i][j][idx_i][idx_j];
                                    cnt[i][j][idx_i][0] %= MOD;
                                    cnt[i][j][0][idx_j] += cnt[i][j][idx_i][idx_j];
                                    cnt[i][j][0][idx_j] %= MOD;
                                }
                            }
                        }
                    }

                    if (2 == l)
                    {
                        long long tmp = (long long)pc[i + 1][0][0] * (long long)cnt[i][j][0][0];
                        tmp %= MOD;
                        ans += tmp;
                        ans %= MOD;
                    }
                }
            }
        }
        cout << ans << endl;
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
