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
#include <set>

using namespace std;

#define MAX_C 1002
#define DEBUG 0

int nnum[MAX_C];

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    // init nnum
    for (int i = 1; i < MAX_C; i++)
    {
        int tmp = 0;
        if (0 <= i - 1)
        {
            tmp = 1 + nnum[i - 1];
        }

        if (0 <= i - 2)
        {
            if (tmp > 1 + nnum[i - 2])
            {
                tmp = 1 + nnum[i - 2];
            }
        }

        if (0 <= i - 5)
        {
            if (tmp > 1 + nnum[i - 5])
            {
                tmp = 1 + nnum[i - 5];
            }
        }

        nnum[i] = tmp;
    }

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

        vector<int> freq(MAX_C);
        int max = 0;
        int min = MAX_C;

        for (size_t i_n = 0; i_n < n; i_n++)
        {
            int chocolate;
#if DEBUG
            inFile >> chocolate;
#else
            cin >> chocolate;
#endif

            if (max < chocolate)
            {
                max = chocolate;
            }

            if (min > chocolate)
            {
                min = chocolate;
            }

            freq[chocolate]++;
        }

        long long ans = 0;
        long long ans1 = 0;
        long long ans2 = 0;

        for (size_t i = max; i > min; i--)
        {
            if (freq[i])
            {
                ans += (long long)freq[i] * (long long)nnum[i - min];
                ans1 += (long long)freq[i] * (long long)nnum[i - min + 1];
                ans2 += (long long)freq[i] * (long long)nnum[i - min + 2];
            }
        }

        ans1 += (long long)freq[min];
        ans2 += (long long)freq[min];

        if (ans > ans1)
        {
            ans = ans1;
        }

        if (ans > ans2)
        {
            ans = ans2;
        }

        cout << ans << endl;
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}