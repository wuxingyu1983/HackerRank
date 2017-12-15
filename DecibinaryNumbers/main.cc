#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int main() {
    int q;

    scanf("%d", &q);

    vector<long long> input(q);
    vector<long long> sorted_input(q);
    vector<string> sorted_output(q);

    for (size_t i = 0; i < q; i++) {
        long long x;
        scanf("%lld", &x);

        input[i] = x;
        sorted_input[i] = x;
    }

    // sort
    sort(sorted_input.begin(), sorted_input.end());


    // output
    for (size_t i = 0; i < q; i++) {
        long long x = input[i];

        vector<long long>::iterator loc = upper_bound(sorted_input.begin(), sorted_input.end(), x);
        int pos = loc - sorted_input.begin();

        printf("%s\n", sorted_output[pos].c_str());
    }

    return 0;
}
