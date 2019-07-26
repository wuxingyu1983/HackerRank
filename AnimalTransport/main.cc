#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <limits.h>

#define DEBUG       0
#define MAX_MN      50001

using namespace std;

int treeNode0[4 * MAX_MN];
int treeNode1[4 * MAX_MN];
int lazy0[4 * MAX_MN];
int lazy1[4 * MAX_MN];

int dp[MAX_MN];
int sum0[MAX_MN];
int sum1[MAX_MN];

void initializeTreeNode(int *arr, int *treeNode, int nodeNumber, int start, int end)
{
    int mid, left, right;
    if (start == end)
    {
        treeNode[nodeNumber] = arr[start]; // intialize leaf treeNode to the array value.
        return;
    }

    mid = (start + end) / 2;
    left = 2 * nodeNumber;
    right = 2 * nodeNumber + 1;

    initializeTreeNode(arr, treeNode, left, start, mid);
    initializeTreeNode(arr, treeNode, right, mid + 1, end);

    treeNode[nodeNumber] = max(treeNode[left], treeNode[right]); // for finding minimum value

    return;
}

void update(int *treeNode, int nodeNumber, int *lazy, int start, int end, int l, int r, int value)
{
    int mid, left, right;
    if (lazy[nodeNumber] != 0)
    {
        treeNode[nodeNumber] += lazy[nodeNumber];
        if (start != end)
        {
            lazy[nodeNumber * 2] += lazy[nodeNumber];
            lazy[nodeNumber * 2 + 1] += lazy[nodeNumber];
        }
        lazy[nodeNumber] = 0;
    }
    if (end < l || start > r)
        return;
    if (start >= l && end <= r)
    {
        treeNode[nodeNumber] += value;
        if (start != end)
        {
            lazy[nodeNumber * 2] += value;
            lazy[nodeNumber * 2 + 1] += value;
        }
        return;
    }

    mid = (start + end) / 2;
    left = nodeNumber * 2;
    right = nodeNumber * 2 + 1;

    update(treeNode, left, lazy, start, mid, l, r, value);
    update(treeNode, right, lazy, mid + 1, end, l, r, value);

    treeNode[nodeNumber] = max(treeNode[left], treeNode[right]);
    return;
}

int query(int *treeNode, int nodeNumber, int *lazy, int start, int end, int l, int r)
{
    int mid, left, right, q1, q2;
    if (end < l || start > r)
        return INT_MIN;
    if (lazy[nodeNumber] != 0)
    {

        treeNode[nodeNumber] += lazy[nodeNumber];

        if (start != end)
        {
            lazy[nodeNumber * 2] += lazy[nodeNumber];
            lazy[nodeNumber * 2 + 1] += lazy[nodeNumber];
        }
        lazy[nodeNumber] = 0;
    }
    if (start >= l && end <= r)
        return treeNode[nodeNumber];

    mid = (start + end) / 2;
    left = nodeNumber * 2;
    right = nodeNumber * 2 + 1;

    q1 = query(treeNode, left, lazy, start, mid, l, r);
    q2 = query(treeNode, right, lazy, mid + 1, end, l, r);
    return max(q1, q2);
}

class Animal
{
public:
    char type;
    int src, dst;

    Animal(char _type = 0, int _src = 0, int _dst = 0)
    {
        type = _type;
        src = _src;
        dst = _dst;
    }

    Animal(const Animal & v)
    {
        type = v.type;
        src = v.src;
        dst = v.dst;
    }
};

