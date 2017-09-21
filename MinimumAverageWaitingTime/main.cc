#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#define DEBUG       0

class Customer {
public:
    Customer(int arrived, int required) {
        m_arrived = arrived;
        m_required = required;
    }

    int m_arrived;
    int m_required;
};

void quick_sort(vector<Customer> &s, int l, int r)
{
    if (l < r)
    {
        int i = l, j = r;
        Customer x = s[l];
        while (i < j)
        {
            while(i < j && x.m_arrived <= s[j].m_arrived)
                j--;
            if(i < j)
                s[i++] = s[j];

            while(i < j && x.m_arrived > s[i].m_arrived)
                i++;
            if(i < j)
                s[j--] = s[i];
        }
        s[i] = x;
        quick_sort(s, l, i - 1);
        quick_sort(s, i + 1, r);
    }
}

bool cmp(Customer &x,Customer &y) {
    return x.m_required > y.m_required;
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

    vector<Customer> customers;
    for (size_t i = 0; i < n; i++) {
        int arr, req;
#if DEBUG
        fin >> arr >> req;
#else
        cin >> arr >> req;
#endif

        customers.push_back(Customer(arr, req));
    }

    // sort
    quick_sort(customers, 0, customers.size() - 1);

    unsigned long long time = 0;
    unsigned long long wait = 0;

    vector<Customer>  min_heap;
    int cus_i = 0;

    while (min_heap.size() > 0 || cus_i < n) {
        // pizza finished
        if (0 < min_heap.size()) {
            pop_heap(min_heap.begin(), min_heap.end(), cmp);
            Customer srved = min_heap.back();
            min_heap.pop_back();

            time += srved.m_required;
            wait += (time - srved.m_arrived);
        }
        else {
            time = customers[cus_i].m_arrived;
        }

        // move customer to min_heap
        while (cus_i < n && time >= customers[cus_i].m_arrived) {
            min_heap.push_back(customers[cus_i]);
            push_heap(min_heap.begin(), min_heap.end(), cmp);
            cus_i ++;
        }
    }

    printf("%llu\n", wait / n);

    return 0;
}
