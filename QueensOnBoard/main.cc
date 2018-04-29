#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

#define DEBUG   0
#define MOD     1000000007
#define N       50
#define M       5

// row, major diagonal, minor diagonal
unsigned int status[2][1 << M][1 << M][1 << M];

bool valid_current(char sta, char board, int m) {
  bool ret = true;

  int pre_pos = -1;
  for (size_t pos = 0; pos < m; pos++) {
    if (sta & (1 << pos)) {
      if (board && (1 << pos)) {
        // blocked
        ret = false;
        break;
      }
      else {
        if (0 > pre_pos) {
          pre_pos = pos;
        }
        else {
          // no blocked square between pre_pos and pos
          ret = false;
          break;
        }
      }
    }
    else {
      if (board && (1 << pos)) {
        // blocked, clean pre pos
        pre_pos = -1;
      }
    }
  }

  return ret;
}

int main() {
  int t;

#if DEBUG
  FILE * fp = fopen("input.txt", "r");
  fscanf(fp, "%d", &t);
#else
  scanf("%d", &t);
#endif


  for (size_t i = 0; i < t; i++) {
    int n, m;

#if DEBUG
    fscanf(fp, "%d %d", &n, &m);
#else
    scanf("%d %d", &n, &m);
#endif

    unsigned char board[N];
    for (size_t row = 0; row < n; row++) {
      board[row] = 0;

      for (size_t col = 0; col < m; col++) {
        char c;
#if DEBUG
        fscanf(fp, "%c", &c);
#else
        scanf("%c", &c);
#endif

        if ('#' == c) {
          // a blocked square
          board[row] |= 1 << col;
        }
      }

      // process
      unsigned int ret = 0;
      for (size_t row = 0; row < n; row++) {
        for (size_t sta = 0; sta < (1 << m); sta++) {
          if (0 == row) {

          }
          else {

          }

          if ((n - 1) == row) {
            // last row

          }
        }
      }

      printf("%u\n", ret);
    }
  }


#if DEBUG
  fclose(fp);
#endif

  return 0;
}
