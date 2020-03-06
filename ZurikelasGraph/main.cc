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
#define MAX_Q   200002

class node
{
public:
    int parent;
    vector<int> children;
    int sum[2];     // [0] - 未选中情况下的最大sum，[1] - 选中情况下的最大sum

    node()
    {
        parent = -1;
    }
};

int set[MAX_Q];     // set[x] 为 xth set 中最多的满足无直接连接的点的个数
node tree[MAX_Q];

void sumOfTree(int root)
{
    tree[root].sum[1] = set[root];

    for (vector<int>::iterator it = tree[root].children.begin(); it != tree[root].children.end(); it++)
    {
        sumOfTree(*it);

        tree[root].sum[0] += (tree[*it].sum[0] > tree[*it].sum[1]) ? tree[*it].sum[0] : tree[*it].sum[1];
        tree[root].sum[1] += tree[*it].sum[0];
    }
    
    set[root] = 0;
}

void c_func(int x, int index)
{
    int root = x;
    // to root
    while (0 < tree[root].parent)
    {
        root = tree[root].parent;
    }

    sumOfTree(root);

    set[index] = (tree[root].sum[0] > tree[root].sum[1]) ? tree[root].sum[0] : tree[root].sum[1];
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int q;
#if DEBUG
    inFile >> q;
#else
    cin >> q;
#endif

    int index = 1;      // index of last created set
    for (size_t i = 0; i < q; i++)
    {
        char op;
#if DEBUG
        inFile >> op;
#else
        cin >> op;
#endif

        if ('A' == op)
        {
            int x;
#if DEBUG
            inFile >> x;
#else
            cin >> x;
#endif

            set[index] = x;

            index ++;
        }
        else if ('B' == op)
        {
            int x, y;
#if DEBUG
            inFile >> x >> y;
#else
            cin >> x >> y;
#endif

            if (0 < set[x] && 0 < set[y])
            {
                tree[x].children.push_back(y);
                tree[y].parent = x;
            }
        }
        else
        {
            // C
            int x;
#if DEBUG
            inFile >> x;
#else
            cin >> x;
#endif

            c_func(x, index);

            index ++;
        }
    }

    int sum = 0;
    for (size_t i = 1; i < index; i++)
    {
        if (0 < set[i])
        {
            if (0 > tree[i].parent && 0 == tree[i].children.size())
            {
                sum += set[i];
            }
            else
            {
                c_func(i, index);

                index++;
            }
        }
    }

    cout << sum << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
