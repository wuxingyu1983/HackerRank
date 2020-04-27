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
#include <stack>

using namespace std;

#define DEBUG   0
#define MAX_N   100000

bool findCircle(vector< vector<int> > &rooms, int curr, int d, stack<int> &dfs, vector<int> &depth, vector<int> &circle)
{
    bool ret = false;

    for (vector<int>::iterator it = rooms[curr].begin(); it != rooms[curr].end(); it++)
    {
        if (0 == depth[*it])
        {
            dfs.push(*it);
            depth[*it] = d + 1;

            ret = findCircle(rooms, *it, d + 1, dfs, depth, circle);
            if (ret)
            {
                break;
            }
        }
        else
        {
            if ((d - 1) == depth[*it])
            {
                // *it 是 curr 的 父亲
            }
            else
            {
                // 找到 回路 了
                circle.resize(d - depth[*it] + 1);

                for (size_t i = 0; i < circle.size(); i++)
                {
                    circle[i] = dfs.top();
                    dfs.pop();
                }

                ret = true;
            }
        }
    }

    dfs.pop();
    depth[curr] = 0;

    return ret;
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

    vector< vector<int> > rooms(n + 1);       // 记录与房间 i 联通的房间数组
    multimap<long long, int> corridors;     // key : a * 100000 + b , value : x

    for (size_t i_n = 0; i_n < n; i_n++)
    {
        int a, b, x;
#if DEBUG
        inFile >> a >> b >> x;
#else
        cin >> a >> b >> x;
#endif

        rooms[a].push_back(b);
        rooms[b].push_back(a);

        long long key = (long long)a * (long long)MAX_N + (long long)b;
        corridors.insert(pair<long long, int>(key, x));
    }

    // find 回路
    stack<int> dfs_tree;        // 深度搜索树
    vector<int> depth(n + 1);   // 该 room 在搜索树中的 depth, 0 - 不在树中
    vector<int> circle;         // 记录回路

    int curr = 1;
    dfs_tree.push(curr);
    depth[curr] = 1;

    findCircle(rooms, curr, 1, dfs_tree, depth, circle);

    int q;
#if DEBUG
    inFile >> q;
#else
    cin >> q;
#endif

    for (size_t i_q = 0; i_q < q; i_q++)
    {
        int s, e, m;
#if DEBUG
        inFile >> s >> e >> m;
#else
        cin >> s >> e >> m;
#endif
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
