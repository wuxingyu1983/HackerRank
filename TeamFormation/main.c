#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int getMin(int x[], int n) {
    int min = 1000001;

    int N = n;
    int count = 0;
    int * num = malloc(sizeof(int) * n);
    int * cnt = malloc(sizeof(int) * n);
    memset(cnt, 0, sizeof(int) * n);

    for (size_t i = 0; i < n; i++) {
        if (0 == count) {
            num[count] = x[i];
            cnt[count] ++;
            count ++;
        }
        else {
            if (x[i] == num[count - 1]) {
                cnt[count - 1] ++;
            }
            else {
                num[count] = x[i];
                cnt[count] ++;
                count ++;
            }
        }
    }

    int start = 0;
    int index = start;
    int tmp = 0;

    while (N > 0) {
        if (index < count - 1) {
            if ((num[index] != (num[index + 1] - 1)) || (cnt[index] > cnt[index + 1])) {
                // stop
                tmp ++;
                if (tmp < min) {
                    min = tmp;
                    if (1 == min) {
                        break;
                    }
                }
                cnt[index] --;
                if (0 == cnt[index]) {
                    start = index ++;
                }
                else {
                    // restart
                    index = start;
                    tmp = 0;
                }
            }
            else {
                tmp ++;
                cnt[index] --;
                if (0 == cnt[index]) {
                    start = index + 1;
                }
                index ++;
            }
        }
        else {
            tmp ++;
            if (tmp < min) {
                min = tmp;
                if (1 == min) {
                    break;
                }
            }

            cnt[index] --;
            index = start;
            tmp = 0;
        }

        N --;
    }

    free(num);
    free(cnt);

    return min;
}

void quick_sort(int s[], int l, int r) {
    if (l < r)
    {
        int i = l, j = r;
        int x = s[l];
        while (i < j)
        {
            while(i < j && s[j] >= x)
            j--;
            if(i < j)
            s[i++] = s[j];

            while(i < j && s[i] < x)
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
    int t;
    scanf("%d", &t);

    int * output = malloc(sizeof(int) * t);
    int x[1000000];

    for (size_t i = 0; i < t; i++) {
        int n;
        scanf("%d", &n);

        for (size_t j = 0; j < n; j++) {
            scanf("%d", x + j);
        }

        // quick sort
        quick_sort(x, 0, n - 1);

        output[i] = getMin(x, n);
    }

    for (size_t i = 0; i < t; i++) {
        printf("%d\n", output[i]);
    }

    free(output);

    return 0;
}
