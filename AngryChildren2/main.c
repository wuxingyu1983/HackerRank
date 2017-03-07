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

  FILE* fstream = fopen("input", "r");

  int N, K;
//  scanf("%d", &N);
//  scanf("%d", &K);
  fscanf(fstream, "%d", &N);
  fscanf(fstream, "%d", &K);
  int arr[N];

  unsigned long long * s;
  unsigned long long * f;

  s = malloc(sizeof(unsigned long long) * N);
  memset(s, 0, sizeof(unsigned long long) * N);
  f = malloc(sizeof(unsigned long long) * N);
  memset(f, 0, sizeof(unsigned long long) * N);

  for(int i = 0; i < N; i++) {
    fscanf(fstream, "%d", &arr[i]);
    //    scanf("%d",&tmp);
  }

  // quick sort
  quick_sort(arr, 0, N - 1);

  finish=clock();
  TheTimes=(double)(finish-start)/CLOCKS_PER_SEC;
  printf("after sort : %f\n",TheTimes);

  unsigned long long unfair = 0;
  for (unsigned int i = 1; i < K; i ++) {
    for (unsigned int j = 0; j < N - i; j ++) {
      s[j] = s[j] + i * (arr[j + i - 1] - arr[j + i]);
      f[j] = f[j] + s[j];

      if (K - 1 == i) {
        if (0 == j) {
          unfair = f[j];
        }
        else {
          if (unfair > f[j]) {
            unfair = f[j];
          }
        }
      }
    }
  }

  printf("%llu\n", unfair);

  free(s);
  free(f);

  finish=clock();
  TheTimes=(double)(finish-start)/CLOCKS_PER_SEC;
  printf("finish : %f\n",TheTimes);

  return 0;
}
