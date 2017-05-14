#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MOD     1000000007

void quick_sort(unsigned int s[], int l, int r)
{
    if (l < r)
    {
        int i = l, j = r;
        unsigned int x = s[l];
        while (i < j)
        {
            while(i < j && s[j] <= x)
            j--;
            if(i < j)
            s[i++] = s[j];

            while(i < j && s[i] > x)
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
    int q;

    scanf("%d", &q);

    unsigned int * output = malloc(sizeof(unsigned int) * q);

    for (size_t i = 0; i < q; i++) {
        int m, n;
        scanf("%d %d", &m, &n);

        unsigned int * y = malloc(sizeof(unsigned int) * (m - 1));
        for (size_t j = 0; j < m - 1; j++) {
            scanf("%u", &y[j]);
        }

        unsigned int * x = malloc(sizeof(unsigned int) * (n - 1));
        for (size_t j = 0; j < n - 1; j++) {
            scanf("%u", &x[j]);
        }

        // sort - desc
        quick_sort(y, 0, m - 2);
        quick_sort(x, 0, n - 2);

        unsigned long long * sumy = malloc(sizeof(unsigned long long) * (m - 1));
        unsigned long long * sumx = malloc(sizeof(unsigned long long) * (n - 1));

        for (int j = m - 2; j >= 0; j --) {
            if (m - 2 == j) {
                sumy[j] = y[j];
            }
            else {
                sumy[j] = y[j] + sumy[j + 1];
            }
        }

        for (int j = n - 2; j >= 0; j --) {
            if (n - 2 == j) {
                sumx[j] = x[j];
            }
            else {
                sumx[j] = x[j] + sumx[j + 1];
            }
        }

        int yi = 0;
        int xi = 0;
        unsigned long long sum = 0;

        while (m - 2 >= yi || n - 2 >= xi) {
            long long costy = 0;
            long long costx = 0;

            if (m - 2 >= yi && n - 2 >= xi) {
                costy = ((long long)sumx[xi]) * (1 + yi);

                costx = ((long long)sumy[yi]) * (1 + xi);

                if (costy <= costx) {
                    sum += ((long long)y[yi]) * (1 + xi);
                    yi ++;
                }
                else {
                    sum += ((long long)x[xi]) * (1 + yi);
                    xi ++;
                }
            }
            else if (m - 2 >= yi) {
                sum += ((long long)y[yi]) * n;
                yi ++;
            }
            else {
                sum += ((long long)x[xi]) * m;
                xi ++;
            }

            sum %= MOD;
        }

        output[i] = sum;

        free(y);
        free(x);
        free(sumy);
        free(sumx);
    }

    for (size_t i = 0; i < q; i++) {
        printf("%u\n", output[i]);
    }

    free(output);

    return 0;
}
