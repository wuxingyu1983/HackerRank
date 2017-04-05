#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//快速排序
void quick_sort(unsigned long long s[], int l, int r)
{
  if (l < r)
  {
    int i = l, j = r, x = s[l];
    while (i < j)
    {
      while(i < j && s[j] > x)
      j--;
      if(i < j)
      s[i++] = s[j];

      while(i < j && s[i] <= x)
      i++;
      if(i < j)
      s[j--] = s[i];
    }
    s[i] = x;
    quick_sort(s, l, i - 1);
    quick_sort(s, i + 1, r);
  }
}

// mark function
void mark(unsigned long long *a, unsigned char *flag, unsigned long long value, int total) {
    int start = 0;
    int end = total - 1;

    while (start <= end) {
        int middle = (start + end) / 2;
        if (a[middle] > value) {
            if (1 < middle) {
                end = middle - 1;
            }
        }
        else if (a[middle] < value) {
            if (middle < total - 1) {
                start = middle + 1;
            }
        }
        else {
//            printf("want to mark value is %llu, middle is %d\n", value, middle);
            while (middle > 0 && value == a[middle - 1]) {
                middle --;
            }

            while (middle < total + 1 && value == a[middle] && flag[middle]) {
                middle ++;
            }

            if (value == a[middle]) {
                flag[middle] = 1;
//                printf("mark middle is %d, value is %llu\n", middle, value);
            }
            break;
        }
    }
}

/*
    a - input array;
    flag - 与 a 数组一一对应,标识已经命中过了, 0 / 1
    output - output array
    io - 当前 output 数组中确定的下标
*/
void func(unsigned long long *a, unsigned char *flag, int *output, int io, int total, int N, int K, int k, unsigned long long sum, int last) {
    if (0 == io) {
        sum += ((unsigned long long)output[io]) * k;

        // mark sum
        mark(a, flag, sum, total);
    }
    else {
        if (K == k) {
            for (int i = 1; i <= K; i ++) {
                func(a, flag, output, io - 1, total, N, K, k - i, sum + ((unsigned long long)output[io]) * i, last);
            }
            while (flag[++ last]) {
            }
            output[++io] = a[last] - ((unsigned long long)output[0]) * (K - 1);
//            printf("output[%d] is %d, last is %d\n", io, output[io], last);
            if (io < N - 1) {
                func(a, flag, output, io, total, N, K, K, 0, last);
            }
        }
        else {
            if (0 == k) {
                // mark sum
                mark(a, flag, sum, total);
            }
            else {
                for (int i = 0; i <= k; i ++) {
                    func(a, flag, output, io - 1, total, N, K, k - i, sum + ((unsigned long long)output[io]) * i, last);
                }
            }
        }
    }
}

int getCnt(int n, int k) {
    int ret = 0;

    if (1 == n || 0 == k) {
        return 1;
    }

    for (int i = 0; i <= k; i ++) {
        ret += getCnt(n - 1, k - i);
    }

    return ret;
}

int main() {
    int T, N, K;
    unsigned long long a[100000];
    unsigned char f[100000];
    unsigned int n[100000];

    scanf("%d", &T);
    int ** output = malloc(T * sizeof(int *));
    for (int i = 0; i < T; i ++) {
        scanf("%d %d", &N, &K);
        memset(a, 0, sizeof(unsigned long long) * 100000);
        memset(f, 0, 100000);

        int total = getCnt(N, K);
        n[i] = N;

        for (int j = 0; j < total; j ++) {
            scanf("%llu", &a[j]);
        }

        // quick sort
        quick_sort(a, 0, total - 1);

        output[i] = malloc(sizeof(int) * N + 1);
        memset(output[i], 0, sizeof(int) * (N + 1));

        output[i][0] = a[0] / K;
        f[0] = 1;
        if (1 < N) {
            output[i][1] = a[1] - ((unsigned long long)output[i][0]) * (K - 1);
        }

        if (2 < N) {
            func(a, f, output[i], 1, total, N, K, K, 0, 1);
        }
    }

    for (int i = 0; i < T; i ++) {
        printf("%d", output[i][0]);
        if (n[i] > 1) {
            for (int j = 1; j < n[i]; j ++) {
                printf(" %d", output[i][j]);
            }
        }
        printf("\n");

        free(output[i]);
    }
    free(output);

    return 0;
}
