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

vector<int>  arry_n(3001);
vector<int>  output;

void init() {
    for (size_t i = 1; i <= 1000; i++) {
        for (size_t j = i + 1; j <= 3000; j++) {
            int cc = i * i + j * j;
            int c = sqrt(cc);
            if (c + i + j > 3000) {
                break;
            }

            if (c * c == cc) {
                if (c * i * j > arry_n[c + i + j]) {
                    arry_n[c + i + j] = i * j * c;
                }
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

        if (arry_n[n]) {
            output.push_back(arry_n[n]);
        }
        else {
            output.push_back(-1);
        }
    }

    for (size_t i = 0; i < output.size(); i++) {
        cout << output[i] << endl;
    }

    return 0;
}
