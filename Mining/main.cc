#include <cmath>
#include <cstdio>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <limits.h>

#define DEBUG 0
#define MAX_N 5001

unsigned long long sumstb[MAX_N];
unsigned long long stb[MAX_N];
unsigned long long sumbts[MAX_N];
unsigned long long bts[MAX_N];

int n;

// 0 - small to big, 1 - big to small
unsigned long long cost[2][MAX_N][MAX_N];

using namespace std;

class Mine
{
public:
    int x, w;

    Mine(int _x = 0, int _w = 0)
    {
        x = _x;
        w = _w;
    }

    void operator=(const Mine &m)
    {
        x = m.x;
        w = m.w;
    }
};

vector<Mine> mines(MAX_N);

bool func(const Mine &m1, const Mine &m2)
{
    return (m1.x < m2.x);
}

inline long long costFromStoB(int s, int b)
{
    long long ret = 0;

    if (s < b)
    {
        if (0 == s)
        {
            ret = stb[b];
        }
        else
        {
            ret = stb[b] - stb[s] - sumstb[s - 1] * (long long)(mines[b].x - mines[s].x);
        }
    }

    return ret;
}

inline long long costFromBtoS(int s, int b)
{
    long long ret = 0;

    if (s < b)
    {
        if (n - 1 == b)
        {
            ret = bts[s];
        }
        else
        {
            ret = bts[s] - bts[b] - sumbts[b + 1] * (long long)(mines[b].x - mines[s].x);
        }
    }

    return ret;
}

int main()
{
//    cout << "begin" << endl;
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int k;
#if DEBUG
    inFile >> n >> k;
#else
    cin >> n >> k;
#endif

    for (size_t i = 0; i < n; i++)
    {
        int x, w;
#if DEBUG
        inFile >> x >> w;
#else
        cin >> x >> w;
#endif

        mines[i].x = x;
        mines[i].w = w;
    }

    // sort
    sort(mines.begin(), mines.begin() + n, func);

    // small to big
    sumstb[0] = mines[0].w;
    for (size_t i = 1; i < n; i++)
    {
        sumstb[i] = mines[i].w + sumstb[i - 1];

        stb[i] = stb[i - 1] + sumstb[i - 1] * (mines[i].x - mines[i - 1].x);
    }

    // big to small
    sumbts[n - 1] = mines[n - 1].w;
    for (int i = n - 2; i >= 0; i--)
    {
        sumbts[i] = mines[i].w + sumbts[i + 1];

        bts[i] = bts[i + 1] + sumbts[i + 1] * (mines[i + 1].x - mines[i].x);
    }

    int tmove = n - k;
    unsigned long long ret = 0;

    for (size_t i = 0; i < n; i++)
    {
        for (size_t m = 0; m <= tmove; m++)
        {
            if (0 < i)
            {
                unsigned long long tmp = cost[0][i - 1][m];
                if (0 == tmp)
                {
                    tmp = cost[1][i - 1][m];
                }
                else
                {
                    if (tmp > cost[1][i - 1][m] && 0 < cost[1][i - 1][m])
                    {
                        tmp = cost[1][i - 1][m];
                    }
                }
                
                if (0 < tmp && (0 == cost[0][i][m] || cost[0][i][m] > tmp))
                {
                    cost[0][i][m] = tmp;
                    if (tmove == m)
                    {
                        if (0 == ret || ret > cost[0][i][m])
                        {
                            ret = cost[0][i][m];
                        }
                    }
                }
                
                if (0 < tmp && (0 == cost[1][i][m] || cost[1][i][m] > tmp))
                {
                    cost[1][i][m] = tmp;
                    if (tmove == m)
                    {
                        if (0 == ret || ret > cost[1][i][m])
                        {
                            ret = cost[1][i][m];
                        }
                    }
                }
            }

            for (int j = i - 1; j >= 0 && j >= i - m; j--)
            {
                if (0 < m - (i - j) && 0 == cost[1][j][m - (i - j)])
                {
                    continue;
                }
                
                if (0 == cost[0][i][m] || cost[0][i][m] > (cost[1][j][m - (i - j)] + costFromStoB(j, i)))
                {
                    cost[0][i][m] = cost[1][j][m - (i - j)] + costFromStoB(j, i);
                    if (tmove == m)
                    {
                        if (0 == ret || ret > cost[0][i][m])
                        {
                            ret = cost[0][i][m];
                        }
                    }
                }
            }

            for (size_t j = i + 1; j < n; j++)
            {
                if (m + j - i > tmove)
                {
                    break;
                }

                unsigned long long tmp = cost[0][i][m];
                if (0 == tmp)
                {
                    tmp = cost[1][i][m];
                }
                else
                {
                    if (tmp > cost[1][i][m] && 0 < cost[1][i][m])
                    {
                        tmp = cost[1][i][m];
                    }
                }
                
                if (0 < m && 0 == tmp)
                {
                    break;
                }

                if (0 == cost[1][j + 1][m + j - i] || cost[1][j + 1][m + j - i] > (tmp + costFromBtoS(i, j)))
                {
                    cost[1][j + 1][m + j - i] = tmp + costFromBtoS(i, j);
                    if (tmove == m + j - i)
                    {
                        if (0 == ret || ret > cost[1][j + 1][m + j - i])
                        {
                            ret = cost[1][j + 1][m + j - i];
                        }
                    }
                }
            }
        }
    }

    cout << ret << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
