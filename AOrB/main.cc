#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

#define DEBUG 0
#define MAX_LEN 50001

char mask[4] = {1, 2, 4, 8};
char rmask[4] = {14, 13, 11, 7};

using namespace std;

void aOrB(int k, string &tmp_a, string &tmp_b, string &tmp_c)
{
    char a[MAX_LEN], b[MAX_LEN], c[MAX_LEN];
    int len = tmp_a.length();
    if (len < tmp_b.length())
    {
        len = tmp_b.length();
    }
    if (len < tmp_c.length())
    {
        len = tmp_c.length();
    }

    // init a, b, c
    int index = 0;
    if (len > tmp_a.length())
    {
        index = len - tmp_a.length();
        memset(a, 0, index);
    }
    for (int i = 0; i < tmp_a.length(); i++)
    {
        if (tmp_a[i] >= '0' && tmp_a[i] <= '9')
        {
            a[index + i] = tmp_a[i] - '0';
        }
        else
        {
            a[index + i] = tmp_a[i] - 'A' + 10;
        }
    }
    a[len] = 0;

    index = 0;
    if (len > tmp_b.length())
    {
        index = len - tmp_b.length();
        memset(b, 0, index);
    }
    for (int i = 0; i < tmp_b.length(); i++)
    {
        if (tmp_b[i] >= '0' && tmp_b[i] <= '9')
        {
            b[index + i] = tmp_b[i] - '0';
        }
        else
        {
            b[index + i] = tmp_b[i] - 'A' + 10;
        }
    }
    b[len] = 0;

    index = 0;
    if (len > tmp_c.length())
    {
        index = len - tmp_c.length();
        memset(c, 0, index);
    }
    for (int i = 0; i < tmp_c.length(); i++)
    {
        if (tmp_c[i] >= '0' && tmp_c[i] <= '9')
        {
            c[index + i] = tmp_c[i] - '0';
        }
        else
        {
            c[index + i] = tmp_c[i] - 'A' + 10;
        }
    }
    c[len] = 0;

    // round 1
    for (int i = 0; i < len; i++)
    {
        for (int j = 3; j >= 0; j--)
        {
            if (((a[i] & mask[j]) | (b[i] & mask[j])) != (c[i] & mask[j]))
            {
                if (c[i] & mask[j])
                {
                    // 1
                    b[i] |= mask[j];
                    k--;
                }
                else
                {
                    // 0
                    if (a[i] & mask[j])
                    {
                        a[i] &= rmask[j];
                        k--;
                    }
                    if (b[i] & mask[j])
                    {
                        b[i] &= rmask[j];
                        k--;
                    }
                }
            }
        }
    }

    // round 2
    if (k < 0)
    {
        cout << "-1"
             << "\n";
        return;
    }
    else if (k > 0)
    {
        for (int i = 0; i < len; i++)
        {
            for (int j = 3; j >= 0; j--)
            {
                if ((a[i] & mask[j]) && (b[i] & mask[j]))
                {
                    a[i] &= rmask[j];
                    k--;
                    if (0 == k)
                    {
                        goto output;
                    }
                }
                else if ((a[i] & mask[j]) && 0 == (b[i] & mask[j]))
                {
                    if (k >= 2)
                    {
                        a[i] &= rmask[j];
                        b[i] |= mask[j];
                        k -= 2;
                        if (0 == k)
                        {
                            goto output;
                        }
                    }
                }
            }
        }
    }

output:
    int p = 0;
    for (int i = 0; i < len; i++)
    {
        if (a[i])
        {
            p = 1;
            if (a[i] <= 9)
            {
                char c = '0' + a[i] - 0;
                cout << c;
            }
            else
            {
                char c = 'A' + a[i] - 10;
                cout << c;
            }
        }
        else
        {
            if (p || i == (len - 1))
            {
                cout << "0";
            }
        }
    }
    cout << "\n";

    p = 0;
    for (int i = 0; i < len; i++)
    {
        if (b[i])
        {
            p = 1;
            if (b[i] <= 9)
            {
                char c = '0' + b[i] - 0;
                cout << c;
            }
            else
            {
                char c = 'A' + b[i] - 10;
                cout << c;
            }
        }
        else
        {
            if (p || i == (len - 1))
            {
                cout << "0";
            }
        }
    }
    cout << "\n";
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

    for (int q_itr = 0; q_itr < q; q_itr++)
    {
        int k;
#if DEBUG
        inFile >> k;
#else
        cin >> k;
#endif
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string tmp_a;
#if DEBUG
        getline(inFile, tmp_a);
#else
        getline(cin, tmp_a);
#endif

        string tmp_b;
#if DEBUG
        getline(inFile, tmp_b);
#else
        getline(cin, tmp_b);
#endif

        string tmp_c;
#if DEBUG
        getline(inFile, tmp_c);
#else
        getline(cin, tmp_c);
#endif

        aOrB(k, tmp_a, tmp_b, tmp_c);
    }

    return 0;
}
