#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

int mx[250], my[250];   // X各點的配對對象、Y各點的配對對象
bool vy[250];           // 記錄Graph Traversal拜訪過的點

struct point {
    int x, y;
};

void quick_sort(unsigned long long s[], int l, int r)
{
  if (l < r)
  {
    int i = l, j = r;
    unsigned long long x = s[l];
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

int LowerBound(unsigned long long A[],int l, int r,unsigned long long val) {
    int low , high , mid ;
    low = l ;
    high = r ;
    while(low <= high){
        mid = ( low + high ) / 2 ; // finding middle element
        if(A[mid] >= val && ( mid == l || A[mid-1] < val )) // checking conditions for lowerbound
            return mid ;
        else if(A[mid] >= val) // answer should be in left part
            high = mid - 1 ;
        else                // answer should in right part if it exists
            low = mid + 1 ;
    }
    return mid ; // this will execute when there is no element in the given array which >= K
}

// 以DFS建立一棵交錯樹
bool DFS(int x, int n, int m, int k, unsigned long long * d, unsigned long long threhold)
{
    for (int y=0; y<m; ++y)
        if (d[x * m + y] <= threhold && !vy[y])
        {
            vy[y] = true;

            // 找到擴充路徑
            if (my[y] == -1 || DFS(my[y], n, m, k, d, threhold))
            {
                mx[x] = y; my[y] = x;
                return true;
            }
        }

    return false;
}

// Ford-Fulkerson Algorithm
bool FFA(int n, int m, int k, unsigned long long * d, unsigned long long threhold) {
    bool ret = false;

    // 全部的點初始化為未匹配點。
    memset(mx, -1, sizeof(mx));
    memset(my, -1, sizeof(my));

    // 依序把X中的每一個點作為擴充路徑的端點，
    // 並嘗試尋找擴充路徑。
    int c = 0;
    for (int x=0; x<n; ++x)
    {
        // 開始Graph Traversal
        memset(vy, false, sizeof(vy));
        if (DFS(x, n, m, k, d, threhold)) {
            c++;
            if (k <= c) {
                ret = true;
                break;
            }
        }
    }

    return ret;
}

int main() {
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);

    struct point * biker = malloc(sizeof(struct point) * N);
    for (size_t i = 0; i < N; i++) {
        int x, y;
        scanf("%d %d", &x, &y);

        biker[i].x = x;
        biker[i].y = y;
    }

    struct point * bike = malloc(sizeof(struct point) * M);
    for (size_t i = 0; i < M; i++) {
        int x, y;
        scanf("%d %d", &x, &y);

        bike[i].x = x;
        bike[i].y = y;
    }

    unsigned long long * dist = malloc(sizeof(unsigned long long) * N * M);
    unsigned long long * sorted = malloc(sizeof(unsigned long long) * N * M);
    size_t index = 0;
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < M; j++) {
            long long llx = biker[i].x - bike[j].x;
            long long lly = biker[i].y - bike[j].y;
            dist[index] = llx * llx + lly * lly;
            sorted[index] = dist[index];

            index ++;
        }
    }

    // quick sort
    quick_sort(sorted, 0, N * M - 1);

    int l = 0;
    int r = N * M - 1;
    unsigned long long ret = 0;

    while (l <= r) {
        unsigned long long min = sorted[l];
        unsigned long long max = sorted[r];
        unsigned long long mid = (min + max) / 2;

        // binary search
        int pos = LowerBound(sorted, l, r, mid);
        if (pos < K - 1) {
            l = pos + 1;
        }
        else {
            bool bOK = false;

            bOK = FFA(N, M, K, dist, sorted[pos]);

            if (true == bOK) {
                // success
                r = pos - 1;
                ret = sorted[pos];
            }
            else {
                // failed
                l = pos + 1;
            }
        }
    }

    printf("%llu\n", ret);

    free(biker);
    free(bike);
    free(dist);
    free(sorted);

    return 0;
}
