#include <queue>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <time.h>
//#include <malloc.h>

using namespace std;

#define DEBUG       0

#define MAX_T       100
#define MAX_2       801
#define MAX_S       100001

int count[MAX_T];

int len_two[MAX_2];
vector<string> str_two(MAX_2);

void init() {
    for (size_t i = 0; i < MAX_2; i++) {
        if (0 == i) {
            str_two[i] = '1';
        }
        else {
            int carry = 0;
            int val = 0;
            for (size_t j = 0; j < str_two[i - 1].length(); j++) {
                val = (str_two[i - 1][j] - '0') * 2 + carry;
                if (9 < val) {
                    str_two[i] += '0' + val - 10;
                    carry = 1;
                }
                else {
                    str_two[i] += '0' + val;
                    carry = 0;
                }
            }

            if (0 < carry) {
                str_two[i] += '1';
            }
        }
    }
}

int two_two(string& s) {
    int ret = 0;


    return ret;
}

int main() {
    int t;

#if DEBUG
    ifstream fin("input.txt");
    if (!fin.is_open()) {
        printf("open file error!\n");
        return -1;
    }
    fin >> t;
#else
    cin >> t;
#endif

    init();

    string s;
    for (size_t i = 0; i < t; i++) {
#if DEBUG
        fin >> s;
#else
        cin >> s;
#endif
        count[i] = two_two(s);
    }

    for (size_t i = 0; i < t; i++) {
        cout << count[i];
    }

    return 0;
}
