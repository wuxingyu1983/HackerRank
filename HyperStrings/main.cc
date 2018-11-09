//
//  main.cpp
//  test
//
//  Created by wuxingyu on 2018/11/9.
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
#define MAX (1 << 10)
#define MOD 1000000007

using namespace std;

char a[100][11];
long long cnt[111][MAX]; // cnt[len][1 << 10]
int l[100];
int len[MAX];
int imax[MAX];
int imin[MAX];

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("/Users/wuxingyu/Desktop/input.txt");
#endif

    int n, m;
#if DEBUG
    inFile >> n >> m;
#else
    cin >> n >> m;
#endif

    for (int i = 0; i < n; i++)
    {
#if DEBUG
        inFile >> a[i];
#else
        cin >> a[i];
#endif
        int tmp = 0;
        for (int j = 0; j < strlen(a[i]); j++)
        {
            tmp |= 1 << (a[i][j] - 'a');
        }

        l[i] = tmp;
    }

    sort(l, l + n);

    for (int i = 1; i < MAX; i++)
    {
        int t_min = -1, t_max = 0;
        for (int j = 0; j < 10; j++)
        {
            if (i & (1 << j))
            {
                len[i]++;
                if (0 > t_min)
                {
                    t_min = j;
                }

                if (j > t_max)
                {
                    t_max = j;
                }
            }
        }

        imin[i] = t_min;
        imax[i] = t_max;
    }

    long long ret = 0;

    cnt[0][0] = 1;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (cnt[i][j])
            {
                for (int k = 0; k < n; k++)
                {
                    if (imax[j] < imin[l[k]])
                    {
                        int new_j = j | l[k];
                        if (0 == cnt[i][new_j])
                        {
                            cnt[i][new_j] += cnt[i][j];
                            cnt[i][new_j] %= MOD;

                            if (m >= i + len[new_j])
                            {
                                ret += cnt[i][j];
                                ret %= MOD;
                            }
                        }
                    }
                    else
                    {
                        cnt[i + len[j]][l[k]] += cnt[i][j];
                        cnt[i + len[j]][l[k]] %= MOD;

                        if (m >= i + len[j] + len[l[k]])
                        {
                            ret += cnt[i][j];
                            ret %= MOD;
                        }
                    }
                }
            }
        }
    }

    cout << ret + 1 << "\n";

    return 0;
}
