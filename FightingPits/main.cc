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
#include <set>

using namespace std;

#define DEBUG   0

class TPlayer
{
public:
    int strength;
    int cnt;
    int parent, leftChild, rightChild;

    TPlayer()
    {
        strength = -1;
        cnt = -1;
        parent = leftChild = rightChild = -1;
    }
};

class Player
{
public:
    int s, t;

    Player()
    {
        s = 0;
        t = 0;
    }
};

class Query
{
public:
    int op, p, x, y;

    Query()
    {
        op = 0;
        p = 0;
        x = 0;
        y = 0;
    }
};

void addPlayer(vector< vector<TPlayer> >&team, int strength)
{
    int level = team.size();
    int parent = 0;

    for (int l = level - 1; l > 0; l --)
    {
        if (strength <= team[l][parent].strength)
        {
            parent = team[l][parent].leftChild;
        }
        else
        {
            parent = team[l][parent].rightChild;
        }
    }

    team[0][parent].cnt += 1;

    parent = team[0][parent].parent;

    for (int l = 1; l < level; l ++)
    {
        team[l][parent].cnt += 1;
        parent = team[l][parent].parent;
    }
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int n, k, q;
#if DEBUG
    inFile >> n >> k >> q;
#else
    cin >> n >> k >> q;
#endif

    vector<Player> players(n);
    set<int> team[k + 1];

    for (size_t i = 0; i < n; i++)
    {
        int s, t;
#if DEBUG
        inFile >> s >> t;
#else
        cin >> s >> t;
#endif

        players[i].s = s;
        players[i].t = t;

        team[t].insert(s);
    }

    vector<Query> queries(q);
    for (size_t i = 0; i < q; i++)
    {
        int op;
#if DEBUG
        inFile >> op;
#else
        cin >> op;
#endif

        queries[i].op = op;
        if (1 == op)
        {
            int p, x;
#if DEBUG
            inFile >> p >> x;
#else
            cin >> p >> x;
#endif

            queries[i].p = p;
            queries[i].x = x;
            
            team[x].insert(p);
        }
        else
        {
            // 2
            int x, y;
#if DEBUG
            inFile >> x >> y;
#else
            cin >> x >> y;
#endif

            queries[i].x = x;
            queries[i].y = y;
        }
    }

    // tteam[k + 1][level][cnt of players]
    vector< vector < vector<TPlayer> > > tteam(k + 1);
    for (size_t t = 1; t <= k; t++)
    {
        int level = 1;
        int sz = team[t].size();
        while (1 != sz)
        {
            if (1 & sz)
            {
                sz = sz / 2 + 1;
            }
            else
            {
                sz /= 2;
            }

            level++;
        }

        tteam[t].resize(level);

        for (size_t l = 0; l < level; l++)
        {
            tteam[t][l].resize(team[t].size());
        }
        
        for (size_t l = 0; l < level; l++)
        {
            if (0 == l)
            {
                int i = 0;
                for (set<int>::reverse_iterator rit = team[t].rbegin(); rit != team[t].rend(); rit ++ , i ++)
                {
                    tteam[t][l][i].cnt = 0;
                    tteam[t][l][i].strength = *rit;
                }
            }
            else
            {
                int i = 0, j = 0;   // i -> l - 1, j -> l
                while (i < team[t].size() && 0 < tteam[t][l - 1][i].strength)
                {
                    tteam[t][l][j].cnt = 0;
                    tteam[t][l - 1][i].parent = j;
                    if (0 > tteam[t][l][j].leftChild)
                    {
                        tteam[t][l][j].leftChild = i;
                        tteam[t][l][j].strength = tteam[t][l - 1][i].strength;
                    }
                    else
                    {
                        tteam[t][l][j].rightChild = i;
                        tteam[t][l][j].strength = (tteam[t][l][j].strength + tteam[t][l - 1][i].strength) / 2;
                        j ++;
                    }
                    
                    i ++;
                }
            }
        }
    }

    for (size_t i = 0; i < n; i++)
    {
        addPlayer(tteam[players[i].t], players[i].s);
    }

    for (size_t i = 0; i < q; i++)
    {
        if (1 == queries[i].op)
        {
            addPlayer(tteam[queries[i].x], queries[i].p);
        }
        else
        {
            int winner = 0;

            

            cout << winner << endl;
        }
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
