#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct point {
    int x, y;
};

struct distance {
    int biker, bike, distance;
};

void quick_sort(struct distance s[], int l, int r)
{
  if (l < r)
  {
    int i = l, j = r;
    struct distance x = s[l];
    while (i < j)
    {
      while(i < j && s[j].distance >= x.distance)
      j--;
      if(i < j)
      s[i++] = s[j];

      while(i < j && s[i].distance < x.distance)
      i++;
      if(i < j)
      s[j--] = s[i];
    }
    s[i] = x;
    quick_sort(s, l, i - 1);
    quick_sort(s, i + 1, r);
  }
}

int LowerBound(struct distance A[],int l, int r,int K) {
    int low , high , mid ;
    low = l ;
    high = r ;
    while(low <= high){
        mid = ( low + high ) / 2 ; // finding middle element
        if(A[mid].distance >= K && ( mid == l || A[mid-1].distance < K )) // checking conditions for lowerbound
            return mid ;
        else if(A[mid].distance >= K) // answer should be in left part
            high = mid - 1 ;
        else                // answer should in right part if it exists
            low = mid + 1 ;
    }
    return mid ; // this will execute when there is no element in the given array which >= K
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

    struct distance * dist = malloc(sizeof(struct distance) * M * N);
    size_t index = 0;
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < M; j++) {
            dist[index].biker = i;
            dist[index].bike = j;
            dist[index].distance = abs(biker[i].x - bike[j].x) + abs(biker[i].y - bike[j].y);

            index ++;
        }
    }

    // quick sort
    quick_sort(dist, 0, N * M - 1);

    int l = 0;
    int r = N * M - 1;
    unsigned long long ret = 0;

    while (l <= r) {
        int min = dist[l].distance;
        int max = dist[r].distance;
        int mid = (min + max) / 2;

        // binary search
        int pos = LowerBound(dist, l, r, mid);
        if (pos < K - 1) {
            l = pos + 1;
        }
        else {
            unsigned char * fbr = malloc(sizeof(unsigned char) * N);
            unsigned char * fb = malloc(sizeof(unsigned char) * M);
            memset(fbr, 0, sizeof(unsigned char) * N);
            memset(fb, 0, sizeof(unsigned char) * M);

            int cnt = 0;
            int i;
            for (i = pos; i >= 0 && cnt < K; i--) {
                if (0 == fbr[dist[i].biker] && 0 == fb[dist[i].bike]) {
                    cnt ++;

                    fbr[dist[i].biker] = 1;
                    fb[dist[i].bike] = 1;
                }
            }

            if (i < 0) {
                // failed
                l = pos + 1;
            }
            else {
                // success
                r = pos - 1;
                ret = dist[pos].distance;
            }

            free(fbr);
            free(fb);
        }
    }

    printf("%llu\n", ret * ret);

    free(biker);
    free(bike);
    free(dist);

    return 0;
}
