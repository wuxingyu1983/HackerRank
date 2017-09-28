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

vector<int> input;

bool palindrome(int num) {
    bool ret = true;

    if (0 < (num / 100000)) {
        // 6
        int h = num / 100000;
        int l = num % 10;

        if (h != l) {
            return false;
        }

        h = (num / 10000) % 10;
        l = (num % 100) / 10;

        if (h != l) {
            return false;
        }

        h = (num / 1000) % 10;
        l = (num % 1000) / 100;

        if (h != l) {
            return false;
        }
    }
    else {
        // 5
        int h = num / 10000;
        int l = num % 10;

        if (h != l) {
            return false;
        }

        h = (num / 1000) % 10;
        l = (num % 100) / 10;

        if (h != l) {
            return false;
        }
    }

    return ret;
}

int main(){
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        int n;
        cin >> n;

        input.push_back(n);
    }
    vector<int> output(t, 0);

    for (size_t x = 999; x >= 100; x --) {
        for (size_t y = x; y >= 100; y--) {
            int product = x * y;
            if (palindrome(product)) {
                for (size_t i = 0; i < input.size(); i++) {
                    if (product < input[i]) {
                        if (0 == output[i] || product > output[i]) {
                            output[i] = product;
                        }
                    }
                }
            }
        }
    }

    for (size_t i = 0; i < output.size(); i++) {
        cout << output[i] << endl;
    }

    return 0;
}
