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

using namespace std;

int main(){
    int t;
    cin >> t;

    vector<int> output;
    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    for(int a0 = 0; a0 < t; a0++){
        int n;
        cin >> n;

        int product = 1;
        for (size_t i = 0; i < 12 && primes[i] <= n; i++) {
            int p = primes[i];
            while (p <= n) {
                product *= primes[i];
                p *= primes[i];
            }
        }

        output.push_back(product);
    }

    for(int a0 = 0; a0 < t; a0++){
        cout << output[a0] << endl;
    }
    return 0;
}
