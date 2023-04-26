// https://www.hackerrank.com/challenges/unique-colors/problem?isFullScreen=false
// Virtual Tree : https://oi-wiki.org/graph/virtual-tree/

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
#define MAX_N   100001

unsigned int n;
unsigned int colors[MAX_N];     // color count
unsigned int nodes[MAX_N];      // color c in node[i]
vector< vector<unsigned int> > roads(MAX_N);
unsigned int sz[MAX_N];
unsigned long long sum[MAX_N];

int main()
{
#if DEBUG
    FILE *fp = fopen("input.txt", "r");
#endif

#if DEBUG
    fscanf(fp, "%u", &n);
#else
    scanf("%u", &n);
#endif

    for (size_t i = 1; i <= n; i++)
    {
#if DEBUG
        fscanf(fp, "%u", &nodes[i]);
#else
        scanf("%u", &nodes[i]);
#endif
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

    

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
