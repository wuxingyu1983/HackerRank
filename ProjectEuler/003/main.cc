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

vector<int> primes;
unsigned char flag[1000000];
vector<int> output;

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

int largest_prime_factor(int index, unsigned long long remain) {
    int ret = primes[index];

    int break_flag = 0;
    for (size_t i = index; i < primes.size() && primes[i] <= sqrt(remain); i++) {
        if (0 == remain % primes[i]) {
            if (1 == remain / primes[i]) {
                ret = primes[i];
            }
            else {
                ret = largest_prime_factor(i, remain / primes[i]);
            }
            break_flag = 1;
            break;
        }
    }

    if (0 == break_flag) {
        ret = remain;
    }

    return ret;
}

int main(){
    int t;
    cin >> t;

    init();

    for(int a0 = 0; a0 < t; a0++){
        unsigned long long n;
        cin >> n;

        int max = -1;
        unsigned long long half = sqrt(n);
        for (size_t i = 0; i < primes.size() && primes[i] <= half; i++) {
            if (0 == n % primes[i]) {
                if (1 == n / primes[i]) {
                    max = primes[i];
                }
                else {
                    max = largest_prime_factor(i, n / primes[i]);
                }
                break;
            }
        }

        if (0 > max) {
            output.push_back(n);
        }
        else {
            output.push_back(max);
        }
    }

    for (size_t i = 0; i < output.size(); i++) {
        cout << output[i] << endl;
    }

    return 0;
}
