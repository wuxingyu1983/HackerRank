#include <cmath>
#include <cstdio>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <limits.h>

#define DEBUG   0
#define MAX_N   100001
#define MAX_K   201
#define MIN_W   (0 - 1000000000)

using namespace std;

class node
{
public:
    int parent;
    int w;
    int remove;     // can remove
    vector<int> children;
    long long sum[MAX_K];

    node()
    {
        parent = -1;
        w = 0;
        remove = 0;
        for (size_t i = 0; i < MAX_K; i++)
        {
            sum[i] = (long long)MAX_N * (long long)MIN_W;
        }
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
    vector<int>::iterator child = tree[curr].children.begin();
    while (child != tree[curr].children.end())
    {
        update_tree(*child);
        tree[curr].sum[0] += tree[*child].sum[0];
        child ++;
    }
}

void proc_tree(int curr, int k)
{
    vector<int>::iterator child = tree[curr].children.begin();
    while (child != tree[curr].children.end())
    {
        proc_tree(*child, k);

        long long tmp[k + 1];
        for (size_t i = 0; i <= k; i ++) {
            tmp[i] = (long long)MAX_N * (long long)MIN_W;
        }
        
        // remove subtree child
        for (size_t i = 0; i <= tree[curr].remove && i < k; i++)
        {
            if (tree[curr].sum[i] - tree[*child].sum[0] > tree[curr].sum[i + 1])
            {
                tmp[i + 1] = tree[curr].sum[i] - tree[*child].sum[0];
            }
            else
            {
                tmp[i + 1] = tree[curr].sum[i + 1];
            }
        }

        if (0 == tree[*child].remove)
        {
            if (tree[curr].remove < k)
            {
                tree[curr].remove++;
            }
        }
        else
        {
            for (size_t i = 0; i <= tree[curr].remove; i++)
            {
                for (size_t j = 1; j <= tree[*child].remove; j++)
                {
                    if (i + j > k)
                    {
                        break;
                    }

                    if (tree[curr].sum[i] - (tree[*child].sum[0] - tree[*child].sum[j]) > tmp[i + j])
                    {
                        tmp[i + j] = tree[curr].sum[i] - (tree[*child].sum[0] - tree[*child].sum[j]);
                    }
                }
            }

            if (tree[curr].remove + tree[*child].remove <= k)
            {
                tree[curr].remove += tree[*child].remove;
            }
            else
            {
                tree[curr].remove = k;
            }
        }
        
        for (size_t i = 1; i <= tree[curr].remove; i ++) {
            tree[curr].sum[i] = tmp[i];
        }

        child ++;
    }
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int n, k;
#if DEBUG
    inFile >> n >> k;
#else
    cin >> n >> k;
#endif

    for (size_t i = 1; i <= n; i++)
    {
#if DEBUG
        inFile >> tree[i].w;
#else
        cin >> tree[i].w;
#endif
        tree[i].sum[0] = tree[i].w;
    }

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

    proc_tree(root, k);

    long long ret = 0;
    for (size_t i = 0; i <= k; i++)
    {
        if (tree[root].sum[i] > ret)
        {
            ret = tree[root].sum[i];
        }
    }

    cout << ret << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
