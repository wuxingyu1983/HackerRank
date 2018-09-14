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

class Point
{
public:
    int x, y;
};

void recu_func(int index, vector<Point> &p, int p1, int p2, int origin, int mask, int m, int count)
{
    if (0 > p2) {
        // new line
        for (p2 = p1; p2 < p.size(); p2++) {
            if (p2 != p1) {
                if (origin & (1 << p2)) {
                    int new_mask = mask | (1 << p2);
                    int dst = origin ^ new_mask;
                    cnt[index][m + 1][dst] += count;
                    cnt[index][m + 1][dst] %= MOD;

                    recu_func(index, p, p1, p2, origin, new_mask, m, count);
                }
            }
        }
    }
    else {
        // find point on p1 => p2
        for (int p3 = p2; p3 < p.size(); p3++) {
            if (p3 != p2) {
                if (origin & (1 << p3)) {
                    if ((p[p2].y - p[p1].y) * (p[p3].x - p[p1].x) == (p[p3].y - p[p1].y) * (p[p2].x - p[p1].x)) {
                        // p1,p2,p3 on the same line
                        int new_mask = mask | (1 << p3);
                        int dst = origin ^ new_mask;
                        cnt[index][m + 1][dst] += count;
                        cnt[index][m + 1][dst] %= MOD;

                        recu_func(index, p, p1, p3, origin, new_mask, m, count);
                    }
                }
            }
        }
    }
}

void getMinMoves(int index, vector<Point> &p)
{
    int max = (1 << p.size()) - 1;

    cnt[index][0][max] = 1;

    for (int m = 0; m <= 8; m++)
    {
        if (cnt[index][m][0])
        {
            // end, process ret
            cout << m << " " << cnt[index][m][0] << "\n";

            break;
        }
        else
        {
            for (int i = 1; i <= max; i++)
            {
                if (cnt[index][m][i])
                {
                    int origin = i;
                    int cnt1 = 0;

                    for (int p1 = 0; p1 < p.size(); p1++)
                    {
                        if (origin & (1 << p1))
                        {
                            cnt1++;
                            int p2 = p1 + 1;
                            for (; p2 < p.size(); p2++)
                            {
                                if (origin & (1 << p2))
                                {
                                    cnt1++;
                                    int mask = 1 << p1 | 1 << p2;
                                    int dst = origin ^ mask;
                                    cnt[index][m + 1][dst] += cnt[index][m][i];
                                    cnt[index][m + 1][dst] %= MOD;

                                    recu_func(index, p, p1, p2, origin, mask, m, cnt[index][m][i]);
                                }
                            }
                        }
                    }

                    if (1 == cnt1)
                    {
                        // only left one point p1
                        int dst = 0;
                        long long tmp = (long long)cnt[index][m][i] * (long long)(m + 1);
                        cnt[index][m + 1][dst] +=  tmp % MOD;
                        cnt[index][m + 1][dst] %= MOD;
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
