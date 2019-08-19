#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <limits.h>

#define DEBUG       0

using namespace std;

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    unsigned long long n, h;
#if DEBUG
    inFile >> n >> h;
#else
    cin >> n >> h;
#endif

    vector<unsigned long long> x(n);
    for (size_t i = 0; i < n; i++)
    {
#if DEBUG
        inFile >> x[i];
#else
        cin >> x[i];
#endif
    }

    if (0 == n || 0 == h)
    {
        cout << 0 << endl;
    }
    else
    {
        vector<int> lastFrom(n);
        vector<unsigned long long> cost(n);

        cost[0] = h;
        lastFrom[0] = 0;

        for (size_t i = 1; i < n; i++)
        {
            cost[i] = h + cost[i - 1];
            lastFrom[i] = i;

            if ((x[i] - x[i - 1]) * (x[i] - x[i - 1]) >= h)
            {
                continue;
            }
            else
            {
                for (int j = i - 1; j >= lastFrom[i - 1]; j--)
                {
                    unsigned long long tmp = h + (x[i] - x[j]) * (x[i] - x[j]);
                    if (0 < j)
                    {
                        tmp += cost[j - 1];
                    }

                    if (tmp < cost[i])
                    {
                        cost[i] = tmp;
                        lastFrom[i] = j;
                    }
                }
            }
        }

        cout << cost[n - 1] << endl;
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
