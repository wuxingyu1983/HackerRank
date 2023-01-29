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
#include <iomanip>

using namespace std;

#define DEBUG 0
#define MAX_N 30001

unsigned int cnt[MAX_N];
unsigned int pa[MAX_N];

unsigned int find(size_t x)
{
    return pa[x] == x ? x : pa[x] = find(pa[x]);
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    unsigned int n;
#if DEBUG
    inFile >> n;
#else
    cin >> n;
#endif

    for (size_t i_n = 1; i_n <= n; i_n++)
    {
        unsigned int x, y;
#if DEBUG
        inFile >> x >> y;
#else
        cin >> x >> y;
#endif

        unsigned int pa_x, pa_y;
        pa_x = find(x);
        pa_y = find(y);

        if (0 == pa_x && 0 == pa_y)
        {
            pa[x] = x;
            pa[y] = x;

            cnt[x] += 2;
        }
        else if (0 == pa_x)
        {
            pa[x] = pa_y;

            cnt[pa_y] ++;
        }
        else if (0 == pa_y)
        {
            pa[y] = pa_x;
            cnt[pa_x] ++;
        }
        else
        {
            if (pa_x != pa_y)
            {
                if (pa_x < pa_y)
                {
                    cnt[pa_x] += cnt[pa_y];
                    cnt[pa_y] = 0;

                    pa[pa_y] = pa_x;
                }
                else
                {
                    cnt[pa_y] += cnt[pa_x];
                    cnt[pa_x] = 0;

                    pa[pa_x] = pa_y;
                }
            }
        }
    }

    unsigned int min = 0, max = 0;

    for (size_t i_n = 1; i_n <= n; i_n++)
    {
        if (cnt[i_n])
        {
            if (0 == min || cnt[i_n] < min)
            {
                min = cnt[i_n];
            }

            if (max < cnt[i_n])
            {
                max = cnt[i_n];
            }
        }
    }

    cout << min << " " << max << endl;

#if DEBUG
    inFile.close();
#endif
    return 0;
}