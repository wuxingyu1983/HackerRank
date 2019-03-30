//
//  main.cpp
//  test
//
//  Created by Julian on 2019/3/30.
//  Copyright © 2019 Julian. All rights reserved.
//

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

long long oneInPositive(long long to)
{
    long long ret = 0;

    long long step = 2;
    for (size_t bit = 0; bit < 31; bit++)
    {
        ret += (long long)((to + 1) / step) * (step / 2);
        if (((to + 1) / step) * step != (to + 1))
        {
            long long cnt = 0;
            cnt = (to + 1) - ((to + 1) / step) * step - step / 2;
            if (0 < cnt)
            {
                ret += cnt;
            }
        }

        step *= 2;
    }

    return ret;
}

long long oneInNegative(long long to)
{
    long long ret = 0;

    if (to == -2147483648)
    {
        ret += (0 - to) * 32 - oneInPositive(0 - to) + (0 - to) - 1;
    }
    else
    {
        ret += (0 - to) * 32 - oneInPositive(0 - to) + (0 - to);
    }

    unsigned int step = 1 << 31;
    long long cnt = 0;

    for (int bit = 31; bit > 0; bit--)
    {
        if (0 != (0 - to) / step)
        {
            ret -= ((0 - to) / step - cnt) * bit;
            cnt += (0 - to) / step - cnt;
        }

        step >>= 1;
    }

    return ret;
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int t;
#if DEBUG
    inFile >> t;
#else
    cin >> t;
#endif

    for (size_t i = 0; i < t; i++)
    {
        int a, b;
        long long cnt = 0;
#if DEBUG
        inFile >> a >> b;
#else
        cin >> a >> b;
#endif

        if (0 <= a)
        {
            // a, b >= 0
            if (0 == a)
            {
                cnt = oneInPositive(b);
            }
            else
            {
                cnt = oneInPositive(b) - oneInPositive(a - 1);
            }
        }
        else if (b <= 0)
        {
            // a, b <= 0
            if (0 == b)
            {
                cnt = oneInNegative(a);
            }
            else
            {
                cnt = oneInNegative(a) - oneInNegative(b + 1);
            }
        }
        else
        {
            // a < 0, b > 0
            cnt = oneInPositive(b) + oneInNegative(a);
        }

        cout << cnt << endl;
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
