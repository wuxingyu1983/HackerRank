#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void quick_sort(int s[], int l, int r)
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

int main() {
    FILE * fp;
    fp = fopen("input.txt", "r");

    int n;
    fscanf(fp, "%d", &n);
//    scanf("%d", &n);

    int * a = malloc(sizeof(int) * n);
    int * s = malloc(sizeof(int) * n);

    for (size_t i = 0; i < n; i ++) {
        fscanf(fp, "%d", &a[i]);
//        scanf("%d", &a[i]);
        s[i] = a[i];
    }

    quick_sort(s, 0, n - 1);

    int cnt = 0, rcnt = 0;
    for (size_t i = 0; i < n; i ++) {
        if (a[i] == s[i]) {
            cnt ++;
        }
        if (a[i] == s[n - 1 - i]) {
            rcnt ++;
        }
    }

    if (cnt > rcnt) {
        printf("%d\n", n - cnt - 1);
    }
    else {
        printf("%d\n", n - rcnt - 1);
    }

    fclose(fp);

    free(a);
    free(s);

    return 0;
}
