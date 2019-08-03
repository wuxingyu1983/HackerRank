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
#define MAX_A       1000000000

using namespace std;

// LIS，Longest Increasing Subsequence, Greedy

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

    vector<int> lis;
    lis.reserve(n);
    for (size_t i_n = 0; i_n < n; i_n++)
    {
        int a;
#if DEBUG
        inFile >> a;
#else
        cin >> a;
#endif

        a -= i_n + 1;
        if (a < 0)
        {
            continue;
        }

        if (0 == lis.size())
        {
            lis.push_back(a);
        }
        else
        {
            if (a >= lis.back())
            {
                lis.push_back(a);
            }
            else
            {
                vector<int>::iterator it = upper_bound(lis.begin(), lis.end(), a);
                lis[it - lis.begin()] = a;
            }
        }
    }

    cout << n - lis.size() << endl;    

#if DEBUG
    inFile.close();
#endif

    return 0;
}