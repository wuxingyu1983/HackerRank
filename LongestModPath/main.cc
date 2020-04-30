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

#define DEBUG           0
#define MAX_N           100000

vector< vector<int> > rooms;        // 记录与房间 i 联通的房间数组
multimap<long long, int> corridors; // key : a * 100000 + b , value : x
stack<int> dfs_tree;                // 深度搜索树
vector<int> depth;           // 该 room 在搜索树中的 depth, 0 - 不在树中
vector<int> circle;                 // 记录回路
vector<long long> circle_sum;
vector<int> circle_pos;
vector<long long> sumFromCircle;
vector<int> ancestorInCircle;

int xForAtoB(int a, int b)
{
    int ret = 0;

    long long key = (long long)a * (long long)MAX_N + b;

    multimap<long long, int>::iterator it = corridors.find(key);
    if (it != corridors.end())
    {
        ret = it->second;
    }
    else
    {
        key = (long long)b * (long long)MAX_N + a;
        it = corridors.find(key);
        if (it != corridors.end())
        {
            ret = 0 - it->second;
        }
    }

    return ret;
}

bool findCircle(int curr, int d)
{
    // curr 已经在 stack dfs 中了 
    bool ret = false;

    for (vector<int>::iterator it = rooms[curr].begin(); it != rooms[curr].end(); it++)
    {
        if (0 == depth[*it])
        {
            dfs_tree.push(*it);
            depth[*it] = d + 1;

            ret = findCircle(*it, d + 1);
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
                    circle[i] = dfs_tree.top();
                    dfs_tree.pop();
                }

                ret = true;
            }
        }
    }

    dfs_tree.pop();
    depth[curr] = 0;

    return ret;
}

void procOtherRooms(int curr, int parent, int ancestor, long long sum)
{
    for (vector<int>::iterator it = rooms[curr].begin(); it != rooms[curr].end(); it++)
    {
        if (0 <= circle_pos[*it])
        {
            // it 在  circle 上
        }
        else if (parent == *it)
        {
            // 已经处理过了
        }
        else
        {
            ancestorInCircle[*it] = ancestor;

            int x = xForAtoB(curr, *it);
            sumFromCircle[*it] = sum + (long long)x;

            procOtherRooms(*it, curr, ancestor, sumFromCircle[*it]);
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

    rooms.resize(n + 1);

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
    depth.resize(n + 1);

    int curr = 1;
    dfs_tree.push(curr);
    depth[curr] = 1;

    findCircle(curr, 1);

    // circle 中已经是 回路 了
    // 计算 circle 顺时针的区间 score 和 ，顺时针 index 从小到大
    // circle[i] 记录的是 index 0 --> i 的区间和，circle[0] 回路顺时针一周的和
    circle_sum.resize(circle.size());

    // 房间 i 在回路 circle 中的位置，-1 ： 不在回路中
    circle_pos.resize(n + 1);
    circle_pos.assign(n + 1, -1);
    for (size_t i_c = 0; i_c < circle.size(); i_c++)
    {
        circle_pos[circle[i_c]] = i_c;

        long long a, b;
        if (i_c + 1 < circle.size())
        {
            a = circle[i_c]; 
            b = circle[i_c + 1];
        }
        else
        {
            a = circle[i_c];
            b = circle[0];
        }

        int x = xForAtoB(a, b);

        if (i_c + 1 < circle.size())
        {
            circle_sum[i_c + 1] = circle_sum[i_c] + (long long)x;
        }
        else
        {
            circle_sum[0] = circle_sum[i_c] + (long long)x;
        }
    }

    // 计算 circle 到其他点的 score 和
    sumFromCircle.resize(n + 1);
    ancestorInCircle.resize(n + 1);

    for (size_t i_c = 0; i_c < circle.size(); i_c++)
    {
        procOtherRooms(circle[i_c], -1, circle[i_c], 0);
    }

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
