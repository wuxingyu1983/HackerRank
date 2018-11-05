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

using namespace std;

long long c[10000];
long long sum[10000];

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int n, k;
#if DEBUG
    inFile >> n >> k;
#else
    cin >> n >> k;
#endif

    for (int i = 0; i < n; i ++)
    {
#if DEBUG
        inFile >> c[i];
#else
        cin >> c[i];
#endif        
    }

    for (int i = 0; i < n; i ++)
    {
        int prei = i - k - 1;
        int nxti = i + k;

        long long tmp = 0;

        if (0 <= prei)
        {
            if (0 == sum[prei])
            {
                continue;
            }
            tmp = sum[prei];
        }

        tmp += c[i];

        if (n > nxti)
        {
            if (0 == sum[nxti] || tmp < sum[nxti])
            {
                sum[nxti] = tmp;
            }
        }
        else {
            if (0 == sum[n - 1] || tmp < sum[n - 1])
            {
                sum[n - 1] = tmp;
            }
        }
    }

    cout << sum[n - 1] << "\n";

    return 0;
}