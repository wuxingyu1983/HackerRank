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

#define DEBUG 0

int n;

class Square
{
public:
    int a, b, d;
    int type;
    int minW;

    Square()
    {
        a = b = d = type = minW = 0;
    }
};

void updateSquare(Square &prev, Square &curr)
{
    if (prev.a == curr.a && prev.b == curr.b && prev.d == curr.d)
    {
        curr.minW = prev.minW;
    }
    else
    {
        int off_a = curr.a - prev.a;
        int off_b = curr.b - prev.b;

        if (0 == prev.type)
        {
            curr.minW = prev.minW + off_a + n * (prev.d - off_b - curr.d);
        }
        else if (1 == prev.type)
        {
            curr.minW = prev.minW + (prev.d - off_b - curr.d) + n * (prev.d - off_a - curr.d);
        }
        else if (2 == prev.type)
        {
            curr.minW = prev.minW + prev.d - off_a - curr.d + n * off_b;
        }
        else
        {
            // type : 3
            curr.minW = prev.minW + off_b + n * off_a;
        }
    }

    curr.type = (prev.type + 1) % 4;
}

bool inSquare(int j, Square &s)
{
    bool ret = false;

    if (0 == s.d)
    {
        if (j == s.minW)
        {
            ret = true;
        }
    }
    else
    {
        int l = 0;
        int r = s.d;
        int mid;

        while (l <= r)
        {
            mid = (l + r) / 2;
            if (j < (s.minW + n * mid))
            {
                r = mid - 1;
            }
            else if (j - s.minW - n * mid > s.d)
            {
                l = mid + 1;
            }
            else
            {
                ret = true;
                break;
            }
        }
    }

    return ret;
}

bool cmp(int j, Square &e)
{
    bool ret = true;

    if (inSquare(j, e))
    {
        ret = false;
    }
    
    return ret;
}

void printAB(int j, Square &s)
{
    int a = s.a, b = s.b;

    int l = 0;
    int r = s.d;
    int mid = 0;

    while (l <= r)
    {
        mid = (l + r) / 2;
        if (j < (s.minW + n * mid))
        {
            r = mid - 1;
        }
        else if (j - s.minW - n * mid > s.d)
        {
            l = mid + 1;
        }
        else
        {
            break;
        }
    }

    if (0 == s.type)
    {
        b += s.d - mid;
        a += j - (s.minW + n * mid);
    }
    else if (1 == s.type)
    {
        a += s.d - mid;
        b += s.d - (j - (s.minW + n * mid));
    }
    else if (2 == s.type)
    {
        b += mid;
        a += s.d - (j - (s.minW + n * mid));
    }
    else
    {
        // 3
        a += mid;
        b += j - (s.minW + n * mid);
    }

    cout << a << ' ' << b << endl;
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

    int s;
#if DEBUG
    inFile >> s;
#else
    cin >> s;
#endif

    vector<Square> squares(s);
    for (size_t i_s = 0; i_s < s; i_s++)
    {
        int a, b, d;
#if DEBUG
        inFile >> a >> b >> d;
#else
        cin >> a >> b >> d;
#endif

        squares[i_s].a = a;
        squares[i_s].b = b;
        squares[i_s].d = d;

        if (0 == i_s)
        {
            squares[i_s].type = 0;
            squares[i_s].minW = n * (a - 1) + (b - 1);
        }
        else
        {
            updateSquare(squares[i_s - 1], squares[i_s]);
        }
    }

    int l;
    #if DEBUG
        inFile >> l;
    #else
        cin >> l;
    #endif
    
    vector<int> js(l);
    for (size_t i_l = 0; i_l < l; i_l++)
    {
#if DEBUG
        inFile >> js[i_l];
#else
        cin >> js[i_l];
#endif
    }
    
    for (size_t i_l = 0; i_l < l; i_l++)
    {
        int j = js[i_l];

        if (false == inSquare(j, squares[0]))
        {
            int a, b;
            a = j / n + 1;
            b = j % n + 1;
            cout << a << ' ' << b << endl;
        }
        else
        {
            vector<Square>::iterator it = upper_bound(squares.begin(), squares.end(), j, cmp);
            it --;
            
            printAB(j, *it);
        }
    }

#if DEBUG
    inFile.close();
#endif
    
    return 0;
}
