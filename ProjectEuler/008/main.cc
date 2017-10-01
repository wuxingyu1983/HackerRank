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

vector<unsigned int> output;

int main(){
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        int n;
        int k;
        cin >> n >> k;
        string num;
        cin >> num;

        int max = 1;
        int tmp = 1;
        size_t i;
        for (i = 0; i < k; i++) {
            tmp *= num[i] - '0';
        }
        max = tmp;

        while (i < num.size()) {
            if (0 == tmp) {
                tmp = 1;
                for (size_t j = 0; j < k; j++) {
                    tmp *= (num[i - j] - '0');
                }

                if (tmp > max) {
                    max = tmp;
                }
            }
            else {
                tmp /= (num[i - k] - '0');
                tmp *= (num[i] - '0');

                if (tmp > max) {
                    max = tmp;
                }
            }

            i ++;
        }

        output.push_back(max);
    }

    for (size_t i = 0; i < output.size(); i++) {
        cout << output[i] << endl;
    }

    return 0;
}
