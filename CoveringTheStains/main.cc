#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

#define DEBUG 0
#define MOD 1000000007
#define MAX_XY 100000
#define MAX_N 1001

using namespace std;

class Point
{
public:
    int x, y;
    long long key;

    Point(int _x = 0, int _y = 0)
    {
        x = _x;
        y = _y;
        key = (long long)x * MAX_XY + y;
    }
};

long long cnt[MAX_N][MAX_N];
vector<Point> points;
vector< vector<Point> > edges(4);

long long getSum(vector<int> &ei, int k)
{
    long long sum = 0;

    set<long long> es;
    for (vector<int>::iterator it = ei.begin(); it != ei.end(); it++)
    {
        for (size_t i = 0; i < edges[*it].size(); i++)
        {
            es.insert(edges[*it][i].key);
        }
    }

    if (es.size() <= k)
    {
        memset(cnt, 0, MAX_N * MAX_N * sizeof(long long));

        cnt[0][0] = 1;

        for (size_t i = 0; i < points.size(); i++)
        {
            if (es.end() != es.find(points[i].key))
            {
                // found, copy
                memcpy(cnt[i + 1], cnt[i], MAX_N * sizeof(long long));
            }
            else
            {
                // remove
                for (size_t j = 1; j < MAX_N; j++)
                {
                    cnt[i + 1][j] += cnt[i][j - 1];
                    cnt[i + 1][j] %= MOD;
                }

                // non-remove
                for (size_t j = 0; j < MAX_N; j++)
                {
                    cnt[i + 1][j] += cnt[i][j];
                    cnt[i + 1][j] %= MOD;
                }
            }
        }

        sum = cnt[points.size()][k - es.size()];
    }

    return sum;
}

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

    int min_x = -1, max_x = -1, min_y = -1, max_y = -1;
    for (size_t i = 0; i < n; i++)
    {
        int x, y;
#if DEBUG
        inFile >> x >> y;
#else
        cin >> x >> y;
#endif

        if (0 > min_x || min_x > x)
        {
            min_x = x;
        }

        if (max_x < x)
        {
            max_x = x;
        }

        if (0 > min_y || min_y > y)
        {
            min_y = y;
        }

        if (max_y < y)
        {
            max_y = y;
        }

        points.push_back(Point(x, y));
    }

    for (size_t i = 0; i < n; i++)
    {
        if (points[i].x == min_x)
        {
            edges[0].push_back(points[i]);
        }
    }

    for (size_t i = 0; i < n; i++)
    {
        if (points[i].y == max_y)
        {
            edges[1].push_back(points[i]);
        }
    }

    for (size_t i = 0; i < n; i++)
    {
        if (points[i].x == max_x)
        {
            edges[2].push_back(points[i]);
        }
    }

    for (size_t i = 0; i < n; i++)
    {
        if (points[i].y == min_y)
        {
            edges[3].push_back(points[i]);
        }
    }

    // O[w,x,y,z]
    long long sum4 = 0;
    int tmp[4] = {0, 1, 2, 3};
    vector<int> ei(tmp, tmp + 4);
    sum4 = getSum(ei, k);
    ei.clear();

    // O[w,x,y]
    long long sum3 = 0;
    for (size_t w = 0; w < 4; w++)
    {
        ei.push_back(w);
        for (size_t x = w + 1; x < 4; x++)
        {
            ei.push_back(x);
            for (size_t y = x + 1; y < 4; y++)
            {
                ei.push_back(y);

                sum3 += getSum(ei, k);
                sum3 %= MOD;

                ei.pop_back();
            }
            ei.pop_back();
        }
        ei.pop_back();
    }

    sum3 -= 4 * sum4;
    sum3 %= MOD;
    sum3 += MOD;
    sum3 %= MOD;

    // O[w,x]
    long long sum2 = 0;
    for (size_t w = 0; w < 4; w++)
    {
        ei.push_back(w);
        for (size_t x = w + 1; x < 4; x++)
        {
            ei.push_back(x);

            sum2 += getSum(ei, k);
            sum2 %= MOD;

            ei.pop_back();
        }
        ei.pop_back();
    }

    sum2 -= 6 * sum4;
    sum2 %= MOD;
    sum2 -= 3 * sum3;
    sum2 %= MOD;
    sum2 += MOD;
    sum2 %= MOD;

    // O[w]
    long long sum1 = 0;
    for (size_t w = 0; w < 4; w++)
    {
        ei.push_back(w);

        sum1 += getSum(ei, k);
        sum1 %= MOD;

        ei.pop_back();
    }
    
    sum1 -= 4 * sum4;
    sum1 %= MOD;
    sum1 -= 3 * sum3;
    sum1 %= MOD;
    sum1 -= 2 * sum2;
    sum1 %= MOD;
    sum1 += MOD;
    sum1 %= MOD;

    long long sum = sum1 + sum2 + sum3 + sum4;
    sum %= MOD;

    cout << sum << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
