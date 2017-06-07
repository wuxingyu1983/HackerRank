#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

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
    scanf("%d", &n);

    int * a = malloc(sizeof(int) * n);
    for (size_t i = 0; i < n; i ++) {
        scanf("%d", a + i);
    }

    int p, q;
    scanf("%d %d", &p, &q);

    // quick sort
    quick_sort(a, 0, n - 1);

    int max = 0;
    int ans = 0;

    if (a[0] >= p) {
        max = a[0] - p;
        ans = p;
    }

    int left = a[0];
    int right = 0;

    for (size_t i = 1; i < n; i++) {
        right = a[i];

        if (left >= q) {
            break;
        }
        else if (right <= ) {
            /* code */
        }


        left = a[i];
    }

    printf("%d\n", ans);

    free(a);

    return 0;
}
