#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

#define DEBUG   1
#define MOD     1000000007

void ninja(vector<int> &a)
{
    long long ret = 0;
    long long cnt[30][2];

    for (size_t i = 0; i < a.size(); i++)
    {
        int tmp = a[i];

        for (size_t bits = 0; bits < 30; bits++)
        {
            if (tmp & (1 << bits))
            {
                // 1
                if (0 == i)
                {
                    cnt[bits][1] = 1;
                    cnt[bits][0] = 0;
                }
                else
                {
                    long long n0 = cnt[bits][0];
                    long long n1 = cnt[bits][1];

                    // 1 xor 1 = 0
                    cnt[bits][0] += n1;

                    // 1 xor 0 = 1
                    cnt[bits][1] += n0;

                    ret += (long long)(1 << bits) * n0;
                    ret %= MOD;

                    cnt[bits][1] ++;
                }

                ret += (1 << bits);
                ret %= MOD;
            }
            else
            {
                // 0
                if (0 == i)
                {
                    cnt[bits][0] = 1;
                    cnt[bits][1] = 0;
                }
                else
                {
                    long long n0 = cnt[bits][0];
                    long long n1 = cnt[bits][1];

                    // 0 xor 1 = 1
                    cnt[bits][0] += n0;

                    // 0 xor 0 = 0
                    cnt[bits][1] += n1;

                    ret += (long long)(1 << bits) * n1;
                    ret %= MOD;

                    cnt[bits][0] ++;
                }
            }
            
            cnt[bits][1] %= MOD;
            cnt[bits][0] %= MOD;
        }
    }

    cout << ret << endl;
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

    for (size_t i_t = 0; i_t < t; i_t++)
    {
        int n;
#if DEBUG
        inFile >> n;
#else
        cin >> n;
#endif

        vector<int> a;
        a.reserve(n);

        for (size_t i_a = 0; i_a < n; i_a++)
        {
            int tmp;
#if DEBUG
            inFile >> tmp;
#else
            cin >> tmp;
#endif
            a.push_back(tmp);
        }

        ninja(a);
    }

#if DEBUG
    inFile.close();
#endif
}
