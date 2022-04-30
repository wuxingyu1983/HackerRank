#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <set>

using namespace std;

#define DEBUG   0

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

    long long min = -1;
    set<long long> price;
    for (size_t i = 0; i < n; i++)
    {
        long long p;
#if DEBUG
        inFile >> p;
#else
        cin >> p;
#endif

        set<long long>::iterator itup;
        itup = price.upper_bound(p);

        if (itup != price.end())
        {
            if (0 > min || min > *itup - p)
            {
                min = *itup - p;
            }
        }

        price.insert(p);
    }

    cout << min << endl;
}
