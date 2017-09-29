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
unsigned long long val[10001];

int main(){
    int t;
    cin >> t;

    vector<unsigned long long> output;

    for (size_t i = 2; i <= 10000; i++) {
        val[i] = val[i - 1] + i * (1 + i - 1) * (i - 1) / 2;
    }

    for(int a0 = 0; a0 < t; a0++){
        int n;
        cin >> n;

        output.push_back(2 * val[n]);
    }

    for(int a0 = 0; a0 < t; a0++){
        cout << output[a0] << endl;
    }

    return 0;
}
