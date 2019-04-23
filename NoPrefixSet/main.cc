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

#define DEBUG 0

const int N = 100000;
const int max_len = 60;
int tot;

struct node
{
    node *next[10];
    int index;
    void init()
    {
        memset(next, 0, sizeof next);
        index = -1;
    }
} trie[N * max_len + 1], *root;

node *new_node()
{
    trie[tot].init();
    return trie + tot++;
}

void trie_init()
{
    tot = 0;
    root = new_node();
}

bool trie_insert(string &str, int idx)
{
    bool ret = false;

    node *p = root;
    for (int i = 0; i < str.length(); i++)
    {
        int j = str[i] - 'a';
        if (p->next[j] == NULL)
        {
            if (p->index < 0)
            {
                p->next[j] = new_node();
                ret = true;

                if (i == (str.length() - 1))
                {
                    p->next[j]->index = idx;
                }
            }
            else
            {
                break;
            }
        }

        p = p->next[j];
    }

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

    trie_init();

    vector<string> strs;
    for (size_t i = 0; i < n; i++)
    {
        string tmp;
#if DEBUG
        inFile >> tmp;
#else
        cin >> tmp;
#endif

        strs.push_back(tmp);
    }

    bool isGood = true;
    for (size_t i = 0; i < n; i++)
    {
        if (false == trie_insert(strs[i], i))
        {
            isGood = false;
            cout << "BAD SET" << endl;
            cout << strs[i] << endl;
            break;
        }
    }

    if (isGood)
    {
        cout << "GOOD SET" << endl;
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