bool comp(Animal& v1, Animal& v2)
{
    return v1.src < v2.src;
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int t;
#if DEBUG
    inFile >> t;
#else
    cin >> t;
#endif

    for (size_t i_t = 0; i_t < t; i_t++)
    {
        int m, n;
#if DEBUG
        inFile >> m >> n;
#else
        cin >> m >> n;
#endif

        vector<Animal> tmp_animals(n);
        for (size_t i_n = 0; i_n < n; i_n++)
        {
            char type;
#if DEBUG
            inFile >> type;
#else
            cin >> type;
#endif

            tmp_animals[i_n] = Animal(type, 0, 0);
        }

        for (size_t i_n = 0; i_n < n; i_n++)
        {
            int src;
#if DEBUG
            inFile >> src;
#else
            cin >> src;
#endif
            tmp_animals[i_n].src = src;
        }
        
        // 0 - {E, C}, 1 - {D, M}
        vector<Animal> animals0;
        animals0.reserve(n);
        vector<Animal> animals1;
        animals1.reserve(n);
        for (size_t i_n = 0; i_n < n; i_n++)
        {
            int dst;
#if DEBUG
            inFile >> dst;
#else
            cin >> dst;
#endif
            tmp_animals[i_n].dst = dst;

            if (tmp_animals[i_n].src < tmp_animals[i_n].dst)
            {
                if ('E' == tmp_animals[i_n].type || 'C' == tmp_animals[i_n].type)
                {
                    animals0.push_back(tmp_animals[i_n]);
                }
                else
                {
                    animals1.push_back(tmp_animals[i_n]);
                }
            }
        }

        // sort
        sort(animals0.begin(), animals0.end(), comp);
        sort(animals1.begin(), animals1.end(), comp);

        map<int, vector<int> > map0;
        map<int, vector<int> > map1;

        for (int i = 0; i < animals0.size(); i ++)
        {
            Animal& v = animals0[i];
            if (map0.end() == map0.find(v.dst))
            {
                map0.insert(pair<int, vector<int> >(v.dst, vector<int>()));
            }

            vector<int>& vec = map0.find(v.dst)->second;
            vec.push_back(v.src);
        }

        for (int i = 0; i < animals1.size(); i ++)
        {
            Animal& v = animals1[i];
            if (map1.end() == map1.find(v.dst))
            {
                map1.insert(pair<int, vector<int> >(v.dst, vector<int>()));
            }

            vector<int>& vec = map1.find(v.dst)->second;
            vec.push_back(v.src);
        }
        
        memset(treeNode0, 0, 4 * MAX_MN * sizeof(int));
        memset(treeNode1, 0, 4 * MAX_MN * sizeof(int));
        memset(lazy0, 0, 4 * MAX_MN * sizeof(int));
        memset(lazy1, 0, 4 * MAX_MN * sizeof(int));

        memset(dp, 0, MAX_MN * sizeof(int));
        memset(sum0, 0, MAX_MN * sizeof(int));
        memset(sum1, 0, MAX_MN * sizeof(int));

        // init segment tree
        initializeTreeNode(sum0, treeNode0, 1, 1, m);
        initializeTreeNode(sum1, treeNode1, 1, 1, m);

        for (int i = 1; i <= m; i ++)
        {
            int tmp = dp[i - 1];
            if (map0.end() != map0.find(i))
            {
                vector<int>& vec = map0.find(i)->second;
                for (int j = 0; j < vec.size(); j ++)
                {
                    update(treeNode0, 1, lazy0, 1, m, 1, vec[j], 1);
                }
                
                int tmp0 = query(treeNode0, 1, lazy0, 1, m, 1, i);
                if (tmp0 > tmp)
                {
                    tmp = tmp0;
                }
            }

            if (map1.end() != map1.find(i))
            {
                vector<int>& vec = map1.find(i)->second;
                for (int j = 0; j < vec.size(); j ++)
                {
                    update(treeNode1, 1, lazy1, 1, m, 1, vec[j], 1);
                }
                
                int tmp1 = query(treeNode1, 1, lazy1, 1, m, 1, i);
                if (tmp1 > tmp)
                {
                    tmp = tmp1;
                }                
            }

            dp[i] = tmp;
            update(treeNode0, 1, lazy0, 1, m, i, i, tmp);
            update(treeNode1, 1, lazy1, 1, m, i, i, tmp);
        }

        int outed = 0;
        for (int i = 1; i <= m; i ++)
        {
            if (dp[i] != outed)
            {
                for (int j = outed; j < dp[i]; j ++)
                {
                    cout << i << " ";
                }

                outed = dp[i];
            }
        }

        for (int i = outed; i < n; i ++)
        {
            cout << "-1 ";
        }

        cout << endl; 
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
