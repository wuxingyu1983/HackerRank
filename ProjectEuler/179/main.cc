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

#define MAX_K          10000000
#define MAX_T          1000000

using namespace std;

struct factor {
    int prime;
    int count;
};

int cnt[MAX_K + 1];
vector< vector<struct factor> > vec(MAX_K + 1);

void init() {
    int pre = -1;
    int now_cnt = 0;

    for (size_t i = 2; i <= MAX_K; i++) {
        if (0 == vec[i].size()) {
            // prime
            size_t j = i;
            while (j <= MAX_K) {
                size_t index = j;

                while (index <= MAX_K) {
                    if (0 == vec[index].size()) {
                        struct factor a;
                        a.prime = i;
                        a.count = 1;

                        vec[index].push_back(a);
                    }
                    else {
                        if (i != vec[index][vec[index].size() - 1].prime) {
                            struct factor a;
                            a.prime = i;
                            a.count = 1;

                            vec[index].push_back(a);
                        }
                        else {
                            vec[index][vec[index].size() - 1].count ++;
                        }
                    }

                    index += j;
                }

                j *= i;
            }
        }

        // calc cnt
        int now = 1;

        for (size_t j = 0; j < vec[i].size(); j++) {
            now *= (vec[i][j].count + 1);
        }

        if (now == pre) {
            now_cnt ++;
        }

        pre = now;

        cnt[i] = now_cnt;
    }
}

int main() {
    int t;
    cin >> t;

    init();
    vector<int> output;

    for (size_t i = 0; i < t; i++) {
        int k;
        cin >> k;

        output.push_back(cnt[k]);
    }

    for (size_t i = 0; i < output.size(); i++) {
        cout << output[i] << endl;
    }

    return 0;
}
