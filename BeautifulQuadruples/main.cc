#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

int main() {
    vector<int> a;
    a.resize(4);
    scanf("%d %d %d %d", &a[0], &a[1], &a[2], &a[3]);

    // sort, asc order
    sort(a.begin(), a.end());



    unsigned long long ret = 0;

    printf("%llu\n", ret);

    return 0;
}
