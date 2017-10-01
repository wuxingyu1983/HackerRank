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

vector<unsigned int> primes;
unsigned char flag[1000000];
vector<unsigned int> output;

void init() {
    flag[0] = 1;
    for (size_t i = 1; i < 1000000; i++) {
        if (0 == flag[i]) {
            primes.push_back(i + 1);

            size_t j = i;
            while (j < 1000000) {
                flag[j] = 1;
                j += i + 1;
            }
        }
    }
}

int main(){
    int t;
    cin >> t;

    init();

    for(int a0 = 0; a0 < t; a0++){
        int n;
        cin >> n;

        output.push_back(primes[n - 1]);
    }

    for(int a0 = 0; a0 < t; a0++){
        cout << output[a0] << endl;
    }

    return 0;
}
