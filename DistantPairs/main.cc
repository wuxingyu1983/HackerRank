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
int c;

class Box
{
public:
    int lower[k];
    int upper[k];
    Box() {}
};

class Pair
{
public:
    int v[k]; // v[a][b][distance]
    Pair *left, *right;

    // box
    Box range;

    Pair() {}
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

        range.lower[a] = range.upper[a] = v[a];
        range.lower[b] = range.upper[b] = v[b];
        range.lower[d] = range.upper[d] = v[d];
    }
};

bool cmpA(const Pair &x, const Pair &y)
{
    return x.v[a] < y.v[a];
}

bool cmpB(const Pair &x, const Pair &y)
{
    return x.v[b] < y.v[b];
}

bool cmpD(const Pair &x, const Pair &y)
{
    return x.v[d] < y.v[d];
}

Pair *buildKDTree(vector<Pair>::iterator ps, int ps_size, int curr_level)
{
    Pair *ret = NULL;

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

        if (ret->range.lower[a] > ret->left->range.lower[a])
        {
            ret->range.lower[a] = ret->left->range.lower[a];
        }

        if (ret->range.upper[a] < ret->left->range.upper[a])
        {
            ret->range.upper[a] = ret->left->range.upper[a];
        }

        if (ret->range.lower[b] > ret->left->range.lower[b])
        {
            ret->range.lower[b] = ret->left->range.lower[b];
        }

        if (ret->range.upper[b] < ret->left->range.upper[b])
        {
            ret->range.upper[b] = ret->left->range.upper[b];
        }

        if (ret->range.lower[d] > ret->left->range.lower[d])
        {
            ret->range.lower[d] = ret->left->range.lower[d];
        }

        if (ret->range.upper[d] < ret->left->range.upper[d])
        {
            ret->range.upper[d] = ret->left->range.upper[d];
        }
    }

    if (mid_idx + 1 < ps_size)
    {
        // right
        ret->right = buildKDTree(ps + mid_idx + 1, ps_size - mid_idx - 1, curr_level + 1);

        if (ret->range.lower[a] > ret->right->range.lower[a])
        {
            ret->range.lower[a] = ret->right->range.lower[a];
        }

        if (ret->range.upper[a] < ret->right->range.upper[a])
        {
            ret->range.upper[a] = ret->right->range.upper[a];
        }

        if (ret->range.lower[b] > ret->right->range.lower[b])
        {
            ret->range.lower[b] = ret->right->range.lower[b];
        }

        if (ret->range.upper[b] < ret->right->range.upper[b])
        {
            ret->range.upper[b] = ret->right->range.upper[b];
        }

        if (ret->range.lower[d] > ret->right->range.lower[d])
        {
            ret->range.lower[d] = ret->right->range.lower[d];
        }

        if (ret->range.upper[d] < ret->right->range.upper[d])
        {
            ret->range.upper[d] = ret->right->range.upper[d];
        }
    }

    return ret;
}

// intersection -- 1, 2
// target contain subtree -- 3
// not -- 0
int isIntersection(Box &target, Box &subtree)
{
    int ret = 0;

    for (size_t i = 0; i < k; i++)
    {
        if (target.lower[i] > subtree.upper[i] || target.upper[i] < subtree.lower[i])
        {
            // not
            ret = 0;
            return ret;
        }
        else
        {
            if (target.lower[i] <= subtree.lower[i] && target.upper[i] >= subtree.upper[i])
            {
                ret++;
            }
        }
    }

    if (3 != ret)
    {
        ret = 1;
    }

    return ret;
}

bool pairInBox(Pair *parent, Box &box)
{
    bool ret = false;

    if (parent)
    {
        // parent self
        int i = 0;
        for (i = 0; i < k; i++)
        {
            if (parent->v[i] < box.lower[i] || parent->v[i] > box.upper[i])
            {
                break;
            }
        }

        if (k == i)
        {
            ret = true;
            return ret;
        }

        int iRet = isIntersection(box, parent->range);
        if (3 == iRet)
        {
            // subtree parent in box
            ret = true;
        }
        else if (0 == iRet)
        {
            // subtree parent not in box
        }
        else
        {
            // intersection
            if (parent->left)
            {
                ret = pairInBox(parent->left, box);
            }

            if (false == ret && parent->right)
            {
                ret = pairInBox(parent->right, box);
            }
        }
    }

    return ret;
}

bool havePair(Pair *root, Pair &p, int dist)
{
    bool ret = false;

    vector<vector<int>> areas;

    // area 0
    {
        if (p.v[a] + dist <= p.v[b] - dist)
        {
            areas.push_back({p.v[a] + dist, p.v[b] - dist});
        }
    }

    // area 1
    {
        if (p.v[a] - dist >= 0)
        {
            if (p.v[b] + dist < c)
            {
                // area 1.1.1
                areas.push_back({p.v[b] + dist, c - 1});
                areas.push_back({0, p.v[a] - dist});
            }
            else
            {
                if ((p.v[b] + dist) % c <= p.v[a] - dist)
                {
                    // area 1.1.2
                    areas.push_back({(p.v[b] + dist) % c, p.v[a] - dist});
                }
            }
        }
        else
        {
            // < 0
            // area 1.2
            if (p.v[b] + dist <= (p.v[a] - dist + c) % c)
            {
                areas.push_back({p.v[b] + dist, (p.v[a] - dist + c) % c});
            }
        }
    }

    for (vector<vector<int>>::iterator it = areas.begin(); it != areas.end(); it++)
    {
        // 2 points both in *it
        {
            Box box;
            box.lower[a] = (*it)[0];
            box.upper[a] = (*it)[1];
            box.lower[b] = (*it)[0];
            box.upper[b] = (*it)[1];
            box.lower[d] = dist;
            box.upper[d] = c;

            ret = pairInBox(root, box);
            if (ret)
            {
                return ret;
            }
        }

        for (vector<vector<int>>::iterator itr = it + 1; itr != areas.end(); itr++)
        {
            // 1 point in *it, 1 point in *itr
            Box box;
            box.lower[a] = (*it)[0];
            box.upper[a] = (*it)[1];
            box.lower[b] = (*itr)[0];
            box.upper[b] = (*itr)[1];
            box.lower[d] = dist;
            box.upper[d] = c;

            ret = pairInBox(root, box);
            if (ret)
            {
                return ret;
            }

            box.lower[a] = (*itr)[0];
            box.upper[a] = (*itr)[1];
            box.lower[b] = (*it)[0];
            box.upper[b] = (*it)[1];

            ret = pairInBox(root, box);
            if (ret)
            {
                return ret;
            }
        }
    }

    return ret;
}

int main()
{
    int n;

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

    vector<Pair> tree(pairs);

    // build kd-tree
    Pair *root = NULL;
    root = buildKDTree(tree.begin(), tree.size(), 0);

    // find max distance
    int max_dist = 0;

    int low = 0, high = pairs[pairs.size() - 1].v[d];
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        Pair midInPairs;
        midInPairs.v[d] = mid;

        vector<Pair>::iterator it = lower_bound(pairs.begin(), pairs.end(), midInPairs, cmpD);

        while (it != pairs.end())
        {
            if (havePair(root, *it, mid))
            {
                max_dist = mid;
                break;
            }

            it++;
        }

        if (it == pairs.end())
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
