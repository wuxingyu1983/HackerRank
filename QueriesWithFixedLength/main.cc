#include <deque>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>

using namespace std;

#define DEBUG       0

class A {
public:
    A(int index, int val) {
        m_index = index;
        m_val = val;
    }

    int m_index;
    int m_val;
};

int a[100000];
int out[100];

int main() {
    int n, q;

#if DEBUG
    ifstream fin("input.txt");
    if (!fin.is_open()) {
        printf("open file error!\n");
        return -1;
    }
    fin >> n >> q;
#else
    cin >> n >> q;
#endif

    for (size_t i = 0; i < n; i++) {
#if DEBUG
        fin >> a[i];
#else
        cin >> a[i];
#endif
    }

    int maxs[100000];
    for (size_t i = 0; i < q; i++) {
        int d;
        int min = 1000000;
#if DEBUG
        fin >> d;
#else
        cin >> d;
#endif
        deque<A> seq;

        for (int j = 0; j < n; j++) {
            maxs[j] = -1;
            if (0 == seq.size()) {
                seq.push_back(A(j, a[j]));
                if (1 == d) {
                    maxs[j] = a[j];
                    min = maxs[j];
                }
            }
            else {
                if (1 == d) {
                    maxs[j] = a[j];
                    if (min > maxs[j]) {
                        min = maxs[j];
                    }
                }
                else {
                    A first = seq.front();
                    if (first.m_val <= a[j]) {
                        // clear
                        seq.clear();
                        seq.push_back(A(j, a[j]));
                    }
                    else {
                        A last = seq.back();
                        if (last.m_val >= a[j]) {
                            seq.push_back(A(j, a[j]));
                        }
                        else {
                            //last.m_val < a[j]
                            while (last.m_val < a[j]) {
                                seq.pop_front();
                                last = seq.back();
                            }
                            seq.push_back(A(j, a[j]));
                        }
                    }

                    first = seq.front();
                    if (0 <= (j + 1 - d)) {
                        maxs[j + 1 - d] = first.m_val;
                        if (min > maxs[j + 1 - d]) {
                            min = maxs[j + 1 - d];
                        }

                        if (first.m_index <= (j + 1 - d)) {
                            seq.pop_front();
                        }
                    }
                }
            }
        }

        out[i] = min;
    }

    for (size_t i = 0; i < q; i++) {
#if DEBUG
        cout << out[i] << endl;
#else
        cout << out[i] << endl;
#endif
    }
}
