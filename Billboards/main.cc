#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    vector<int> revenues(n);
    long long sum = 0;

    for (size_t i = 0; i < n; i++) {
        int v;
        scanf("%d", &v);

        revenues[i] = v;
        sum += v;
    }

    priority_queue<long long> billboard;
    priority_queue<long long> abandon;
    vector<long long> ks(k + 1);

    // init -- 0
    billboard.push(0);
    billboard.push(revenues[0]);

    ks[0] = 0;

    for (size_t i = 1; i <= k; i++) {
        long long max = billboard.top();
        billboard.push(max - revenues[i]);

        ks[i] = max - revenues[i];
    }

    int pos = 0;
    for (size_t i = k + 1; i < n; i++) {
        
    }

    if (1 < n) {
        sum += billboard.top();
    }
    printf("%lld\n", sum);

    return 0;
}
