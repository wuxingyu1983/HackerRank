#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#define DEBUG       0

bool cmp(int x,int y) {
    return x > y;
}

int main() {
    int n;

#if DEBUG
    ifstream fin("input.txt");
    if (!fin.is_open()) {
        printf("open file error!\n");
        return -1;
    }
    fin >> n;
#else
    cin >> n;
#endif

    vector<int> max_heap;
    vector<int> min_heap;

    double * out = (double *)malloc(n * sizeof(double));

    for (size_t i = 0; i < n; i++) {
        int a;
#if DEBUG
        fin >> a;
#else
        cin >> a;
#endif
        if (0 == max_heap.size()) {
            max_heap.push_back(a);
        }
        else if (0 == min_heap.size()) {
            if (a > max_heap[0]) {
                min_heap.push_back(a);
            }
            else {
                // a <= max_heap[0]
                min_heap.push_back(max_heap[0]);
                max_heap.pop_back();
                max_heap.push_back(a);
            }
        }
        else {
            if (a < max_heap[0]) {
                if (max_heap.size() > min_heap.size()) {
                    // move max_heap[0] to min_heap
                    pop_heap(max_heap.begin(), max_heap.end());
                    int max = max_heap.back();
                    max_heap.pop_back();

                    min_heap.push_back(max);
                    push_heap(min_heap.begin(), min_heap.end(), cmp);
                }

                max_heap.push_back(a);
                push_heap(max_heap.begin(), max_heap.end());
            }
            else if (a > min_heap[0]){
                if (max_heap.size() == min_heap.size()) {
                    // move min_heap[0] to max_heap
                    pop_heap(min_heap.begin(), min_heap.end(), cmp);
                    int min = min_heap.back();
                    min_heap.pop_back();

                    max_heap.push_back(min);
                    push_heap(max_heap.begin(), max_heap.end());
                }

                min_heap.push_back(a);
                push_heap(min_heap.begin(), min_heap.end(), cmp);
            }
            else {
                // max_heap[0] <= a <= min_heap[0]
                if (max_heap.size() == min_heap.size()) {
                    // add a to max heap
                    max_heap.push_back(a);
                    push_heap(max_heap.begin(), max_heap.end());
                }
                else {
                    // add a to min heap
                    min_heap.push_back(a);
                    push_heap(min_heap.begin(), min_heap.end(), cmp);
                }
            }
        }

        if (max_heap.size() > min_heap.size()) {
            out[i] = (double)max_heap[0];
        }
        else {
            // max_heap.size() == min_heap.size()
            out[i] = ((double)(max_heap[0] + min_heap[0])) / 2;
        }
    }

    for (size_t i = 0; i < n; i++) {
        printf("%.1f\n", out[i]);
    }

    free(out);

    return 0;
}
