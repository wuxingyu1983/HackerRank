#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

void quick_sort(int s[], int l, int r)
{
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
    int n;
    int hit;
    int t;
    scanf("%d %d %d", &n, &hit, &t);
    int * h = malloc(sizeof(int) * n);
    for(int h_i = 0; h_i < n; h_i++){
        scanf("%d",&h[h_i]);
    }

    quick_sort(h, 0, n - 1);

    int result = 0;

    while (t > 0 && result < n) {
        h[result] -= hit;
        if (0 >= h[result]) {
            result ++;
        }
        t --;
    }

    printf("%d\n", result);
    return 0;
}
