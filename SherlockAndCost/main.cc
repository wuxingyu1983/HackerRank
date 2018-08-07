#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

vector<string> split_string(string);

int tmp[100000][101];

// Complete the cost function below.
int cost(vector<int>& B)
{
    int ret = 0;
    int cnt = B.size();

    for (int i = 0; i < cnt; i ++) {
        if (0 == i) {
            for (int b = 1; b <= B[i]; b ++) {
                tmp[i][b] = 0;
            }
        }
        else {
            for (int b = 1; b <= B[i]; b ++) {
                tmp[i][b] = max(abs(1 - b) + tmp[i - 1][1], abs(B[i - 1] - b) + tmp[i - 1][B[i - 1]]);
                if (i == (cnt - 1)) {
                    if (ret < tmp[i][b]) {
                        ret = tmp[i][b];
                    }
                }
            }
        }
    }

    return ret;
}

int main()
{
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++)
    {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<int> B(n);

        for (int i = 0; i < n; i++)
        {
            cin >> B[i];
        }

        int result = cost(B);

        cout << result << "\n";
    }

    return 0;
}


