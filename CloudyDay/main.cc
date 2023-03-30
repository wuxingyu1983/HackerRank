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
#define MAX_N       200001
#define MAX_M       100001

class Town
{
public:
    unsigned int p, x;

    Town()
    {
        p = x = 0;
    }
};

class Cloud
{
public:
    unsigned int y, r;

    Cloud()
    {
        y = r = 0;
    }
};

vector<Town> towns(MAX_N);
vector<Cloud> clouds(MAX_M);

bool comp(Town &a, Town &b)
{
    return (a.x < b.x);
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

    for (size_t i = 0; i < n; i++)
    {
#if DEBUG
    inFile >> cities[i].p;
#else
    cin >> towns[i].p;
#endif
    }

    for (size_t i = 0; i < n; i++)
    {
#if DEBUG
    inFile >> cities[i].x;
#else
    cin >> towns[i].x;
#endif
    }

    int m;
#if DEBUG
    inFile >> m;
#else
    cin >> m;
#endif

    for (size_t i = 0; i < m; i++)
    {
#if DEBUG
    inFile >> clouds[i].y;
#else
    cin >> clouds[i].y;
#endif
    }

    for (size_t i = 0; i < m; i++)
    {
#if DEBUG
    inFile >> clouds[i].r;
#else
    cin >> clouds[i].r;
#endif
    }

    // sort cities
    sort(towns.begin(), towns.begin() + n, comp);

    

#if DEBUG
    inFile.close();
#endif

    return 0;
}
