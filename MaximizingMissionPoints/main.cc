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

#define DEBUG 1
#define ls ch[0]
#define rs ch[1]
#define MAX_N       200000
#define MIN_POINT   -300000

struct Point
{
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
} ps[MAX_N];

bool dimension;

//比较当前维度下大小关系
bool cmpForPoint(const Point &p1, const Point &p2)
{
    if (dimension == 0)
        return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
    return p1.y < p2.y || (p1.y == p2.y && p1.x < p2.x);
}

struct kdTree
{
    kdTree *parent;
    kdTree *ch[2];
    Point p, r1, r2;        // r1, r2 是矩形的左下、右上角的坐标
    long long pPoints;       // 当前位置p 可能的最大 points
    long long maxPoints;     // r1, r2 范围内 最大的 points
    kdTree(const Point& p) : p(p), r1(p), r2(p), pPoints(MIN_POINT), maxPoints(MIN_POINT) { parent = ch[0] = ch[1] = NULL; }
    kdTree() : pPoints(MIN_POINT), maxPoints(MIN_POINT) { parent = ch[0] = ch[1] = NULL; }
    //    void *operator new(size_t) { return pit++; }
    void maintain()
    { //维护当前点覆盖的矩形
        if (ls && ls->r1.x < r1.x)
        {
            r1.x = ls->r1.x;
        }
        if (rs && rs->r1.x < r1.x)
        {
            r1.x = rs->r1.x;
        }
        
        if (ls && ls->r1.y < r1.y)
        {
            r1.y = ls->r1.y;
        }
        if (rs && rs->r1.y < r1.y)
        {
            r1.y = rs->r1.y;
        }
        
        if (ls && ls->r2.x > r2.x)
        {
            r2.x = ls->r2.x;
        }
        if (rs && rs->r2.x > r2.x)
        {
            r2.x = rs->r2.x;
        }
        
        if (ls && ls->r2.y > r2.y)
        {
            r2.y = ls->r2.y;
        }
        if (rs && rs->r2.y > r2.y)
        {
            r2.y = rs->r2.y;
        }
        
    }
} * root;

map<long long, kdTree *>pToKDTree;

kdTree *build(int l, int r, bool d)
{
    if (l >= r)
        return NULL;
    int mid = (l + r) / 2;
    dimension = d;
    nth_element(ps + l, ps + mid, ps + r, cmpForPoint); //使用中位数来使树尽量平衡
    kdTree *o = new kdTree(ps[mid]);

    long long key = (long long)ps[mid].x * 1000000 + ps[mid].y;
    pToKDTree.insert(pair<long long, kdTree *>(key, o));

    o->ls = build(l, mid, d ^ 1), o->rs = build(mid + 1, r, d ^ 1);
    if (o->ls)
    {
        o->ls->parent = o;
    }
    if (o->rs)
    {
        o->rs->parent = o;
    }
    o->maintain();
    return o;
}

class City
{
public:
    int x, y, h, p;

    City() {}

    City(int _x, int _y, int _h, int _p)
    {
        this->x = _x;
        this->y = _y;
        this->h = _h;
        this->p = _p;
    }

    City(const City &c)
    {
        this->x = c.x;
        this->y = c.y;
        this->h = c.h;
        this->p = c.p;
    }
};

// city 按照 height 排序
bool cmpForCity(const City &c1, const City &c2)
{
    return c1.h < c2.h;
}

