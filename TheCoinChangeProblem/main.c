#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
  unsigned int m, n;
  scanf("%u %u", &n, &m);

  unsigned int * c;
  c = malloc(sizeof(unsigned int) * m);
  for (unsigned int i = 0; i < m; i ++) {
    unsigned int tmp;
    scanf("%u", &tmp);

    // 插入排序
    unsigned int j;
    for (j = 0; j < i; j ++) {
      if (c[j] > tmp) {
        for (unsigned int k = i; k > j; k --) {
          c[k] = c[k - 1];
        }
        break;
      }
    }
    c[j] = tmp;
  }


  return 0;
}
