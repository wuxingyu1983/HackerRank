//
//  main.cpp
//  test
//
//  Created by Julian on 2019/3/27.
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
#include <iomanip>

using namespace std;

int getNewInt(int old, int bits, int pos)
{
    int ret = 0;

    if (0 == pos)
    {
        ret = old >> 1;
    }
    else if (pos == bits - 1)
    {
        ret = old & ((1 << pos) - 1);
    }
    else
    {
        ret = (old & ((1 << pos) - 1)) | ((old >> (pos + 1)) << pos);
    }

    return ret;
}

int main()
{
    int n, k;
    cin >> n >> k;

    string balls;
    cin >> balls;

    int db = 0;
    for (size_t i = 0; i < n; i++)
    {
        db <<= 1;
        if ('B' == balls[i])
        {
            db |= 1;
        }
    }

    float en = 0; // expected number

    int bit = n;
    vector<int> us_arry; // unique, sorted array
    us_arry.push_back(db);
    for (size_t i = 0; i < k; i++)
    {
        vector<int> arry; // temp
        for (size_t j = 0; j < us_arry.size(); j++)
        {
            int val = us_arry[j];
            int mask = 0;
            int count = 0;
            for (size_t k = 0; k < bit; k++)
            {
                if (0 == (val & (1 << k)) && 0 == (mask & (1 << k)))
                {
                    // white ball
                    if (2 * k == (bit - 1))
                    {
                        mask |= 1 << k;
                        count += 1;
                    }
                    else
                    {
                        mask |= 1 << k;
                        mask |= 1 << (bit - 1 - k);
                        count += 2;
                    }

                    int newInt = getNewInt(val, bit, k);
                    if (0 == arry.size())
                    {
                        arry.push_back(newInt);
                    }
                    else
                    {
                        if (newInt != arry[arry.size() - 1])
                        {
                            arry.push_back(newInt);
                        }
                    }
                }
            }

            en += (float)count / (float)(bit * us_arry.size());
        }

        // sort, unique
        sort(arry.begin(), arry.end());

        us_arry.clear();
        int pre = -1;
        for (size_t j = 0; j < arry.size(); j++)
        {
            if (pre < 0)
            {
                us_arry.push_back(arry[j]);
            }
            else if (pre != arry[j])
            {
                us_arry.push_back(arry[j]);
            }
            pre = arry[j];
        }

        bit--;
    }

    cout << fixed << setprecision(10) << en << endl;

    return 0;
}
