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

vector<unsigned int> pa;
vector<unsigned int> costs;
vector<unsigned long long> csizes;

unsigned int index(vector<unsigned int> &weights, unsigned int w)
{
    unsigned int wsize = weights.size();
    if (w > weights[wsize - 1])
    {
        return wsize - 1;
    }
    else
    {
        vector<unsigned int>::iterator it = lower_bound(weights.begin(), weights.end(), w);
        if (*it == w)
        {
            return it - weights.begin();
        }
        else
        {
            return it - weights.begin() - 1;
        }
    }
}

unsigned int find(unsigned int x)
{
    return pa[x] == x ? x : pa[x] = find(pa[x]);
}

// set x => set y
void unite(unsigned int x, unsigned int y)
{
    pa[find(x)] = find(y);
}

class Road
{
public:
    unsigned int u, v, w;

    Road()
    {
        u = v = w = 0;
    }
};

bool cmp(Road &a, Road &b)
{
    return a.w < b.w;
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    unsigned int n, q;
#if DEBUG
    inFile >> n >> q;
#else
    cin >> n >> q;
#endif

    // init
    pa.resize(n + 1);
    costs.resize(n + 1);
    csizes.resize(n + 1);
    iota(pa.begin(), pa.end(), 0);

    vector<Road> roads(n - 1);
    vector<unsigned int> weights(n - 1);

    for (size_t i = 0; i < n - 1; i++)
    {
#if DEBUG
        inFile >> roads[i].u >> roads[i].v >> roads[i].w;
#else
        cin >> roads[i].u >> roads[i].v >> roads[i].w;
#endif

        weights[i] = roads[i].w;
    }

    // sort
    sort(roads.begin(), roads.end(), cmp);
    sort(weights.begin(), weights.end());
    weights.erase(unique(weights.begin(), weights.end()), weights.end());

    vector<unsigned long long> cnts(weights.size(), 0);

    for (size_t i = 0; i < n - 1; i++)
    {
        unsigned int pau = find(roads[i].u);
        unsigned int pav = find(roads[i].v);
        unsigned int cost = roads[i].w;

        // pau -> pav
        if (csizes[pav] < csizes[pau])
        {
            swap(pau, pav);
        }
        unite(pau, pav);

        unsigned int idx = index(weights, cost);

        cnts[idx] += 1 + csizes[pau] + csizes[pav] + csizes[pau] * csizes[pav];
        csizes[pav] += csizes[pau] + 1;
    }

    for (size_t i = 0; i < q; i++)
    {
        unsigned int l, r;
#if DEBUG
        inFile >> l >> r;
#else
        cin >> l >> r;
#endif

        unsigned int idxl, idxr;
        idxl = index(weights, l);
        idxr = index(weights, r);

        unsigned long long out = 0;
        for (size_t j = idxl; j <= idxr; j++)
        {
            out += cnts[j];
        }

        cout << out << endl;
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
