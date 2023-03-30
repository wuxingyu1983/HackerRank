#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <numeric>

using namespace std;

#define DEBUG       0
#define MAX_N       200002
#define MAX_M       100002

// segment tree
vector<unsigned long long> covers(MAX_N * 4);
vector<unsigned long long> lazycovers(MAX_N * 4);
vector<unsigned long long> coversidxes(MAX_N * 4);
vector<unsigned long long> lazycoversidxes(MAX_N * 4);

void update(vector<unsigned long long>& d, vector<unsigned long long>& b, int l, int r, unsigned long long c, int s, int t, int p)
{
    if (l <= s && t <= r)
    {
        d[p] += (t - s + 1) * c, b[p] += c;
        return;
    }
    int m = s + ((t - s) >> 1);
    if (b[p] && s != t)
    {
        d[p * 2] += b[p] * (m - s + 1), d[p * 2 + 1] += b[p] * (t - m);
        b[p * 2] += b[p], b[p * 2 + 1] += b[p];
        b[p] = 0;
    }
    if (l <= m)
        update(d, b, l, r, c, s, m, p * 2);
    if (r > m)
        update(d, b, l, r, c, m + 1, t, p * 2 + 1);
    d[p] = d[p * 2] + d[p * 2 + 1];
}

unsigned long long getsum(vector<unsigned long long>& d, vector<unsigned long long>& b, int l, int r, int s, int t, int p)
{
    if (l <= s && t <= r)
        return d[p];
    int m = s + ((t - s) >> 1);
    if (b[p])
    {
        d[p * 2] += b[p] * (m - s + 1), d[p * 2 + 1] += b[p] * (t - m);
        b[p * 2] += b[p], b[p * 2 + 1] += b[p];
        b[p] = 0;
    }
    unsigned long long sum = 0;
    if (l <= m)
        sum = getsum(d, b, l, r, s, m, p * 2);
    if (r > m)
        sum += getsum(d, b, l, r, m + 1, t, p * 2 + 1);
    return sum;
}

class Town
{
public:
    unsigned int p, x;

    Town()
    {
        p = x = 0;
    }
};

class Cloud
{
public:
    unsigned int y, r;

    Cloud()
    {
        y = r = 0;
    }
};

vector<Town> towns(MAX_N);
vector<Cloud> clouds(MAX_M);

bool comp(Town &a, Town &b)
{
    return (a.x < b.x);
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int n;
#if DEBUG
    inFile >> n;
#else
    cin >> n;
#endif

    for (size_t i = 1; i <= n; i++)
    {
#if DEBUG
    inFile >> towns[i].p;
#else
    cin >> towns[i].p;
#endif
    }

    vector<int> xs(n + 1, 0);

    for (size_t i = 1; i <= n; i++)
    {
#if DEBUG
    inFile >> towns[i].x;
#else
    cin >> towns[i].x;
#endif
        xs[i] = towns[i].x;
    }

    int m;
#if DEBUG
    inFile >> m;
#else
    cin >> m;
#endif

    for (size_t i = 1; i <= m; i++)
    {
#if DEBUG
    inFile >> clouds[i].y;
#else
    cin >> clouds[i].y;
#endif
    }

    for (size_t i = 1; i <= m; i++)
    {
#if DEBUG
    inFile >> clouds[i].r;
#else
    cin >> clouds[i].r;
#endif
    }

    // sort cities
    sort(towns.begin() + 1, towns.begin() + n + 1, comp);
    sort(xs.begin() + 1, xs.end());

    // init segment trees
    // all 0, do nothing

    // update segment trees
    for (size_t i = 1; i <= m; i++)
    {
        int left = clouds[i].y - clouds[i].r;
        int right = clouds[i].y + clouds[i].r;

        // find towns in [left, right]
        // >= left
        vector<int>::iterator low;
        low = lower_bound(xs.begin(), xs.end(), left);
        if (low != xs.end())
        {
            // > right
            vector<int>::iterator up;
            up = upper_bound(xs.begin(), xs.end(), right);
            
            {
                int idx_left = low - xs.begin();
                int idx_right = up - xs.begin() - 1;
                
                if (idx_left <= idx_right && 0 < idx_right)
                {
                    update(covers, lazycovers, idx_left, idx_right, 1, 1, n, 1);
                    update(coversidxes, lazycoversidxes, idx_left, idx_right, i, 1, n, 1);
                }
            }
        }
    }

    unsigned long long sunny = 0;
    unsigned long long cloudy = 0;

    unsigned long long pre_idx = 0;
    unsigned long long pre_cloudy = 0;

    for (size_t i = 1; i <= n; i++)
    {
        unsigned long long flag = getsum(covers, lazycovers, i, i, 1, n, 1);
        if (0 == flag)
        {
            sunny += towns[i].p;
        }
        else
        {
            if (1 == flag)
            {
                // only one cloud
                unsigned long long idx = getsum(coversidxes, lazycoversidxes, i, i, 1, n, 1);
                if (idx == pre_idx)
                {
                    pre_cloudy += towns[i].p;
                }
                else
                {
                    if (pre_cloudy > cloudy)
                    {
                        cloudy = pre_cloudy;
                    }

                    pre_cloudy = towns[i].p;
                    pre_idx = idx;
                }
            }
        }
    }

    if (pre_cloudy > cloudy)
    {
        cloudy = pre_cloudy;
    }

    cout << sunny + cloudy << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
