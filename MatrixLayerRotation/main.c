#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct position {
  unsigned int row;
  unsigned int column;
};

struct position g_ret;

void getNewPos(unsigned int m, unsigned int n, unsigned r, unsigned i, unsigned j) {
  // 确定第几圈
  unsigned int lap = 301;
  unsigned int direct = 0;
  if (lap > i) {
    lap = i;
    direct = 3;  // 向左
  }
  if (lap > (m - 1 - i)) {
    lap = m - 1 - i;
    direct = 1;  // 向右
  }
  if (lap > j) {
    lap = j;
    direct = 0;  // 向下
  }
  if (lap > (n - 1 - j)) {
    lap = n - 1 - j;
    direct = 2;  // 向上
  }

  // 确定周长
  unsigned int girth = 2 * (n - 2 * lap) + 2 * (m - 2 * lap) - 4;

  // 确定r对周长的模
  unsigned int step = r % girth;

//  printf("the lap is %u, direct is %u, girth is %u, step is %u, i is %u, j is %u\n", lap, direct, girth, step, i, j);

  // 计算新位置
  while (step) {
    if (0 == direct) {
      // 向下
      if (step > (m - 1 - lap - i)) {
        step -= (m - 1 - lap - i);
        i += (m - 1 - lap - i);
        direct = 1;
      }
      else {
        i += step;
        step = 0;
      }
//      printf("0 : i is %u, j is %u, step is %u\n", i, j, step);
    }
    else if (1 == direct) {
      // 向右
      if (step > (n - 1 - lap - j)) {
        step -= (n - 1 - lap - j);
        j += (n - 1 - lap - j);
        direct = 2;
      }
      else {
        j += step;
        step = 0;
      }
//      printf("1 : i is %u, j is %u, step is %u\n", i, j, step);
    }
    else if (2 == direct) {
      // 向上
      if (step > (i - lap)) {
        step -= (i - lap);
        i -= (i - lap);
        direct = 3;
      }
      else {
        i -= step;
        step = 0;
      }
//      printf("2 : i is %u, j is %u, step is %u\n", i, j, step);
    }
    else {
      // 向左
      if (step > (j - lap)) {
        step -= (j - lap);
        j -= (j - lap);
        direct = 0;
      }
      else {
        j -= step;
        step = 0;
      }
//      printf("3 : i is %u, j is %u, step is %u\n", i, j, step);
    }
  }

  g_ret.row = i;
  g_ret.column = j;
}

int main() {
//  FILE* fstream = fopen("input.txt", "r");
  unsigned int m, n, r;

  scanf("%u %u %u", &m, &n, &r);
//  fscanf(fstream, "%u", &n);

  unsigned int as[300][300];

  for (unsigned int i = 0; i < m; i ++) {
    for (unsigned int j = 0; j < n; j ++) {
      unsigned int a;
      scanf("%u", &a);
      getNewPos(m, n, r, i, j);
//      printf("a is %u, new row is %u, col is %u\n", a, g_ret.row, g_ret.column);
      as[g_ret.row][g_ret.column] = a;
    }
  }

  for (unsigned int i = 0; i < m; i ++) {
    for (unsigned int j = 0; j < n; j ++) {
      printf("%u", as[i][j]);
      if (j == n - 1) {
        printf("\n");
      }
      else {
        printf(" ");
      }
    }
  }

  return 0;
}
