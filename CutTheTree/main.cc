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
#include <queue>
#include <stack>

using namespace std;

#define DEBUG   0
#define MAX_N   100002

int t[MAX_N];
int ans = -1;
int total;

class node
{
public:
    int parent;
    vector<int> children;
    long long sum;

    node()
    {
        parent = -1;
        sum = 0;
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
    if (0 < tree[curr].children.size())
    {
        vector<int>::iterator child = tree[curr].children.begin();
        while (child != tree[curr].children.end())
        {
            update_tree(*child);
            tree[curr].sum += tree[*child].sum;
            child++;
        }
    }

    tree[curr].sum += t[curr];

    if (0 > ans)
    {
        ans = abs(total - tree[curr].sum - tree[curr].sum);
    }
    else
    {
        if (ans > abs(total - tree[curr].sum - tree[curr].sum)) 
        {
            ans = abs(total - tree[curr].sum - tree[curr].sum);
        }
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

    for (size_t i = 1; i <= n; i++)
    {
#if DEBUG
        inFile >> t[i];
#else
        cin >> t[i];
#endif

        total += t[i];
    }

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

    cout << ans << endl;

    return 0;
}
