#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#define DEBUG 0

const int k = 3;
const int a = 0;
const int b = 1;
const int d = 2;

class Pair
{
    public:
        int v[k];
        Pair * left, * right;

        Pair(int _a, int _b, int _c)
        {
            if (_a < _b)
            {
                v[a] = _a;
                v[b] = _b;
            }
            else
            {
                v[a] = _b;
                v[b] = _a;
            }

            v[d] = min(abs(_a - _b), _c - abs(_a - _b));

            left = right = NULL;
        }
};

bool cmpA(Pair &x, Pair &y)
{
    return x.v[a] < y.v[a];
}

bool cmpB(Pair &x, Pair &y)
{
    return x.v[b] < y.v[b];
}

bool cmpD(Pair &x, Pair &y)
{
    return x.v[d] < y.v[d];
}

int main()
{
    int n, c;

#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

#if DEBUG
    inFile >> n >> c;
#else
    cin >> n >> c;
#endif

    vector<Pair> pairs;

    for (size_t i = 0; i < n; i++)
    {
        int _a, _b;
#if DEBUG
        inFile >> _a >> _b;
#else
        cin >> _a >> _b;
#endif

        pairs.push_back(Pair(_a, _b, c));
    }

    // sort by d(distance)
    sort(pairs.begin(), pairs.end(), cmpD);

    vector<int> distances;
    
    
    return 0;
}
