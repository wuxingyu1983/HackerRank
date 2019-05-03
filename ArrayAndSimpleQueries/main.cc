#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <set>
#include <iomanip>

using namespace std;

#define DEBUG 0

struct Treap
{
    int val;
    int size;
    int pri;
    Treap *left;
    Treap *right;
    Treap(int _val = -1)
    {
        val = _val;
        size = 1;
        pri = rand();
        left = NULL;
        right = NULL;
    }
} * root;

int size(Treap * tree)
{
    if (tree)
    {
        return tree->size;
    }
    else
    {
        return 0;
    }
}

void update_size(Treap *t)
{
    if (t)
        t->size = 1 + size(t->left) + size(t->right);
}

Treap *merge(Treap *l, Treap *r)
{
    if (!l || !r)
        return (!l) ? r : l;
    Treap *ans = NULL;
    if (l->pri > r->pri)
    {
        l->right = merge(l->right, r);
        ans = l;
    }
    else
    {
        r->left = merge(l, r->left);
        ans = r;
    }

    update_size(ans);
    return ans;
}

void split(Treap *t, int k, Treap *&l, Treap *&r)
{
    if (!t)
    {
        l = r = 0;
        return;
    }

    int key = size(t->left);
    if (key < k)
    {
        split(t->right, k - key - 1, t->right, r);
        l = t;
    }
    else
    {
        split(t->left, k, l, t->left);
        r = t;
    }

    update_size(t);
}

void insert(int val)
{
    root = merge(root, new Treap(val));
}

int find_kth(Treap *t, int k, int add = 0)
{
    int cur_pos = add + size(t->left) + 1;
    if (cur_pos == k)
        return t->val;
    if (cur_pos < k)
        return find_kth(t->right, k, cur_pos);
    return find_kth(t->left, k, add);
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int n, m;
#if DEBUG
    inFile >> n >> m;
#else
    cin >> n >> m;
#endif

    for (size_t i = 0; i < n; i++)
    {
        int tmp;
#if DEBUG
        inFile >> tmp;
#else
        cin >> tmp;
#endif
        insert(tmp);
    }

    Treap *leftPart, *rightPart, *middlePart;
    for (size_t i = 0; i < m; i++)
    {
        int type, begin, end;
#if DEBUG
        inFile >> type >> begin >> end;
#else
        cin >> type >> begin >> end;
#endif

        split(root, begin - 1, leftPart, rightPart);
        split(rightPart, end - begin + 1, middlePart, rightPart);

        if (1 == type)
        {
            root = merge(middlePart, leftPart);
            root = merge(root, rightPart);
        }
        else
        {
            root = merge(leftPart, rightPart);
            root = merge(root, middlePart);
        }
    }

    printf("%d\n", abs(find_kth(root, 1) - find_kth(root, n)));
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", find_kth(root, i));
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
