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
#include <queue>
#include <stack>

using namespace std;

#define DEBUG   0
#define MAX_N   200

char board[MAX_N][MAX_N];
int n;

class Position
{
public:
    int i, j;

    Position(int _i, int _j)
    {
        i = _i;
        j = _j;
    }
};

void pushToQ(queue<Position> &q, Position &pos)
{
    int i, j;

    // UL -- 1
    i = pos.i - 2;
    j = pos.j - 1; 
    if (0 <= i && 0 <= j)
    {
        if (0 == board[i][j])
        {
            // 还没有访问过
            board[i][j] = 1; 
            q.push(Position(i, j));
        }
    }

    // UR -- 2
    i = pos.i - 2;
    j = pos.j + 1;
    if (0 <= i && n > j)
    {
        if (0 == board[i][j])
        {
            // 还没有访问过
            board[i][j] = 2; 
            q.push(Position(i, j));
        }
    }

    // R -- 3
    i = pos.i;
    j = pos.j + 2;
    if (n > j)
    {
        if (0 == board[i][j])
        {
            // 还没有访问过
            board[i][j] = 3; 
            q.push(Position(i, j));
        }
    }

    // LR -- 4
    i = pos.i + 2;
    j = pos.j + 1;
    if (n > i && n > j)
    {
        if (0 == board[i][j])
        {
            // 还没有访问过
            board[i][j] = 4; 
            q.push(Position(i, j));
        }
    }

    // LL -- 5
    i = pos.i + 2;
    j = pos.j - 1;
    if (n > i && 0 <= j)
    {
        if (0 == board[i][j])
        {
            // 还没有访问过
            board[i][j] = 5; 
            q.push(Position(i, j));
        }
    }

    // L -- 6
    i = pos.i;
    j = pos.j - 2;
    if (0 <= j)
    {
        if (0 == board[i][j])
        {
            // 还没有访问过
            board[i][j] = 6; 
            q.push(Position(i, j));
        }
    }
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif
    
#if DEBUG
    inFile >> n;
#else
    cin >> n;
#endif

    int i_start, j_start, i_end, j_end;
#if DEBUG
    inFile >> i_start >> j_start >> i_end >> j_end;
#else
    cin >> i_start >> j_start >> i_end >> j_end;
#endif    

    queue<Position> q;
    Position start(i_start, j_start);

    // init
    pushToQ(q, start);

    while (0 < q.size())
    {
        Position pos = q.front();
        pushToQ(q, pos);
        q.pop();
    }

    if (0 == board[i_end][j_end])
    {
        cout << "Impossible" << endl;
    }
    else
    {
        stack<string> stk;
        int i, j;
        i = i_end;
        j = j_end;

        while (i != i_start || j != j_start)
        {
            switch (board[i][j])
            {
            case 1:
                stk.push("UL");
                i += 2;
                j += 1;
                break;
            case 2:
                stk.push("UR");
                i += 2;
                j -= 1;
                break;
            case 3:
                stk.push("R");
                j -= 2;
                break;
            case 4:
                stk.push("LR");
                i -= 2;
                j -= 1;
                break;
            case 5:
                stk.push("LL");
                i -= 2;
                j += 1;
                break;
            default:
            case 6:
                stk.push("L");
                j += 2;
                break;
            }
        }

        cout << stk.size() << endl;

        while (0 < stk.size())
        {
            string str = stk.top();
            cout << str;
            stk.pop();

            if (0 < stk.size())
            {
                cout << " ";
            }
            else
            {
                cout << endl;
            }
        }
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
