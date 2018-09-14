//
//  main.cpp
//  test
//
//  Created by 吴星煜 on 2018/8/22.
//  Copyright © 2018年 吴星煜. All rights reserved.
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

#define MOD         1000000007
#define MAX         (1 << 16)
#define DEBUG       0

using namespace std;

int cnt[50][9][MAX]; // 8 - max turns

int flag[MAX];
int pos1[MAX];
int pos2[MAX];

int cnt1[MAX];

class Point
{
  public:
    int x, y;
};

void getMinMoves(int index, vector<Point> &p)
{
    int p_size = p.size();
    int max = (1 << p_size) - 1;

    cnt[index][0][max] = 1;

    for (int m = 0; m <= 8; m++)
    {
        int i = 0;

        if (0 == m)
        {
            i = max;
        }

        if (cnt[index][m][0])
        {
            // end, process ret
            cout << m << " " << cnt[index][m][0] << "\n";

            break;
        }
        else
        {
            for (; i <= max; i++)
            {
                if (cnt[index][m][i])
                {
                    int origin = i;

                    if (1 == cnt1[origin])
                    {
                        long long tmp = (long long)cnt[index][m][i] * (long long)(m + 1);
                        cnt[index][m + 1][0] += tmp % MOD;
                        cnt[index][m + 1][0] %= MOD;
                    }
                    else
                    {
                        // remove all
                        int flag_size = 0;

                        for (int p1 = 0; p1 < p_size; p1++)
                        {
                            if (origin < (1 << p1))
                            {
                                break;
                            }

                            if (origin & (1 << p1))
                            {
                                int mask = 1 << p1;

                                if (0 < flag_size)
                                {
                                    int tmp_size = flag_size;
                                    for (int f_i = 0; f_i < tmp_size; f_i++)
                                    {
                                        int p2 = -1, p3 = -1;

                                        p2 = pos1[f_i];
                                        p3 = pos2[f_i];

                                        if (0 > p3)
                                        {
                                            int dst = origin ^ (mask | flag[f_i]);
                                            cnt[index][m + 1][dst] += cnt[index][m][i];
                                            cnt[index][m + 1][dst] %= MOD;

                                            pos1[flag_size] = p1;
                                            pos2[flag_size] = p2;
                                            flag[flag_size++] = mask | flag[f_i];
                                        }
                                        else
                                        {
                                            if ((p[p2].y - p[p1].y) * (p[p3].x - p[p1].x) == (p[p3].y - p[p1].y) * (p[p2].x - p[p1].x))
                                            {
                                                // on one line
                                                int dst = origin ^ (mask | flag[f_i]);
                                                cnt[index][m + 1][dst] += cnt[index][m][i];
                                                cnt[index][m + 1][dst] %= MOD;

                                                pos1[flag_size] = p1;
                                                pos2[flag_size] = p3;
                                                flag[flag_size++] = mask | flag[f_i];
                                            }
                                        }
                                    }
                                }

                                // set p1
                                {
/*
                                    int dst = origin ^ mask;
                                    cnt[index][m + 1][dst] += cnt[index][m][i];
                                    cnt[index][m + 1][dst] %= MOD;
*/
                                    pos1[flag_size] = p1;
                                    pos2[flag_size] = -1;
                                    flag[flag_size++] = mask;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int main()
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

    for (int i = 0; i < 16; i ++) {
        cnt1[1 << i] = 1;
    }

    for (int i_t = 0; i_t < t; i_t++)
    {
        int n;
#if DEBUG
        inFile >> n;
#else
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
#endif
        vector<Point> p(n);

        for (int i_n = 0; i_n < n; i_n++)
        {
            int x, y;
#if DEBUG
            inFile >> x >> y;
#else
            cin >> x >> y;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
#endif

            p[i_n].x = x;
            p[i_n].y = y;
        }

        getMinMoves(i_t, p);
    }

    return 0;
}
