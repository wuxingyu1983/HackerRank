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
#define MAX_L 10000000

map<unsigned int, unsigned long long> dp1;
map<unsigned int, unsigned long long> dp2;
map<unsigned int, unsigned long long> dp22;

unsigned long long getValueForKey(map<unsigned int, unsigned long long> &dp, unsigned int key)
{
    unsigned long long ret = 0;

    map<unsigned int, unsigned long long>::iterator it = dp.find(key);
    if (it != dp.end())
    {
        ret = it->second;
    }

    return ret;
}

unsigned long long func_c2(unsigned long long n)
{
    unsigned long long ret = 0;

    if (1 < n)
    {
        ret = n * (n - 1) / 2;
    }

    return ret;
}

unsigned long long func_c3(unsigned long long n)
{
    unsigned long long ret = 0;

    if (2 < n)
    {
        ret = n * (n - 1) * (n - 2) / 6;
    }

    return ret;
}

unsigned long long func_c4(unsigned long long n)
{
    unsigned long long ret = 0;

    if (3 < n)
    {
        ret = n * (n - 1) * (n - 2) * (n - 3) / 24;
    }

    return ret;
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int n;
#if DEBUG
    inFile >> n;
#else
    cin >> n;
#endif

    vector<unsigned int> inputs(n);
    for (size_t i_n = 0; i_n < n; i_n++)
    {
#if DEBUG
        inFile >> inputs[i_n];
#else
        cin >> inputs[i_n];
#endif
    }

    bool hasEG2 = false;
    unsigned int max_l = 0;

    // init dp1
    for (int i_n = 0; i_n < n; i_n++)
    {
        if (dp1[inputs[i_n]])
        {
            dp1[inputs[i_n]] = dp1[inputs[i_n]] + 1;
            hasEG2 = true;
        }
        else
        {
            dp1[inputs[i_n]] = 1;
        }

        if (inputs[i_n] > max_l)
        {
            max_l = inputs[i_n];
        }
    }

    unsigned long long cnt = 0;
    if (hasEG2)
    {
        // update dp2, dp22
        for (map<unsigned int, unsigned long long>::iterator it = dp1.begin(); it != dp1.end(); it++)
        {
            for (map<unsigned int, unsigned long long>::iterator pre = dp1.begin(); pre != it; pre++)
            {
                unsigned int l = it->first + pre->first;
                if (max_l < l)
                {
                    break;
                }

                if (!dp2[l])
                {
                    dp2[l] = 0;
                }
                if (!dp22[l])
                {
                    dp22[l] = 0;
                }

                dp22[l] += dp2[l] * it->second * pre->second + func_c2(it->second) * func_c2(pre->second);
                dp2[l] += it->second * pre->second;
            }

            if (1 < it->second)
            {
                unsigned int l = it->first + it->first;
                if (max_l < l)
                {
                    continue;
                }

                if (!dp2[l])
                {
                    dp2[l] = 0;
                }
                if (!dp22[l])
                {
                    dp22[l] = 0;
                }

                dp22[l] += dp2[l] * func_c2(it->second) + func_c4(it->second);
                dp2[l] += func_c2(it->second);
            }
        }

        for (map<unsigned int, unsigned long long>::iterator it = dp1.begin(); it != dp1.end(); it++)
        {
            if (2 <= it->second)
            {
                unsigned long long cnt3diff = 0;

                for (map<unsigned int, unsigned long long>::iterator pre = dp1.begin(); pre != it; pre++)
                {
                    if (3 <= it->second)
                    {
                        // 1 1 1 3
                        unsigned int l = it->first - pre->first;
                        unsigned long long c = getValueForKey(dp2, l);

                        // {l/2, l/2}
                        if (0 == (l & 1))
                        {
                            // l/2
                            c -= func_c2(getValueForKey(dp1, l / 2));
                        }

                        // {pre->first, x}
                        if (l > pre->first && getValueForKey(dp1, l - pre->first))
                        {
                            if (l != 2 * pre->first)
                            {
                                c -= getValueForKey(dp1, pre->first) * getValueForKey(dp1, l - pre->first);
                            }
                        }

                        c = c * pre->second;
                        cnt3diff += c;

                        if (3 * pre->first == it->first)
                        {
                            cnt += func_c3(pre->second) * func_c3(it->second);
                        }
                        else
                        {
                            if (2 * pre->first < it->first && getValueForKey(dp1, it->first - 2 * pre->first))
                            {
                                cnt += func_c2(pre->second) * getValueForKey(dp1, it->first - 2 * pre->first) * func_c3(it->second);
                            }
                        }
                    }
                }
                // 1 1 2 2
                cnt += getValueForKey(dp22, it->first) * func_c2(it->second);

                if (cnt3diff)
                {
                    cnt += func_c3(it->second) * cnt3diff / 3;
                }
            }
        }
    }

    cout << cnt << endl;

#if DEBUG
    inFile.close();
#endif
}
