#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//快速排序
void quick_sort(int s[], int l, int r)
{
  if (l < r)
  {
    int i = l, j = r, x = s[l];
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
  clock_t start,finish;
  double TheTimes;
  start=clock();

//  FILE* fstream = fopen("input", "r");

  int N, K;
  scanf("%d", &N);
  scanf("%d", &K);
//  fscanf(fstream, "%d", &N);
//  fscanf(fstream, "%d", &K);
  int arr[N];

  for(int i = 0; i < N; i++) {
//    fscanf(fstream, "%d", &arr[i]);
    scanf("%d",&arr[i]);
  }

  // quick sort
  quick_sort(arr, 0, N - 1);

  finish=clock();
  TheTimes=(double)(finish-start)/CLOCKS_PER_SEC;
//  printf("after sort : %f\n",TheTimes);

  long long unfair = 0;
  long long min = 0;
  long long offset = 0;
  long long tmp = 0;
  long long * d = malloc(sizeof(long long) * N);
  memset(d, 0, sizeof(long long) * N);

  for (int i = 1; i < N; i ++) {
    d[i] = arr[i - 1] - arr[i];
    if (i < K) {
      unfair += d[i] * (K - i) * i;
      min = unfair;
      offset += d[i] * (K - 1 - 2 * (i - 1));
    }
    else {
      offset -= d[i] * (K - 1);
      if (i > K) {
        offset -= d[i - K] * (K - 1);
        offset += 2 * tmp;
      }
      unfair -= offset;
      if (min > unfair) {
        min = unfair;
      }
    }
    if (i > 1) {
      tmp += d[i];
    }
    if (i > K) {
      tmp -= d[i - K + 1];
    }
  }

  printf("%lld\n", min);

  finish=clock();
  TheTimes=(double)(finish-start)/CLOCKS_PER_SEC;
//  printf("finish : %f\n",TheTimes);

  return 0;
}
