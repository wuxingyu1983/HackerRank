//
//  main.cpp
//  test
//
//  Created by wuxingyu on 2018/11/13.
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
#define MAX_K 10

using namespace std;

int c[MAX_K][20];
int cost[1 << MAX_K][21];
int cnt[1 << MAX_K]; // 0 - 1 << 10 的各数字二进制1的个数

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

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
#if DEBUG
            inFile >> c[i][j];
#else
            cin >> c[i][j];
#endif

            if (0 < j)
            {
                c[i][j] += c[i][j - 1];
            }
        }
    }

    for (int i = 0; i < (1 << k); i++)
    {
        for (int j = 0; j < k; j++)
        {
            if (i & (1 << j))
            {
                cnt[i]++;
            }
        }
    }

    for (int i = 0; i < (1 << k); i++)
    {
        for (int j = 0; j <= n; j++)
        {
            cost[i][j] = -1;
        }
    }

    cost[0][0] = 0;
    int min = 0;

    for (int step = 0; step < k; step++)
    {
        for (int killer = 0; killer < k; killer++)
        {
            for (int i = 0; i < (1 << k); i++)
            {
                if (cnt[i] == step)
                {
                    if (0 == (i & (1 << killer)))
                    {
                        // killer 还未使用
                        for (int killed = 0; killed < n; killed++)
                        {
                            if (0 == killed)
                            {
                                // killer no kill
                                cost[i | (1 << killer)][killed] = 0;

                                for (int new_killed = killed + 1; new_killed <= n; new_killed++)
                                {
                                    int tmp = cost[i][killed] + c[killer][new_killed - 1];
                                    if ((0 > cost[i | (1 << killer)][new_killed]) || tmp < cost[i | (1 << killer)][new_killed])
                                    {
                                        cost[i | (1 << killer)][new_killed] = tmp;

                                        if (new_killed == n && (0 == min || tmp < min))
                                        {
                                            min = tmp;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                if (0 <= cost[i][killed])
                                {
                                    // killer no kill
                                    int tmp = cost[i][killed];
                                    if (0 > cost[i | (1 << killer)][killed] || tmp < cost[i | (1 << killer)][killed])
                                    {
                                        cost[i | (1 << killer)][killed] = tmp;
                                    }

                                    for (int new_killed = killed + 1; new_killed <= n; new_killed++)
                                    {
                                        tmp = cost[i][killed] + c[killer][new_killed - 1] - c[killer][killed - 1];

                                        if ((0 > cost[i | (1 << killer)][new_killed]) || tmp < cost[i | (1 << killer)][new_killed])
                                        {
                                            cost[i | (1 << killer)][new_killed] = tmp;

                                            if (new_killed == n && (0 == min || tmp < min))
                                            {
                                                min = tmp;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    cout << min << "\n";

    return 0;
}
