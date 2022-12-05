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

const int k = 3;
const int a = 0;
const int b = 1;
const int d = 2;

class Pair
{
    public:
        int v[k];   // v[a][b][distance]
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

Pair *buildKDTree(vector<Pair>::iterator ps, int ps_size, int curr_level)
{
    Pair * ret = NULL;

    int mid_idx = ps_size / 2;
    if (0 > curr_level || 0 == curr_level % k)
    {
        nth_element(ps, ps + mid_idx, ps + ps_size, cmpA);
    }
    else if (1 == curr_level % k)
    {
        nth_element(ps, ps + mid_idx, ps + ps_size, cmpB);
    }
    else
    {
        // 2 == curr_level % k
        nth_element(ps, ps + mid_idx, ps + ps_size, cmpD);
    }

    ret = &(*(ps + mid_idx));

    if (0 < mid_idx)
    {
        // left
        ret->left = buildKDTree(ps, mid_idx, curr_level + 1);
    }

    if (mid_idx + 1 < ps_size)
    {
        // right
        ret->right = buildKDTree(ps + mid_idx + 1, ps_size - mid_idx - 1, curr_level + 1);
    }

    return ret;
}

bool havePair(Pair * root, Pair &p)
{
    bool ret = false;

    return ret;
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

    vector<int> dists;
    multimap<int, Pair> pairInDis;

    int idx = -1;
    for (vector<Pair>::iterator it = pairs.begin(); it != pairs.end(); it ++)
    {
        if (0 > idx || dists[idx] != (*it).v[d])
        {
            dists.push_back((*it).v[d]);
            idx ++;
        }

        pairInDis.insert(pair<int, Pair>((*it).v[d], *it));
    }

    // build kd-tree
    Pair * root = NULL;
    root = buildKDTree(pairs.begin(), pairs.size(), -1);

    // find max distance
    int max_dist = 0;

    int low = 0, high = dists.size() - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        int mid_dist = dists[mid];

        auto it = pairInDis.equal_range(mid_dist);
        auto itr = it.first;
        while (itr != it.second)
        {
            if (havePair(root, itr->second))
            {
                max_dist = itr->first;
                break;
            }

            itr ++;
        }

        if (itr == it.second)
        {
            // no found, try lower distance
            high = mid - 1;
        }
        else
        {
            // found, try higher distance
            low = mid + 1;
        }
    }

    cout << max_dist << endl;
    
    return 0;
}
