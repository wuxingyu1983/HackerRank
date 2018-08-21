//
//  main.cpp
//  test
//
//  Created by wuxingyu on 2018/8/21.
//  Copyright © 2018年 wuxingyu. All rights reserved.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAX 1001

using namespace std;

int base[MAX];   // base[w]
int A[MAX][MAX]; // A[h][w]
int S[MAX][MAX];

int legoBlocks(int n, int m)
{
    if (0 == S[n][m])
    {
        for (int w = 1; w <= m; w++)
        {
            if (1 == w)
            {
                S[n][w] = 1;
            }
            else
            {
                S[n][w] = A[n][w];
                for (int l = 1; l < w; l++)
                {
                    long long prd = (long long)S[n][l] * (long long)A[n][w - l];
                    prd %= MOD;
                    S[n][w] = S[n][w] + MOD - prd;
                    S[n][w] %= MOD;
                }
            }
        }
    }

    return S[n][m];
}

int main()
{
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    base[0] = 1;
    for (int i = 1; i < MAX; i++)
    {
        if (0 <= i - 1)
        {
            base[i] += base[i - 1];
            base[i] %= MOD;
        }
        if (0 <= i - 2)
        {
            base[i] += base[i - 2];
            base[i] %= MOD;
        }
        if (0 <= i - 3)
        {
            base[i] += base[i - 3];
            base[i] %= MOD;
        }
        if (0 <= i - 4)
        {
            base[i] += base[i - 4];
            base[i] %= MOD;
        }
    }

    for (int h = 1; h < MAX; h++)
    {
        for (int w = 1; w < MAX; w++)
        {
            if (1 == h)
            {
                A[h][w] = base[w];
            }
            else
            {
                long long prd = (long long)base[w] * (long long)A[h - 1][w];
                A[h][w] = prd % MOD;
            }
        }
    }

    for (int i = 0; i < t; i++)
    {
        int n, m;
        cin >> n >> m;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int result = legoBlocks(n, m);
        cout << result << "\n";
    }

    return 0;
}
