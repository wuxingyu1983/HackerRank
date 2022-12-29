#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#define DEBUG 0
#define MOD 1000000007

class City
{
public:
    unsigned long long c;
    unsigned long long p;

    unsigned int idx_c;

    City() {}
};

bool cmp_c(City &a, City &b)
{
    bool ret = false;

    if (a.c < b.c)
    {
        ret = true;
    }
    else if (a.c == b.c)
    {
        if (a.p < b.p)
        {
            ret = true;
        }
    }

    return ret;
}

bool cmp_p(City &a, City &b)
{
    bool ret = false;

    if (a.p < b.p)
    {
        ret = true;
    }
    else if (a.p == b.p)
    {
        if (a.c < b.c)
        {
            ret = true;
        }
    }

    return ret;
}

void update(vector<unsigned long long> &d, vector<unsigned char> &b, int l, int r, int c, int s, int t, int p)
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

unsigned long long getsum(vector<unsigned long long> &d, vector<unsigned char> &b, int l, int r, int s, int t, int p)
{
  if (l <= s && t <= r) return d[p];
  int m = s + ((t - s) >> 1);
  if (b[p]) {
    d[p * 2] += b[p] * (m - s + 1), d[p * 2 + 1] += b[p] * (t - m);
    b[p * 2] += b[p], b[p * 2 + 1] += b[p];
    b[p] = 0;
  }
  unsigned long long sum = 0;
  if (l <= m) sum = getsum(d, b, l, r, s, m, p * 2);
  if (r > m) sum += getsum(d, b, l, r, m + 1, t, p * 2 + 1);
  return sum;
}

vector<City> cities;

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
#endif

    for (size_t i = 0; i < t; i++)
    {
        int n;
#if DEBUG
        inFile >> n;
#else
        cin >> n;
#endif

        unsigned long long cs[n];
        unsigned long long ps[n];

        for (size_t j = 0; j < n; j++)
        {
#if DEBUG
            inFile >> cs[j];
#else
            cin >> cs[j];
#endif
        }

        for (size_t j = 0; j < n; j++)
        {
#if DEBUG
            inFile >> ps[j];
#else
            cin >> ps[j];
#endif
        }

        cities.clear();

        for (size_t j = 0; j < n; j++)
        {
            City city;
            city.c = cs[j];
            city.p = ps[j];

            cities.push_back(city);
        }

        // sort by c
        sort(cities.begin(), cities.end(), cmp_c);
        for (size_t j = 0; j < n; j++)
        {
            cities[j].idx_c = j;
        }

        unsigned int size = ceil(log((double)n) / log(2.0));
        size = pow(2, size + 1);

        vector<unsigned long long> flags_c(size + 1, 0);
        vector<unsigned char> lazy_c(size + 1, 0);
        vector<unsigned long long> flags_p(size + 1, 0);
        vector<unsigned char> lazy_p(size + 1, 0);

        // sort by p
        sort(cities.begin(), cities.end(), cmp_p);

        unsigned long long cnt = 0;

        for (size_t j = 0; j < n; j++)
        {
            if (0 < j)
            {
                unsigned long long cs_left = getsum(flags_c, lazy_c, 1, cities[j].idx_c + 1, 1, n, 1);
                unsigned long long ps_left = getsum(flags_p, lazy_p, 1, cities[j].idx_c + 1, 1, n, 1);
                unsigned long long cs_right = getsum(flags_c, lazy_c, cities[j].idx_c + 1, n, 1, n, 1);
                unsigned long long ps_right = getsum(flags_p, lazy_p, cities[j].idx_c + 1, n, 1, n, 1);

                cnt += (cs_left * cities[j].c - ps_left) * cities[j].p % MOD;
                cnt += (ps_right - cs_right * cities[j].c) * cities[j].p % MOD;
                cnt %= MOD;
            }

            update(flags_c, lazy_c, cities[j].idx_c + 1, cities[j].idx_c + 1, 1, 1, n, 1);
            update(flags_p, lazy_p, cities[j].idx_c + 1, cities[j].idx_c + 1, cities[j].c, 1, n, 1);
        }

        cout << cnt << endl;
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
