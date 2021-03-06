#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define DEBUG       0

int LowerBound(int A[],int N,int K){
    int low , high , mid ;
    low = 0 ;
    high = N ;
    while(low <= high){
        mid = ( low + high ) / 2 ; // finding middle element
        if(A[mid] >= K && ( mid == 0 || A[mid-1] < K )) // checking conditions for lowerbound
            return mid ;
        else if(A[mid] >= K) // answer should be in left part
            high = mid - 1 ;
        else                // answer should in right part if it exists
            low = mid + 1 ;
    }
    return mid ; // this will execute when there is no element in the given array which >= K
}

int getEQTPos(int A[], int N, int K) {
    int pos = -1;

    if (A[N] >= K) {
        pos = LowerBound(A, N, K);
    }

    return pos;
}

void quick_sort(int s[], int l, int r)
{
  if (l < r)
  {
    int i = l, j = r, x = s[l];
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
    FILE * fp = stdin;

#if DEBUG
    fp = fopen("input.txt", "r");
#endif

    int N;
    fscanf(fp, "%d", &N);

    int * n = malloc(sizeof(int) * N);
    for (size_t i = 0; i < N; i++) {
        fscanf(fp, "%d", &n[i]);
    }

    int Q;
    fscanf(fp, "%d", &Q);

    long long * q = malloc(sizeof(long long) * Q);
    for (size_t i = 0; i < Q; i++) {
        long long tmp;
        fscanf(fp, "%lld", &tmp);

        if (0 == i) {
            q[i] = tmp;
        }
        else {
            q[i] = q[i - 1] + tmp;
        }
    }

    // quick sort
    quick_sort(n, 0, N - 1);

    unsigned long long * sums = malloc(sizeof(unsigned long long) * N);
    for (size_t i = 0; i < N; i++) {
        if (0 == i) {
            sums[i] = abs(n[i]);
        }
        else {
            sums[i] = sums[i - 1] + abs(n[i]);
        }
    }

    // find >= 0 pos
    int egt0_pos = getEQTPos(n, N - 1, 0);

    for (size_t i = 0; i < Q; i++) {
        if (0 == q[i]) {
            printf("%llu\n", sums[N - 1]);
        }
        else if (0 < q[i]) {
            int pos = getEQTPos(n, N - 1, (-1) * q[i]);

            unsigned long long sum = 0;

            if (-1 == pos) {
                sum = sums[N - 1] - q[i] * N;
            }
            else {
                if (0 < pos) {
                    sum += sums[pos - 1] - pos * q[i];
                }

                if (0 <= egt0_pos) {
                    if (0 < egt0_pos) {
                        sum += (sums[N - 1] - sums[egt0_pos - 1]) + (N - egt0_pos) * q[i];
                    }
                    else {
                        sum += sums[N - 1] + (N - egt0_pos) * q[i];
                    }
                }

                if (0 < egt0_pos) {
                    if (0 < pos) {
                        sum += q[i] * (egt0_pos - pos) - (sums[egt0_pos - 1] - sums[pos - 1]);
                    }
                    else {
                        sum += q[i] * egt0_pos - sums[egt0_pos - 1];
                    }
                }
                else {
                    if (0 < pos) {
                        sum += q[i] * (N - pos) - (sums[N - 1] - sums[pos - 1]);
                    }
                    else {
                        sum += q[i] * N - sums[N - 1];
                    }
                }
            }

            printf("%llu\n", sum);
        }
        else {
            // 0 > q[i]
            int pos = getEQTPos(n, N - 1, (-1) * q[i]);

            unsigned long long sum = 0;

            if (-1 == egt0_pos) {
                sum += sums[N - 1] - N * q[i];
            }
            else {
                if (0 < egt0_pos) {
                    sum += sums[egt0_pos - 1] - egt0_pos * q[i];
                }

                if (0 <= pos) {
                    if (0 < pos) {
                        sum += (sums[N - 1] - sums[pos - 1]) + (N - pos) * q[i];
                    }
                    else {
                        sum += sums[N - 1] + N * q[i];
                    }
                }

                if (0 > pos) {
                    if (0 < egt0_pos) {
                        sum += (sums[N - 1] - sums[egt0_pos - 1]) * (-1) - (N - egt0_pos) * q[i];
                    }
                    else {
                        sum += sums[N - 1] * (-1) - N * q[i];
                    }
                }
                else {
                    if (0 < egt0_pos) {
                        sum += (sums[pos - 1] - sums[egt0_pos - 1]) * (-1) - (pos - egt0_pos) * q[i];
                    }
                    else {
                        sum += sums[pos - 1] * (-1) - pos * q[i];
                    }
                }
            }

            printf("%llu\n", sum);
        }
    }

#if DEBUG
    fclose(fp);
#endif

    free(n);
    free(q);
    free(sums);

    return 0;
}
