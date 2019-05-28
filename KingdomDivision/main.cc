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

#define DEBUG   0
#define MOD     1000000007
#define MAX_N   100001


class node
{
public:
    long long sum[4];   // 0 - Betty, 1 - Reggy, 2 - Must Betty, 3 - Must Reggy
    
    int parent;
    
    vector<int> children;
    
    node()
    {
        sum[0] = 0;
        sum[1] = 0;
        sum[2] = 0;
        sum[3] = 0;

        parent = -1;
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
            tree[curr].children.push_back((*it).second);
            
            build_tree(edges, (*it).second);
        }
    }
}

void update_tree(int curr)
{
    if (0 == tree[curr].children.size())
    {
        tree[curr].sum[2] = 1;
        tree[curr].sum[3] = 1;
    }
    else
    {
        for (size_t i = 0; i < tree[curr].children.size(); i++)
        {
            update_tree(tree[curr].children[i]);
        }

        long long betty = 1;
        long long mustBetty = 1;
        for (size_t i = 0; i < tree[curr].children.size(); i++)
        {
            betty *= (long long)(tree[tree[curr].children[i]].sum[0] + tree[tree[curr].children[i]].sum[1] + tree[tree[curr].children[i]].sum[2]);
            betty %= MOD;

            mustBetty *= (long long)(tree[tree[curr].children[i]].sum[1]);
            mustBetty %= MOD;
        }

        betty = betty + MOD - mustBetty;
        betty %= MOD;

        tree[curr].sum[0] = betty;
        tree[curr].sum[1] = betty;
        tree[curr].sum[2] = mustBetty;
        tree[curr].sum[3] = mustBetty;
    }
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int n;
#if DEBUG
    inFile >> n;
#else
    cin >> n;
#endif

    multimap<int, int> edges;
    for (size_t i = 0; i < n - 1; i++)
    {
        int u, v;
#if DEBUG
        inFile >> u >> v;
#else
        cin >> u >> v;
#endif

        edges.insert(pair<int, int>(u, v));
        edges.insert(pair<int, int>(v, u));
    }

    // build tree
    int root = 1;
    tree[root].parent = 0;
    build_tree(edges, root);

    update_tree(root);

    long long sum = tree[1].sum[0] + tree[1].sum[1];
    sum %= MOD;

    cout << sum << endl;

    return 0;
}
