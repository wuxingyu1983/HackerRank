#include <string>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <bitset>

#define MAX_N       100000000

using namespace std;

bitset<MAX_N / 2 + 1>   flag;
vector<int>     primes;
vector<int>     outputs;

void init() {
    flag[0] = 1;
    flag[1] = 1;

    for (size_t i = 2; i <= MAX_N / 2; i++) {
        if (0 == flag[i]) {
            // prime
            primes.push_back(i);

            int j = i;
            while (j <= MAX_N / 2) {
                flag[j] = 1;
                j += i;
            }
        }
    }
}

int main() {
    int t;
    cin >> t;

    init();

    for (size_t i = 0; i < t; i++) {
        int n;
        cin >> n;

        int ret = 0;

        n --;
        vector<int>::iterator pos = primes.begin();
        while (*pos <= sqrt(n)) {
            vector<int>::iterator loc = upper_bound(primes.begin(), primes.end(), (int)(n / *pos));
            ret += (loc - pos);

            pos ++;
        }

        outputs.push_back(ret);
    }

    for (size_t i = 0; i < outputs.size(); i++) {
        cout << outputs[i] << endl;
    }

    return 0;
}