long long findMaxInRange(const kdTree *curr, int r1x, int r1y, int r2x, int r2y)
{
    long long ret = MIN_POINT;

    if (r1x <= curr->r1.x && r1y <= curr->r1.y && r2x >= curr->r2.x && r2y >= curr->r2.y)
    {
        // curr 的区域在 r1、r2 的区域内
        ret = curr->maxPoints;
    }
    else
    {
        // curr->p 是否在范围内，它的值
        if (MIN_POINT < curr->pPoints && curr->p.x >= r1x && curr->p.y >= r1y && curr->p.x <= r2x && curr->p.y <= r2y)
        {
            ret = curr->pPoints;
        }

        if (curr->ls && MIN_POINT < curr->ls->maxPoints && curr->rs && MIN_POINT < curr->rs->maxPoints && curr->ls->maxPoints > curr->rs->maxPoints)
        {
            // curr->ls 左孩子该范围内的最大值
            if (curr->ls && MIN_POINT < curr->ls->maxPoints && ret < curr->ls->maxPoints)
            {
                int a1x = curr->ls->r1.x, a1y = curr->ls->r1.y, a2x = curr->ls->r2.x, a2y = curr->ls->r2.y, b1x = r1x, b1y = r1y, b2x = r2x, b2y = r2y;

                int cx1 = a1x > b1x ? a1x : b1x;
                int cy1 = a1y > b1y ? a1y : b1y;
                int cx2 = a2x < b2x ? a2x : b2x;
                int cy2 = a2y < b2y ? a2y : b2y;

                if (cx1 > cx2 || cy1 > cy2)
                {
                }
                else
                {
                    // 相交
                    long long tmp = findMaxInRange(curr->ls, r1x, r1y, r2x, r2y);
                    if (tmp > ret)
                    {
                        ret = tmp;
                    }
                }
            }

            // curr->rs 右孩子该范围内的最大值
            if (curr->rs && MIN_POINT < curr->rs->maxPoints && ret < curr->rs->maxPoints)
            {
                int a1x = curr->rs->r1.x, a1y = curr->rs->r1.y, a2x = curr->rs->r2.x, a2y = curr->rs->r2.y, b1x = r1x, b1y = r1y, b2x = r2x, b2y = r2y;

                int cx1 = a1x > b1x ? a1x : b1x;
                int cy1 = a1y > b1y ? a1y : b1y;
                int cx2 = a2x < b2x ? a2x : b2x;
                int cy2 = a2y < b2y ? a2y : b2y;

                if (cx1 > cx2 || cy1 > cy2)
                {
                }
                else
                {
                    // 相交
                    long long tmp = findMaxInRange(curr->rs, r1x, r1y, r2x, r2y);
                    if (tmp > ret)
                    {
                        ret = tmp;
                    }
                }
            }
        }
        else
        {
            // curr->rs 右孩子该范围内的最大值
            if (curr->rs && MIN_POINT < curr->rs->maxPoints && ret < curr->rs->maxPoints)
            {
                int a1x = curr->rs->r1.x, a1y = curr->rs->r1.y, a2x = curr->rs->r2.x, a2y = curr->rs->r2.y, b1x = r1x, b1y = r1y, b2x = r2x, b2y = r2y;

                int cx1 = a1x > b1x ? a1x : b1x;
                int cy1 = a1y > b1y ? a1y : b1y;
                int cx2 = a2x < b2x ? a2x : b2x;
                int cy2 = a2y < b2y ? a2y : b2y;

                if (cx1 > cx2 || cy1 > cy2)
                {
                }
                else
                {
                    // 相交
                    long long tmp = findMaxInRange(curr->rs, r1x, r1y, r2x, r2y);
                    if (tmp > ret)
                    {
                        ret = tmp;
                    }
                }
            }

            // curr->ls 左孩子该范围内的最大值
            if (curr->ls && MIN_POINT < curr->ls->maxPoints && ret < curr->ls->maxPoints)
            {
                int a1x = curr->ls->r1.x, a1y = curr->ls->r1.y, a2x = curr->ls->r2.x, a2y = curr->ls->r2.y, b1x = r1x, b1y = r1y, b2x = r2x, b2y = r2y;

                int cx1 = a1x > b1x ? a1x : b1x;
                int cy1 = a1y > b1y ? a1y : b1y;
                int cx2 = a2x < b2x ? a2x : b2x;
                int cy2 = a2y < b2y ? a2y : b2y;

                if (cx1 > cx2 || cy1 > cy2)
                {
                }
                else
                {
                    // 相交
                    long long tmp = findMaxInRange(curr->ls, r1x, r1y, r2x, r2y);
                    if (tmp > ret)
                    {
                        ret = tmp;
                    }
                }
            }
        }
    }

    return ret;
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int n, dlat, dlong;
#if DEBUG
    inFile >> n >> dlat >> dlong;
#else
    cin >> n >> dlat >> dlong;
#endif

    vector<City> cites(n);

    for (size_t i_n = 0; i_n < n; i_n++)
    {
        int latde, londe, height, points;
#if DEBUG
        inFile >> latde >> londe >> height >> points;
#else
        cin >> latde >> londe >> height >> points;
#endif

        cites[i_n].x = latde;
        cites[i_n].y = londe;
        cites[i_n].h = height;
        cites[i_n].p = points;

        ps[i_n].x = latde;
        ps[i_n].y = londe;
    }

    root = build(0, n, 0);

    // sort city by height
    sort(cites.begin(), cites.end(), cmpForCity);

    for (vector<City>::iterator it = cites.begin(); it != cites.end(); it++)
    {
        // 找到 可以跳转到该city 最大的points
        long long max = 0;
        if (MIN_POINT < root->maxPoints)
        {
            max = findMaxInRange(root, it->x - dlat, it->y - dlong, it->x + dlat, it->y + dlong);
        }

        if (0 <= max)
        {
            max += it->p;
        }
        else
        {
            max = it->p;
        }

        // 更新 kd-tree 中对应的 points
        long long key = (long long)(it->x) * 1000000 + it->y;
        map<long long, kdTree *>::iterator mp_it = pToKDTree.find(key);
        if (mp_it != pToKDTree.end())
        {
            kdTree * curr = mp_it->second;
            curr->pPoints = max;

            while (curr)
            {
                if (max > curr->maxPoints)
                {
                    curr->maxPoints = max;
                    curr = curr->parent;
                }
                else
                {
                    break;
                }
            }
        }
    }

    cout << root->maxPoints << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
