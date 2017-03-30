#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//快速排序
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

int getCnt(int * a, int n, int k, int index) {
  int ret = 0;

  int start = index + 1;
  int end = n - 1;

  if (k == (a[start] - a[index])) {
    ret ++;
  }

  if (k > (a[start] - a[index])) {
    while (start <= end) {
      int middle = (start + end) / 2;

      if (k == (a[middle] - a[index])) {
        ret ++;
        break;
      }

      if (k < (a[middle] - a[index])) {
        if (middle > 1) {
          end = middle - 1;
        }
        else {
          break;
        }
      }

      if (k > (a[middle] - a[index])) {
        if (middle < n - 1) {
          start = middle + 1;
        }
        else {
          break;
        }
      }
    }
  }

  return ret;
}

int main() {
  int n,k;
  scanf("%d %d", &n, &k);

  int * a = malloc(n * sizeof(int));
  for (int i = 0; i < n; i ++) {
    scanf("%d", &a[i]);
  }

  // quick sort
  quick_sort(a, 0, n - 1);

  int cnt = 0;

  for (int i = 0; i < n - 1; i ++) {
    cnt += getCnt(a, n, k, i);
  }

  printf("%d\n", cnt);

  return 0;
}
