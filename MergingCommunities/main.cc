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

#define DEBUG 0

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

void union_func(vector<int> &id, vector<int> &sz, int p, int q)
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
        }
        else
        {
            id[rootP] = rootQ;
            sz[rootQ] += sz[rootP];
        }
    }
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int n, q;
#if DEBUG
    inFile >> n >> q;
#else
    cin >> n >> q;
#endif

    vector<int> sz(n + 1);
    vector<int> id(n + 1);

    for (size_t i = 0; i <= n; i++)
    {
        sz[i] = 1;
        id[i] = i;
    }

    for (size_t i = 0; i < q; i++)
    {
        char op;
        int fst, snd;
#if DEBUG
        inFile >> op;
#else
        cin >> op;
#endif

        if ('M' == op)
        {
#if DEBUG
            inFile >> fst >> snd;
#else
            cin >> fst >> snd;
#endif

            union_func(id, sz, fst, snd);
        }
        else
        {
// Q
#if DEBUG
            inFile >> fst;
#else
            cin >> fst;
#endif

            cout << sz[getRoot(id, fst)] << endl;
        }
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
