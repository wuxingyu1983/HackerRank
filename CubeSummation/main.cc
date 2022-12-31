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

const int K = 3;
const int X = 0;
const int Y = 1;
const int Z = 2;

class Box
{
public:
    int lower[K];
    int upper[K];
    Box() {}
};

class Point
{
public:
    int v[K]; // v[x][y][z]
    unsigned long long w;
    unsigned long long sum;
    Point *left, *right, *parent;

    // box
    Box range;

    Point() {}
    Point(int _x, int _y, int _z)
    {
        v[X] = _x;
        v[Y] = _y;
        v[Z] = _z;
        w = sum = 0;

        left = right = parent = NULL;

        range.lower[X] = range.upper[X] = v[X];
        range.lower[Y] = range.upper[Y] = v[Y];
        range.lower[Z] = range.upper[Z] = v[Z];
    }
};

bool cmpX(const Point &a, const Point &b)
{
    return a.v[X] < b.v[X];
}

bool cmpY(const Point &a, const Point &b)
{
    return a.v[Y] < b.v[Y];
}

bool cmpZ(const Point &a, const Point &b)
{
    return a.v[Z] < b.v[Z];
}

Point *buildKDTree(vector<Point>::iterator ps, int ps_size, int curr_level)
{
    Point *ret = NULL;

    int mid_idx = ps_size / 2;
    if (0 > curr_level || 0 == curr_level % K)
    {
        nth_element(ps, ps + mid_idx, ps + ps_size, cmpX);
    }
    else if (1 == curr_level % K)
    {
        nth_element(ps, ps + mid_idx, ps + ps_size, cmpY);
    }
    else
    {
        // 2 == curr_level % k
        nth_element(ps, ps + mid_idx, ps + ps_size, cmpZ);
    }

    ret = &(*(ps + mid_idx));

    if (0 < mid_idx)
    {
        // left
        ret->left = buildKDTree(ps, mid_idx, curr_level + 1);
        ret->left->parent = ret;

        if (ret->range.lower[X] > ret->left->range.lower[X])
        {
            ret->range.lower[X] = ret->left->range.lower[X];
        }

        if (ret->range.upper[X] < ret->left->range.upper[X])
        {
            ret->range.upper[X] = ret->left->range.upper[X];
        }

        if (ret->range.lower[Y] > ret->left->range.lower[Y])
        {
            ret->range.lower[Y] = ret->left->range.lower[Y];
        }

        if (ret->range.upper[Y] < ret->left->range.upper[Y])
        {
            ret->range.upper[Y] = ret->left->range.upper[Y];
        }

        if (ret->range.lower[Z] > ret->left->range.lower[Z])
        {
            ret->range.lower[Z] = ret->left->range.lower[Z];
        }

        if (ret->range.upper[Z] < ret->left->range.upper[Z])
        {
            ret->range.upper[Z] = ret->left->range.upper[Z];
        }
    }

    if (mid_idx + 1 < ps_size)
    {
        // right
        ret->right = buildKDTree(ps + mid_idx + 1, ps_size - mid_idx - 1, curr_level + 1);
        ret->right->parent = ret;

        if (ret->range.lower[X] > ret->right->range.lower[X])
        {
            ret->range.lower[X] = ret->right->range.lower[X];
        }

        if (ret->range.upper[X] < ret->right->range.upper[X])
        {
            ret->range.upper[X] = ret->right->range.upper[X];
        }

        if (ret->range.lower[Y] > ret->right->range.lower[Y])
        {
            ret->range.lower[Y] = ret->right->range.lower[Y];
        }

        if (ret->range.upper[Y] < ret->right->range.upper[Y])
        {
            ret->range.upper[Y] = ret->right->range.upper[Y];
        }

        if (ret->range.lower[Z] > ret->right->range.lower[Z])
        {
            ret->range.lower[Z] = ret->right->range.lower[Z];
        }

        if (ret->range.upper[Z] < ret->right->range.upper[Z])
        {
            ret->range.upper[Z] = ret->right->range.upper[Z];
        }
    }

    return ret;
}

class Operation
{
public:
    string op;

    // update
    int x, y, z;
    unsigned long long w;

    // query
    int x1, y1, z1, x2, y2, z2;

    Operation() {}
};

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

    for (size_t i_t = 0; i_t < t; i_t++)
    {
        int n, m;
#if DEBUG
        inFile >> n >> m;
#else
        cin >> n >> m;
#endif

        vector<Operation> ops;
        vector<Point> points;
        unsigned char flags[101][101][101];

        memset(flags, 0, 101*101*101);

        for (size_t i_m = 0; i_m < m; i_m++)
        {
            Operation op;

#if DEBUG
            inFile >> op.op;
#else
            cin >> op.op;
#endif

            if (op.op == "UPDATE")
            {
#if DEBUG
                inFile >> op.x >> op.y >> op.z >> op.w;
#else
                cin >> op.x >> op.y >> op.z >> op.w;
#endif
                if (0 == flags[op.x][op.y][op.z])
                {
                    points.push_back(Point(op.x, op.y, op.z));
                    flags[op.x][op.y][op.z] = 1;
                }
            }
            else
            {
#if DEBUG
                inFile >> op.x1 >> op.y1 >> op.z1 >> op.x2 >> op.y2 >> op.z2;
#else
                cin >> op.x1 >> op.y1 >> op.z1 >> op.x2 >> op.y2 >> op.z2;
#endif
            }

            ops.push_back(op);
        }

        // build kd-tree
        Point *root = NULL;
        root = buildKDTree(points.begin(), points.size(), 0);
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
