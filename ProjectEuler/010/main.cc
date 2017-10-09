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

vector<long long>  sum;
vector<long long>  output;
unsigned char flag[1000001];

void init() {
    flag[0] = 1;
    sum.push_back(0);
    flag[1] = 1;
    sum.push_back(0);
    long long tmp = 0;
    for (size_t i = 2; i <= 1000000; i++) {
        if (0 == flag[i]) {
            tmp += (long long)i;
            size_t j = i;
            while (j <= 1000000) {
                flag[j] = 1;
                j += i;
            }
        }

        sum.push_back(tmp);
    }
}

int main(){
    int t;
    cin >> t;

    init();

    for(int a0 = 0; a0 < t; a0++){
        int n;
        cin >> n;
        output.push_back(sum[n]);
    }

    for (size_t i = 0; i < output.size(); i++) {
        cout << output[i] << endl;
    }

    return 0;
}
