#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

#define DEBUG       0

using namespace std;

int main() {

#if DEBUG
    FILE * fp;
    fp = fopen("input.txt", "r");
#endif

    int n, k;

#if DEBUG
    fscanf(fp, "%d %d", &n, &k);
#else
    scanf("%d %d", &n, &k);
#endif

    vector<long long> revenues(n + 1);
    long long sum = 0;

    revenues[0] = 0;
    for (size_t i = 1; i <= n; i++) {
        long long v;

#if DEBUG
        fscanf(fp, "%lld", &v);
#else
        scanf("%lld", &v);
#endif

        revenues[i] = v;
        sum += v;
    }

    priority_queue<long long> billboard;
    priority_queue<long long> abandon;
    vector<long long> ks(k + 1);

    // init -- 0
    billboard.push(revenues[0]);

    ks[0] = revenues[0];

    for (size_t i = 1; i <= k; i++) {
        long long max = billboard.top();
        billboard.push(max - revenues[i]);

        ks[i] = max - revenues[i];
    }

    int pos = 0;
    for (size_t i = k + 1; i <= n; i++) {
        // campare billboard.top() and abandon.top()
        while (0 < abandon.size() && billboard.top() == abandon.top()) {
            billboard.pop();
            abandon.pop();
        }

        long long max = 0;
        if (billboard.top() == ks[pos]) {
            max = billboard.top();

            billboard.pop();
        }
        else {
            // add ks[pos] to abandon
            abandon.push(ks[pos]);

            max = billboard.top();
        }

        billboard.push(max - revenues[i]);

        ks[pos] = max - revenues[i];

        pos = (pos + 1) % (k + 1);
    }

    while (0 < abandon.size() && billboard.top() == abandon.top()) {
        billboard.pop();
        abandon.pop();
    }

    sum += billboard.top();

    printf("%lld\n", sum);

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
