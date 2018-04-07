#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MOD     1000000007

int main() {
    int n;
    scanf("%d", &n);

    vector<int> vec_m;
    vec_m.reserve(n);

    int m;
    for (size_t i = 0; i < n; i++) {
        scanf("%d", &m);
        vec_m.push_back(m);
    }

    return 0;
}
