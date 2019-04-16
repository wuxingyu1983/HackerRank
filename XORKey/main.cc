#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

#define DEBUG   0

const int N = 100000 + 10;
int tot;
int len = 16;

struct node
{
    node *next[2];
    vector<int> vec;
    void init()
    {
        memset(next, 0, sizeof next);
        vec.clear();
    }
} trie[N * 16], *root;

node * new_node()
{
    trie[tot].init();
    return trie + tot++;
}

void trie_init()
{
    tot = 0;
    root = new_node();
}

void trie_insert(int val, int id)
{
    node *p = root;
    for (int i = len - 1; i >= 0; i--)
    {
        int j = 1 & (val >> i);
        if (p->next[j] == NULL)
            p->next[j] = new_node();
        p->next[j]->vec.push_back(id);
        p = p->next[j];
    }
}

bool check(node *&p, int l, int r)
{
    return upper_bound(p->vec.begin(), p->vec.end(), r) - lower_bound(p->vec.begin(), p->vec.end(), l);
}

int trie_query(int val, int l, int r)
{
    node *p = root;
    int ans = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        int j = !(1 & (val >> i));
        if (p->next[j] && check(p->next[j], l, r))
        {
            ans = ans * 2 + 1;
            p = p->next[j];
        }
        else
        {
            ans = ans * 2 + 0;
            p = p->next[!j];
        }
    }
    return ans;
}

void xorkey(int a, int l, int r)
{
    int ans = trie_query(a, l, r);
    cout << ans << endl;
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
        int n, q;
#if DEBUG
        inFile >> n >> q;
#else
        cin >> n >> q;
#endif

        vector<int> x;
        x.reserve(n);

        trie_init();

        for (size_t i_a = 0; i_a < n; i_a++)
        {
            int tmp;
#if DEBUG
            inFile >> tmp;
#else
            cin >> tmp;
#endif
            x.push_back(tmp);

            trie_insert(tmp, i_a + 1);
        }

        for (size_t i_q = 0; i_q < q; i_q++)
        {
            int a, l, r;
#if DEBUG
            inFile >> a >> l >> r;
#else
            cin >> a >> l >> r;
#endif
            xorkey(a, l, r);
        }
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}