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
#define MAX_AB 100000

using namespace std;

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int n, m, q;
#if DEBUG
    inFile >> n >> m >> q;
#else
    cin >> n >> m >> q;
#endif

    vector<int> a(n);
    vector<int> b(m);

    for (size_t i = 0; i < n; i++)
    {
#if DEBUG
        inFile >> a[i];
#else
        cin >> a[i];
#endif
    }

    for (size_t i = 0; i < m; i++)
    {
#if DEBUG
        inFile >> b[i];
#else
        cin >> b[i];
#endif
    }

    for (size_t i = 0; i < q; i++)
    {
        int r1, r2, c1, c2;
#if DEBUG
        inFile >> r1 >> c1 >> r2 >> c2;
#else
        cin >> r1 >> c1 >> r2 >> c2;
#endif

        int numa[MAX_AB + 1];
        int numb[MAX_AB + 1];

        memset(numa, 0, sizeof(int) * (MAX_AB + 1));
        memset(numb, 0, sizeof(int) * (MAX_AB + 1));

        for (size_t j = r1; j <= r2; j++)
        {
            numa[a[j]]++;
        }

        for (size_t j = c1; j <= c2; j++)
        {
            numb[b[j]]++;
        }

        for (size_t j = 1; j <= MAX_AB; j++)
        {
            for (size_t k = 2 * j; k <= MAX_AB; k += j)
            {
                numa[j] += numa[k];
                numb[j] += numb[k];
            }
        }

        long long cnt[MAX_AB + 1];
        memset(cnt, 0, sizeof(long long) * (MAX_AB + 1));

        int ret = 0;
        for (size_t j = MAX_AB; j >= 1; j--)
        {
            cnt[j] = (long long)numa[j] * (long long)numb[j];
            for (size_t k = 2 * j; k <= MAX_AB; k += j)
            {
                cnt[j] -= cnt[k];
            }

            if (cnt[j])
            {
                ret++;
            }
        }

        cout << ret << endl;
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
