#include <cmath>
#include <cstdio>
#include <set>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

#define DEBUG       0

int main() {
    int t, d, m, over_shoot=0;

    set<int> free;
    set<int>::iterator first, last;

    for (int i = 1; i <= 100000 + 1; i++) {
        free.insert(i);
    }

    scanf("%d", &t);

    for (int i = 1; i <= t; i++) {
        scanf("%d %d", &d, &m);

        // first.value > d
        first = free.upper_bound(d);
        last = first;

        while (first != free.begin() && m > 0) {
            first--;
            m--;
        }

        free.erase(first, last);
        over_shoot += m;

        printf("%d\n", over_shoot);
    }

    return 0;
}
