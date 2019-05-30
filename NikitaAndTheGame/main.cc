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

#define DEBUG   0

int score(vector<long long> &sums, int begin, int end)
{
    int ret = 0;

    if (begin < end && 0 == ((sums[end] - sums[begin - 1]) & 1))
    {
        // even
        long long half = (sums[end] - sums[begin - 1]) / 2 + sums[begin - 1];
        vector<long long>::iterator it = lower_bound(sums.begin() + begin, sums.begin() + end, half);
        if (half == *it)
        {
            ret ++;
            int left = score(sums, begin, it - sums.begin());
            int right = score(sums, it - sums.begin() + 1, end);
            if (left > right)
            {
                ret += left;
            }
            else
            {
                ret += right;
            }
        } 
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

    for (size_t i_t = 0; i_t < t; i_t++)
    {
        int n;
#if DEBUG
        inFile >> n;
#else
        cin >> n;
#endif

        vector<int> arr;
        vector<long long> sums;
        long long tmp_sum = 0;
        sums.push_back(tmp_sum);
        for (size_t i_n = 0; i_n < n; i_n++)
        {
            int tmp;
#if DEBUG
            inFile >> tmp;
#else
            cin >> tmp;
#endif
            arr.push_back(tmp);

            tmp_sum += (long long)tmp;
            sums.push_back(tmp_sum);
        }

        cout << score(sums, 1, n) << endl;
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
