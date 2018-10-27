//
//  main.cpp
//  test
//
//  Created by wuxingyu on 2018/10/27.
//  Copyright © 2018 wuxingyu. All rights reserved.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

#define DEBUG 0
#define MOD 1000000007

using namespace std;

int x[10], D[10];
long long tmp[10][10][301][101]; // test cases, dimensions, step, point
long long cnt[10][10][301];      // test cases, dimensions, step
long long c[301][301];
long long sum[10][10][301]; // test cases, dimensions, step

int main(int argc, char const *argv[])
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int t;
#if DEBUG
    inFile >> t;
#else
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
#endif

    for (long long i = 1; i <= 300; i++)
    {
        c[i][0] = 1;
        c[i][i] = 1;
        for (long long j = 1; j <= i / 2; j++)
        {
            if (1 == j)
            {
                c[i][j] = i;
            }
            else
            {
                c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
            }
            c[i][j] %= MOD;

            c[i][i - j] = c[i][j];
        }
    }

    for (int i_t = 0; i_t < t; i_t++)
    {
        int n, m; // dimensions, step
#if DEBUG
        inFile >> n >> m;
#else
        cin >> n >> m;
#endif

        for (int i_x = 0; i_x < n; i_x++)
        {
#if DEBUG
            inFile >> x[i_x];
#else
            cin >> x[i_x];
#endif
        }

        for (int i_d = 0; i_d < n; i_d++)
        {
#if DEBUG
            inFile >> D[i_d];
#else
            cin >> D[i_d];
#endif
        }

        for (int i_n = 0; i_n < n; i_n++)
        {
            tmp[i_t][i_n][0][x[i_n]] = 1;

            cnt[i_t][i_n][0] = 1;
            for (int step = 1; step <= m; step++)
            {
                for (int point = 1; point <= D[i_n]; point++)
                {
                    if (point - 1 > 0)
                    {
                        tmp[i_t][i_n][step][point] += tmp[i_t][i_n][step - 1][point - 1];
                        tmp[i_t][i_n][step][point] %= MOD;
                    }

                    if (point + 1 <= D[i_n])
                    {
                        tmp[i_t][i_n][step][point] += tmp[i_t][i_n][step - 1][point + 1];
                        tmp[i_t][i_n][step][point] %= MOD;
                    }

                    cnt[i_t][i_n][step] += tmp[i_t][i_n][step][point];
                    cnt[i_t][i_n][step] %= MOD;
                }
            }
        }

        for (int i_n = 0; i_n < n; i_n++)
        {
            for (int step = 0; step <= m; step++)
            {
                if (0 == i_n)
                {
                    sum[i_t][i_n][step] = cnt[i_t][i_n][step];
                }
                else
                {
                    if (0 == step)
                    {
                        sum[i_t][i_n][step] = 1;
                    }
                    else
                    {
                        if (0 == cnt[i_t][i_n][step])
                        {
                            sum[i_t][i_n][step] = sum[i_t][i_n - 1][step];
                        }
                        else
                        {
                            for (int i = 0; i <= step; i++)
                            {
                                long long plus = (sum[i_t][i_n - 1][step - i] * cnt[i_t][i_n][i]) % MOD;
                                sum[i_t][i_n][step] += (plus * c[step][i]) % MOD;
                                sum[i_t][i_n][step] %= MOD;
                            }
                        }
                    }
                }
            }
        }

        cout << sum[i_t][n - 1][m] << "\n";
    }

    return 0;
}
