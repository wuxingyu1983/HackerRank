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

#define DEBUG 0
#define MAX_N 51

class node
{
public:
    int parent;
    vector<int> children;
    long long connect[MAX_N];

    node()
    {
        parent = -1;
        memset(connect, 0, sizeof(long long) * MAX_N);
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
        if (0 == tree[curr].parent)
        {
            tree[curr].connect[0] = 1;
        }
        else
        {
            tree[curr].connect[1] = 1;
        }
    }
    else
    {
        vector<int>::iterator child = tree[curr].children.begin();
        while (child != tree[curr].children.end())
        {
            update_tree(*child);
            child++;
        }

        if (0 == tree[curr].parent)
        {
            tree[curr].connect[tree[curr].children.size()] = 1;
        }
        else
        {
            tree[curr].connect[tree[curr].children.size() + 1] = 1;
        }

        long long tmp[MAX_N];

        child = tree[curr].children.begin();
        while (child != tree[curr].children.end())
        {
            memcpy(tmp, tree[curr].connect, sizeof(long long) * MAX_N);
            for (size_t i = 0; i < MAX_N; i++)
            {
                for (size_t j = 0; j < MAX_N; j++)
                {
                    if (0 <= (i + j - 2) && MAX_N > (i + j - 2) && 0 < tree[curr].connect[i] && 0 < tree[*child].connect[j])
                    {

                        tmp[i + j - 2] += tree[curr].connect[i] * tree[*child].connect[j];
                    }
                }
            }

            memcpy(tree[curr].connect, tmp, sizeof(long long) * MAX_N);
            child++;
        }
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

    update_tree(root);

    long long cnt = 1;

    for (size_t i = 1; i <= n; i++)
    {
        for (size_t j = 0; j <= k; j++)
        {
            cnt += tree[i].connect[j];
        }
    }

    cout << cnt << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
