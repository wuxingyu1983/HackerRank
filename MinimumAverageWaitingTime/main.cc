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

    
}
