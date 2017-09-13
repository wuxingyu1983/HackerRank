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

int output[MAX_T];

void init() {


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
        output[i] = two_two(s);
    }

    for (size_t i = 0; i < t; i++) {
        cout << output[i];
    }

    return 0;
}
