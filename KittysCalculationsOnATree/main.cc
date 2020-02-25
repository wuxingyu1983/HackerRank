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
#define MAX_N 200002
#define MOD 1000000007

vector<int> sset;
vector<int> flag; // 是否已经访问过
vector<int> lvl[2];

long long sum;

class node
{
public:
    int parent;
    int depth;
    int idx; // child index in parent
    vector<int> children;
    vector<int> flag; // 1 - children in set
    long long sum1;   // ∑ua
    long long sum2;   // ∑u

    node()
    {
        parent = -1;
        depth = 0;
        idx = -1;
        sum1 = 0;
        sum2 = 0;
    }
};

vector<node> tree;

class nodeDep
{
public:
    int val;
    int depth;

    nodeDep()
    {
        val = 0;
        depth = 0;
    }
};

vector<nodeDep> nodes;

bool cmp(nodeDep &a, nodeDep &b)
{
    return a.depth > b.depth;
}

void build_tree(multimap<int, int> &edges, int curr, int dep)
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
            tree[(*it).second].depth = dep;
            tree[(*it).second].idx = tree[curr].children.size();
            tree[curr].children.push_back((*it).second);
            tree[curr].flag.push_back(0);

            build_tree(edges, (*it).second, dep + 1);
        }
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

    tree.resize(n + 1);
    sset.resize(n + 1, 0);
    flag.resize(n + 1, 0);
    lvl[0].resize(n + 1, 0);
    lvl[1].resize(n + 1, 0);
    nodes.resize(n + 1);

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
    int dep = 1;
    tree[root].parent = 0;
    tree[root].depth = dep;
    build_tree(edges, root, dep + 1);

    for (size_t i = 1; i <= q; i++)
    {
        int k;
#if DEBUG
        inFile >> k;
#else
        cin >> k;
#endif

        for (size_t j = 0; j < k; j++)
        {
            int elem;
#if DEBUG
            inFile >> elem;
#else
            cin >> elem;
#endif
            sset[elem] = i; // 标记此轮set有它

            tree[elem].sum1 = 0;
            tree[elem].sum2 = elem;

            nodes[j].val = elem;
            nodes[j].depth = tree[elem].depth;
        }

        if (1 == k)
        {
            cout << 0 << endl;
        }
        else
        {
            sum = 0;

            // sort
            sort(nodes.begin(), nodes.begin() + k, cmp);

            int dp = nodes[0].depth;
            int min_dp = nodes[k - 1].depth;

            int src = 0;
            int idx = 0;
            int idxInSrc = 0;
            int idxInDst = 0;

            while (idx < k)
            {
                if (nodes[idx].depth == dp)
                {
                    lvl[src][idxInSrc++] = nodes[idx].val;
                    idx++;
                }
                else
                {
                    break;
                }
            }

            idxInDst = idxInSrc;

            while (1 < dp)
            {
                int dst = 1 - src;
                idxInSrc = idxInDst;
                idxInDst = 0;

                for (vector<int>::iterator it = lvl[src].begin(); it != lvl[src].begin() + idxInSrc; it++)
                {
                    int parent = tree[*it].parent;

                    if (flag[parent] != i)
                    {
                        // 还没有访问过
                        if (sset[parent] != i)
                        {
                            tree[parent].sum1 = 0;
                            tree[parent].sum2 = 0;
                        }

                        lvl[dst][idxInDst++] = parent;

                        flag[parent] = i;
                    }

                    sum += (tree[*it].sum1 + tree[*it].sum2) * tree[parent].sum2 + tree[parent].sum1 * tree[*it].sum2;

                    sum %= MOD;

                    tree[parent].sum1 += tree[*it].sum1 + tree[*it].sum2;
                    tree[parent].sum1 %= MOD;
                    tree[parent].sum2 += tree[*it].sum2;
                    tree[parent].sum2 %= MOD;
                }

                dp--;

                while (idx < k)
                {
                    if (nodes[idx].depth == dp)
                    {
                        if (flag[nodes[idx].val] != i)
                        {
                            // 还没有访问过
                            lvl[dst][idxInDst++] = nodes[idx].val;

                            flag[nodes[idx].val] = i;
                        }

                        idx++;
                    }
                    else
                    {
                        break;
                    }
                }

                if (dp < min_dp && 1 >= idxInDst)
                {
                    break;
                }

                src = 1 - src;
            }

            cout << sum << endl;
        }
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
