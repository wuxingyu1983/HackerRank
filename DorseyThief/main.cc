#include <cmath>
#include <cstdio>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <limits.h>

#define DEBUG   0
#define MAX_X   5001

using namespace std;

unsigned long long sum[2][MAX_X];
vector<unsigned int> p[MAX_X];

bool cmp(unsigned int i, unsigned int j)
{
    return (i > j);
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int n, x;
#if DEBUG
    inFile >> n >> x;
#else
    cin >> n >> x;
#endif

    for (size_t i = 0; i < n; i++)
    {
        unsigned int v, a;
#if DEBUG
        inFile >> v >> a;
#else
        cin >> v >> a;
#endif

        if (a <= x)
        {
            p[a].push_back(v);
        }
    }

    for (size_t i = 1; i <= x; i++)
    {
        if (0 < p[i].size())
        {
            sort(p[i].begin(), p[i].end(), cmp);
        }
    }

    int index = 0;
    for (size_t i = 1; i <= x; i++)
    {
        if (0 < p[i].size())
        {
            memcpy(sum[index], sum[1 - index], (x + 1) * sizeof(unsigned long long));

            unsigned int step = 0;
            unsigned long long s = 0;
            for (vector<unsigned int>::iterator it = p[i].begin(); it != p[i].end(); it ++)
            {
                step += i;
                if (step > x)
                {
                    break;
                }
                else
                {
                    s += *it;
                    for (size_t j = 0; j <= x - step; j++)
                    {
                        if (0 == j || sum[1 - index][j])
                        {
                            if (sum[1 - index][j] + s > sum[index][j + step])
                            {
                                sum[index][j + step] = sum[1 - index][j] + s;
                            }
                        }
                    }
                }
            }

            index = 1 - index;
        }
    }

    index = 1 - index;

    if (sum[index][x])
    {
        cout << sum[index][x] << endl;
    }
    else
    {
        cout << "Got caught!" << endl;
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
