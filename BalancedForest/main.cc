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
#define MAX_N   50001

class node
{
public:
    long long val;
    long long sum;
    
    int count;
    int parent;
    int indexInParent;
    
    vector<int> children;
    
    node(long long _val = 0)
    {
        init(_val);
    }
    
    void init(long long _val = 0)
    {
        val = _val;
        sum = _val;
        count = 1;
        parent = -1; // -1 : not used, 0 : root
        indexInParent = 0;
        children.clear();
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
            tree[(*it).second].indexInParent = tree[curr].children.size();
            tree[(*it).second].parent = curr;
            tree[curr].children.push_back((*it).second);
            
            build_tree(edges, (*it).second);
        }
    }
}

long long update_tree(int curr)
{
    long long ret = tree[curr].val;
    
    if (0 < tree[curr].children.size())
    {
        vector<int>::iterator it = tree[curr].children.begin();
        for (; it != tree[curr].children.end(); it++)
        {
            ret += update_tree(*it);
            tree[curr].count += tree[*it].count;
        }
    }
    
    tree[curr].sum = ret;
    
    return ret;
}

long long can_split(int root, long long offset)
{
    bool ret = false;

    if (tree[root].sum > offset)
    {
        for (vector<int>::iterator it = tree[root].children.begin(); it != tree[root].children.end(); it++)
        {
            if (*it)
            {
                if (offset == tree[*it].sum)
                {
                    ret = true;
                    break;
                }
                else if (offset < tree[*it].sum)
                {
                    ret = can_split(*it, offset);
                }
            }
        }
    }

    return ret;
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
    
    for (size_t i_q = 0; i_q < q; i_q++)
    {
        int n;
#if DEBUG
        inFile >> n;
#else
        cin >> n;
#endif
        
        for (size_t i_n = 1; i_n <= n; i_n++)
        {
            int tmp;
#if DEBUG
            inFile >> tmp;
#else
            cin >> tmp;
#endif
            node *curr = &tree[i_n];
            curr->init(tmp);
        }
        
        vector< pair<int, int> > vec_edges;
        multimap<int, int> edges;
        for (size_t i_n = 0; i_n < n - 1; i_n++)
        {
            int x, y;
#if DEBUG
            inFile >> x >> y;
#else
            cin >> x >> y;
#endif
            edges.insert(pair<int, int>(x, y));
            edges.insert(pair<int, int>(y, x));
            
            vec_edges.push_back(pair<int, int>(x, y));
        }
        
        // build tree
        int root = 1;
        tree[root].parent = 0;
        build_tree(edges, root);
        
        // update tree sum, count
        update_tree(root);
        
        long long cw = -1;
        
        for (vector< pair<int, int> >::iterator it = vec_edges.begin(); it != vec_edges.end(); it++)
        {
            int x = (*it).first;
            int y = (*it).second;
            
            int child;
            
            if (tree[y].parent == x)
            {
                child = y;
            }
            else
            {
                // tree[x].parent == y
                child = x;
            }
            
            if (tree[child].sum == (tree[root].sum - tree[child].sum))
            {
                if (0 > cw || cw > tree[child].sum)
                {
                    cw = tree[child].sum;
                }
            }

            if (1 < tree[child].count)
            {
                if (0 == (1 & tree[child].sum) && tree[child].sum / 2 >= (tree[root].sum - tree[child].sum))
                {
                    // 平分 child 树
                    if (can_split(child, tree[child].sum / 2))
                    {
                        if (0 > cw || cw > (tree[child].sum / 2 - (tree[root].sum - tree[child].sum)))
                        {
                            cw = tree[child].sum / 2 - (tree[root].sum - tree[child].sum);
                        }
                    }
                }

                if (tree[child].sum > (tree[root].sum - tree[child].sum) && (tree[root].sum - tree[child].sum) >= (tree[child].sum - (tree[root].sum - tree[child].sum)))
                {
                    // 从 child 树中裁出来 root - child 其余的部分
                    if (can_split(child, tree[root].sum - tree[child].sum))
                    {
                        if (0 > cw || cw > (tree[root].sum - tree[child].sum - (tree[child].sum - (tree[root].sum - tree[child].sum))))
                        {
                            cw = tree[root].sum - tree[child].sum - (tree[child].sum - (tree[root].sum - tree[child].sum));
                        }
                    }
                }
            }
            
            if (1 < (tree[root].count - tree[child].count))
            {
                if (0 == (1 & (tree[root].sum - tree[child].sum)) && (tree[root].sum - tree[child].sum) / 2 >= tree[child].sum)
                {
                    // 平分 root - child 树
                    tree[tree[child].parent].children[tree[child].indexInParent] = 0;
                    for (size_t i = tree[child].parent; i > 0; i = tree[i].parent)
                    {
                        tree[i].count -= tree[child].count;
                        tree[i].sum -= tree[child].sum;
                    }

                    if (can_split(root, tree[root].sum / 2) && (0 > cw || cw > (tree[root].sum / 2 - tree[child].sum)))
                    {
                        cw = tree[root].sum / 2 - tree[child].sum;
                    }

                    for (size_t i = tree[child].parent; i > 0; i = tree[i].parent)
                    {
                        tree[i].count += tree[child].count;
                        tree[i].sum += tree[child].sum;
                    }
                    tree[tree[child].parent].children[tree[child].indexInParent] = child;
                }

                if ((tree[root].sum - tree[child].sum) > tree[child].sum && tree[child].sum >= (tree[root].sum - tree[child].sum - tree[child].sum))
                {
                    // 从 root - child 树中裁出 child
                    tree[tree[child].parent].children[tree[child].indexInParent] = 0;
                    for (size_t i = tree[child].parent; i > 0; i = tree[i].parent)
                    {
                        tree[i].count -= tree[child].count;
                        tree[i].sum -= tree[child].sum;
                    }

                    if (can_split(root, tree[child].sum) && (0 > cw || cw > (tree[child].sum - (tree[root].sum - tree[child].sum))))
                    {
                        cw = tree[child].sum - (tree[root].sum - tree[child].sum);
                    }

                    for (size_t i = tree[child].parent; i > 0; i = tree[i].parent)
                    {
                        tree[i].count += tree[child].count;
                        tree[i].sum += tree[child].sum;
                    }
                    tree[tree[child].parent].children[tree[child].indexInParent] = child;
                }
            }
        }
        
        cout << cw << endl;
    }
    
#if DEBUG
    inFile.close();
#endif
}
