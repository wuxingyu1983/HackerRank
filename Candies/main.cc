#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <numeric>

using namespace std;

#define DEBUG       0
#define MAX_N       100000

unsigned int arr[MAX_N];
unsigned int ranking[MAX_N];
unsigned int opranking[MAX_N];

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

    for (size_t i = 0; i < n; i++)
    {
#if DEBUG
        inFile >> arr[i];
#else
        cin >> arr[i];
#endif
    }

    ranking[0] = 1;
    for (size_t i = 1; i < n; i++)
    {
        if (arr[i] >= arr[i - 1])
        {
            if (0 == ranking[i - 1])
            {
                ranking[i - 1] = 1;
            }

            if (arr[i] == arr[i - 1])
            {
                ranking[i] = 1;
            }
            else
            {
                ranking[i] = ranking[i - 1] + 1;
            }
        }
    }

    opranking[n - 1] = 1;
    for (int i = n - 2; i >= 0; i--)
    {
        if (arr[i] >= arr[i + 1])
        {
            if (0 == opranking[i + 1])
            {
                opranking[i + 1] = 1;
            }

            if (arr[i] == arr[i + 1])
            {
                opranking[i] = 1;
            }
            else
            {
                opranking[i] = opranking[i + 1] + 1;
            }
        }
    }

    unsigned long long ans = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (ranking[i] >= opranking[i])
        {
            ans += ranking[i];
        }
        else
        {
            ans += opranking[i];
        }
    }
     
    cout << ans << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}