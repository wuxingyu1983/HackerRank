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

#define DEBUG       0
#define MAX_LEN     5001
#define MAX_OPT     62

int cnt[MAX_LEN][MAX_LEN];
int rcnt[MAX_LEN][MAX_LEN];
char options[MAX_OPT];

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    string a, b;
#if DEBUG
    inFile >> a;
    inFile >> b;
#else
    cin >> a;
    cin >> b;
#endif

    for (int i = 0; i < a.length(); i++)
    {
        for (int j = 0; j < b.length(); j++)
        {
            if (a[i] == b[j])
            {
                if (0 == i || 0 == j)
                {
                    cnt[i][j] = 1;
                }
                else
                {
                    cnt[i][j] = cnt[i - 1][j - 1] + 1;                    
                }
            }
            else
            {
                cnt[i][j] = 0;

                if (0 < i)
                {
                    cnt[i][j] = cnt[i - 1][j];
                }

                if (0 < j)
                {
                    if (cnt[i][j] < cnt[i][j - 1])
                    {
                        cnt[i][j] = cnt[i][j - 1];
                    }
                }
            }
        }
    }

    for (int i = a.length() - 1; i >= 0; i--)
    {
        for (int j = b.length() - 1; j >= 0; j--)
        {
            if (a[i] == b[j])
            {
                if (i == a.length() - 1 || j == b.length() - 1)
                {
                    rcnt[i][j] = 1;
                }
                else
                {
                    rcnt[i][j] = rcnt[i + 1][j + 1] + 1;
                }
            }
            else
            {
                rcnt[i][j] = 0;

                if (a.length() - 1 > i)
                {
                    rcnt[i][j] = rcnt[i + 1][j];
                }

                if (b.length() - 1 > j)
                {
                    if (rcnt[i][j] < rcnt[i][j + 1])
                    {
                        rcnt[i][j] = rcnt[i][j + 1];
                    }
                }
            }
        }
    }

    int lcs_len = rcnt[0][0];
    lcs_len = cnt[a.length() - 1][b.length() - 1];
    int ret = 0;

    int index = 0;
    for (char ch = 'a'; ch <= 'z'; ch++)
    {
        options[index++] = ch;
    }

    for (char ch = 'A'; ch <= 'Z'; ch++)
    {
        options[index++] = ch;
    }

    for (char ch = '0'; ch <= '9'; ch++)
    {
        options[index++] = ch;
    }

    // insert before a[0]
    for (size_t opt = 0; opt < MAX_OPT; opt++)
    {
        char ch = options[opt];
        for (size_t j = 0; j < b.length(); j++)
        {
            if (ch == b[j])
            {
                int nlcs = 1;
                if (j < b.length() - 1)
                {
                    nlcs += rcnt[0][j + 1];
                }

                if (nlcs == lcs_len + 1)
                {
                    ret++;
                    break;
                }
            }
        }
    }

    for (size_t i = 0; i < a.length(); i++)
    {
        for (size_t opt = 0; opt < MAX_OPT; opt++)
        {
            char ch = options[opt];

            for (size_t j = 0; j < b.length(); j++)
            {
                if (ch == b[j])
                {
                    int nlcs = 1;
                    if (0 < j)
                    {
                        nlcs += cnt[i][j - 1];
                    }

                    if (i < a.length() - 1 && j < b.length() - 1)
                    {
                        nlcs += rcnt[i + 1][j + 1];
                    }

                    if (nlcs == lcs_len + 1)
                    {
                        ret++;
                        break;
                    }
                }
            }
        }
    }

    cout << ret << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
