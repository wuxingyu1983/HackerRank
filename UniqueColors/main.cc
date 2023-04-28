// https://www.hackerrank.com/challenges/unique-colors/problem?isFullScreen=false
// Virtual Tree : https://oi-wiki.org/graph/virtual-tree/
// Segment Tree : https://oi-wiki.org/ds/seg/

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
#include <queue>
#include <stack>

using namespace std;

#define DEBUG   0
#define MAX_N   100002
//#define MAX_N   12

int n;
unsigned int colors[MAX_N];     // color count
unsigned int nodes[MAX_N];      // color c in node[i]
vector< vector<unsigned int> > roads(MAX_N);
int sz[MAX_N];
int sum[MAX_N];

unsigned int dfsPath[MAX_N];
long long sumNode[MAX_N];       // sum for node

vector<long long> sumPath(MAX_N * 4);        // sum for dfs path, segment tree
vector<long long> sumPathLazy(MAX_N * 4);

int szOuterColor[MAX_N];   // outer size for color c

// segment tree functions
void update(vector<long long>& d, vector<long long>& b, int l, int r, long c, int s, int t, int p)
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

long long getSum(vector<long long>& d, vector<long long>& b, int l, int r, int s, int t, int p)
{
    if (l <= s && t <= r)
        return d[p];
    int m = s + ((t - s) >> 1);
    if (b[p])
    {
        d[p * 2] += b[p] * (m - s + 1), d[p * 2 + 1] += b[p] * (t - m);
        b[p * 2] += b[p], b[p * 2 + 1] += b[p];
        b[p] = 0;
    }
    long long sum = 0;
    if (l <= m)
        sum = getSum(d, b, l, r, s, m, p * 2);
    if (r > m)
        sum += getSum(d, b, l, r, m + 1, t, p * 2 + 1);
    return sum;
}

// init
int init(const unsigned int idx, const unsigned int parent, unsigned int &idxInDfs)
{
    sz[idx] = 1;
    dfsPath[idxInDfs] = idx;
    idxInDfs ++;

    int all = 0;
    for (vector<unsigned int>::iterator it = roads[idx].begin(); it != roads[idx].end(); it ++)
    {
        if (parent != *it)
        {
            int last = sum[nodes[idx]];
            sz[idx] += init(*it, idx, idxInDfs);
            int add = sum[nodes[idx]] - last;
            all += sz[*it] - add;
        }
    }
    sum[nodes[idx]] += all + 1;

    return sz[idx];
}

void coloring(const unsigned int c, const unsigned int idxInDfs, const int szInner, long long offset)
{
    unsigned int idx = idxInDfs;
    unsigned int pre = idx;
    int szCpy = szInner;

    while (0 < szCpy)
    {
        if (c == nodes[dfsPath[idx]])
        {
            if (pre != idx)
            {
                update(sumPath, sumPathLazy, pre, idx - 1, offset, 1, n, 1);
            }
            idx += sz[dfsPath[idx]];
            pre = idx;
        }
        else
        {
            idx ++;
            szCpy --;
        }
    }

    if (pre != idx)
    {
        update(sumPath, sumPathLazy, pre, idx - 1, offset, 1, n, 1);
    }
}

int func(const unsigned int idx, const unsigned int parent, unsigned int &idxInDfs)
{
    unsigned int idxCpy = idxInDfs;
    idxInDfs ++;
    sz[idx] = 1;
    
    if (0 < szOuterColor[nodes[idx]])
    {
        update(sumPath, sumPathLazy, idxCpy, idxCpy, szOuterColor[nodes[idx]], 1, n, 1);
    }

    int all = 0;
    for (vector<unsigned int>::iterator it = roads[idx].begin(); it != roads[idx].end(); it ++)
    {
        if (parent != *it)
        {
            int last = sum[nodes[idx]];
            sz[idx] += func(*it, idx, idxInDfs);
            int add = sum[nodes[idx]] - last;

            int szInnerColor = sz[*it] - add;

            long long tmp = 0;
            if (0 < szOuterColor[nodes[idx]])
            {
                tmp = szOuterColor[nodes[idx]] - (szInnerColor);
            }
            else
            {
                tmp -= szInnerColor;
            }

            coloring(nodes[idx], idxCpy + 1, szInnerColor, tmp);

            idxCpy += sz[*it];

            all += szInnerColor;
        }
    }
    sum[nodes[idx]] += all + 1;

    return sz[idx];
}

int main()
{
#if DEBUG
//    FILE *fp = fopen("/Users/wuxingyu/Downloads/input02.txt", "r");
    FILE *fp = fopen("input.txt", "r");
#endif

#if DEBUG
    fscanf(fp, "%d", &n);
#else
    scanf("%d", &n);
#endif

    long long colorCnt = 0;
    for (size_t i = 1; i <= n; i++)
    {
        unsigned int c;
#if DEBUG
        fscanf(fp, "%u", &c);
#else
        scanf("%u", &c);
#endif
        if (0 == colors[c])
        {
            colorCnt ++;
        }
        colors[c] ++;
        nodes[i] = c;
    }

    for (size_t i = 1; i < n; i++)
    {
        unsigned int a, b;
#if DEBUG
        fscanf(fp, "%u %u", &a, &b);
#else
        scanf("%u %u", &a, &b);
#endif
        roads[a].push_back(b);
        roads[b].push_back(a);
    }

    // init dfs path, outer sum for colors
    unsigned int idxInDfs = 1;
    init(1, 0, idxInDfs);

    long long tmp = (long long)(n) * colorCnt;

    for (size_t i = 1; i < MAX_N; i++)
    {
        if (colors[i])
        {
            szOuterColor[i] = n - sum[i];
            if (0 < szOuterColor[i])
            {
                tmp -= szOuterColor[i];
            }
        }
    }
    
    // init segment tree
    update(sumPath, sumPathLazy, 1, n, tmp, 1, n, 1);

    memset(sz, 0, sizeof(sz));
    memset(sum, 0, sizeof(sum));
    idxInDfs = 1;
    func(1, 0, idxInDfs);

    for (size_t i = 1; i <= n; i++)
    {
        long long tmp = getSum(sumPath, sumPathLazy, i, i, 1, n, 1);
        sumNode[dfsPath[i]] = tmp;
    }

    for (size_t i = 1; i <= n; i++)
    {
        printf("%lld\n", sumNode[i]);
    }

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
