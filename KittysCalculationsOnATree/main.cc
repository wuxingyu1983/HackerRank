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
#include <set>

using namespace std;

#define DEBUG 0
#define MAX_N   200002
#define MOD 1000000007

class node
{
public:
    int parent;
    int idx; // child index in parent
    vector<int> children;
    vector<int> flag; // 1 - children in set
    long long sum1;   // ∑ua
    long long sum2;   // ∑u

    node()
    {
        parent = -1;
        idx = -1;
        sum1 = 0;
        sum2 = 0;
    }
} tree[MAX_N];

void build_tree(multimap<int, int> &edges, int curr)
{
    for (multimap<int, int>::iterator it = edges.equal_range(curr).first; it != edges.equal_range(curr).second; ++it)
    {
        if (0 <= tree[(*it).second].parent)
        {
            // in the tree already
        }
        else
        {
            tree[(*it).second].parent = curr;
            tree[(*it).second].idx = tree[curr].children.size();
            tree[curr].children.push_back((*it).second);
            tree[curr].flag.push_back(0);

            build_tree(edges, (*it).second);
        }
    }
}

void getSubSum(set<int> &sset, int curr, long long &sum)
{
    tree[curr].sum1 = 0;
    tree[curr].sum2 = 0;

    if (sset.end() != sset.find(curr))
    {
        // find
        tree[curr].sum2 = curr;
    }

    if (0 < tree[curr].children.size())
    {
        for (vector<int>::iterator it = tree[curr].children.begin(); it != tree[curr].children.end(); it++)
        {
            if (1 == tree[curr].flag[it - tree[curr].children.begin()])
            {
                getSubSum(sset, *it, sum);

                sum += (tree[*it].sum1 + tree[*it].sum2) * tree[curr].sum2 + tree[curr].sum1 * tree[*it].sum2;

                sum %= MOD;

                tree[curr].sum1 += tree[*it].sum1 + tree[*it].sum2;
                tree[curr].sum1 %= MOD;
                tree[curr].sum2 += tree[*it].sum2;
                tree[curr].sum2 %= MOD;
            }
        }
    }

    if (0 <= tree[curr].idx)
    {
        tree[tree[curr].parent].flag[tree[curr].idx] = 0;
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

    multimap<int, int> edges;
    for (size_t i = 0; i < n - 1; i++)
    {
        int a, b;
#if DEBUG
        inFile >> a >> b;
#else
        cin >> a >> b;
#endif

        edges.insert(pair<int, int>(a, b));
        edges.insert(pair<int, int>(b, a));
    }

    // build tree
    int root = 1;
    tree[root].parent = 0;
    build_tree(edges, root);

    for (size_t i = 0; i < q; i++)
    {
        int k;
#if DEBUG
        inFile >> k;
#else
        cin >> k;
#endif

        set<int> sset;
        for (size_t j = 0; j < k; j++)
        {
            int elem;
#if DEBUG
            inFile >> elem;
#else
            cin >> elem;
#endif
            sset.insert(elem);

            int tmp = elem;
            while (0 <= tree[tmp].idx && 0 == tree[tree[tmp].parent].flag[tree[tmp].idx])
            {
                tree[tree[tmp].parent].flag[tree[tmp].idx] = 1;
                tmp = tree[tmp].parent;
            }
        }

        if (0 == k)
        {
            cout << 0 << endl;
        }
        else
        {
            long long sum = 0;

            getSubSum(sset, root, sum);

            cout << sum << endl;
        }
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
