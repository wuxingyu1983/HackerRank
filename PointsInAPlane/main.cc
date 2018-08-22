//
//  main.cpp
//  test
//
//  Created by wuxingyu on 2018/8/22.
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
#define MAX (1 << 16)

using namespace std;

int cnt[9][MAX]; // 8 - max turns

class Point
{
  public:
    int x, y;
};

void getMinMoves(vector<Point> &p)
{
    long long ret = 0;

    int max = (1 << p.size()) - 1;
    for (int i = 0; i <= 8; i++)
    {
        for (int j = 0; j <= max; j++)
        {
            cnt[i][j] = 0;
        }
    }

    cnt[0][max] = 1;

    for (int m = 0; m <= 8; m++)
    {
        if (cnt[m][0])
        {
            // end, process ret
            ret = 1;
            for (int i_m = m; i_m >= 1; i_m--)
            {
                ret *= i_m;
            }

            ret *= cnt[m][0];
            ret %= MOD;

            cout << m << " " << ret << "\n";

            break;
        }
        else
        {
            for (int i = 1; i <= max; i++)
            {
                if (cnt[m][i])
                {
                    int origin = i;
                    int j = 0;
                    for (j = 0; j < p.size(); j++)
                    {
                        if (origin == (1 << j))
                        {
                            // only 1 point
                            cnt[m + 1][0] += cnt[m][i];
                            cnt[m + 1][0] %= MOD;
                            break;
                        }
                    }

                    if (j == p.size())
                    {
                        vector<int> masks;

                        for (int p1 = 0; p1 < p.size(); p1++)
                        {
                            for (int p2 = 0; p2 < p.size(); p2++)
                            {
                                if (p1 != p2)
                                {
                                    if (origin & (1 << p1) && origin & (1 << p2))
                                    {
                                        int mask = (1 << p1) | (1 << p2);

                                        for (int p3 = 0; p3 < p.size(); p3++)
                                        {
                                            if (p3 != p1 && p3 != p2 && (origin & (1 << p3)))
                                            {
                                                if ((p[p2].x - p[p1].x) * (p[p3].y - p[p1].y) == (p[p3].x - p[p1].x) * (p[p2].y - p[p1].y))
                                                {
                                                    // on one line
                                                    mask |= (1 << p3);
                                                }
                                            }
                                        }

                                        if (0 == masks.size())
                                        {
                                            masks.push_back(mask);
                                            int dst = origin ^ mask;
                                            cnt[m + 1][dst] += cnt[m][origin];
                                            cnt[m + 1][dst] %= MOD;
                                        }
                                        else
                                        {
                                            int i_m = 0;
                                            for (i_m = 0; i_m < masks.size(); i_m++)
                                            {
                                                if (masks[i_m] == mask)
                                                {
                                                    break;
                                                }
                                            }

                                            if (i_m == masks.size())
                                            {
                                                masks.push_back(mask);
                                                int dst = origin ^ mask;
                                                cnt[m + 1][dst] += cnt[m][origin];
                                                cnt[m + 1][dst] %= MOD;
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
}

int main()
{
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i_t = 0; i_t < t; i_t++)
    {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<Point> p(n);

        for (int i_n = 0; i_n < n; i_n++)
        {
            int x, y;
            cin >> x >> y;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            p[i_n].x = x;
            p[i_n].y = y;
        }

        getMinMoves(p);
    }

    return 0;
}
