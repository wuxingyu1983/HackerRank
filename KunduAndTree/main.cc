#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

#define DEBUG   0
#define MOD     1000000007

int getRoot(vector<int> &id, int i)
{
    while (i != id[i])
    {
        // path compression
        id[i] = id[id[i]];
        i = id[i];
    }
    return i;
}

void union_func(vector<int> &id, vector<long long> &sz, int p, int q)
{
    int rootP = getRoot(id, p);
    int rootQ = getRoot(id, q);

    if (rootP != rootQ)
    {
        // weighted quick union
        if (sz[rootP] >= sz[rootQ])
        {
            id[rootQ] = rootP;
            sz[rootP] += sz[rootQ];
            sz[rootQ] = 1;
        }
        else
        {
            id[rootP] = rootQ;
            sz[rootQ] += sz[rootP];
            sz[rootP] = 1;
        }
    }
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    long long n;
#if DEBUG
    inFile >> n;
#else
    cin >> n;
#endif

    long long sum = 0;

    if (3 < n)
    {
        vector<int> id(n + 1);
        vector<long long> sz(n + 1);

        for (size_t i = 1; i <= n; i++)
        {
            id[i] = i;
            sz[i] = 1;
        }

        sum = n * (n - 1) * (n - 2) / 6;
        sum %= MOD;

        for (size_t i = 1; i < n; i++)
        {
            int x, y;
            char color;

#if DEBUG
            inFile >> x >> y >> color;
#else
            cin >> x >> y >> color;
#endif

            if ('b' == color)
            {
                union_func(id, sz, x, y);
            }
        }

        for (size_t i = 1; i <= n; i++)
        {
            if (1 < sz[i])
            {
                long long tmp = 0;

                if (2 < sz[i])
                {
                    tmp = sz[i] * (sz[i] - 1) * (sz[i] - 2) / 6;
                    tmp %= MOD;

                    sum += MOD;
                    sum -= tmp;

                    sum %= MOD;
                }

                tmp = sz[i] * (sz[i] - 1) / 2;
                tmp *= (n - sz[i]);
                tmp %= MOD;

                sum += MOD;
                sum -= tmp;

                sum %= MOD;
            }
        }
    }

    cout << sum << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
