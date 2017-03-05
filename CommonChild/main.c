#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
  //  FILE* fstream = fopen("input.txt", "r");
  char a[5001];
  char b[5001];

  scanf("%s", a);
  scanf("%s", b);
  //  fscanf(fstream, "%u", &n);

  unsigned int len = strlen(a);

  unsigned int * * c = malloc(sizeof(unsigned int *) * (len + 1));
  for (unsigned int i = 0; i <= len; i ++) {
    c[i] = malloc(sizeof(unsigned int) * (len + 1));
    memset(c[i], 0, sizeof(unsigned int) * (len + 1));
  }

  for (unsigned int i = 1; i <= len; i ++) {
    for (unsigned int j = 1; j <= len; j ++) {
      if (a[i - 1] == b[j - 1]) {
        c[i][j] = c[i - 1][j - 1] + 1;
      }
      else {
        if (c[i - 1][j] >= c[i][j - 1]) {
          c[i][j] = c[i - 1][j];
        }
        else {
          c[i][j] = c[i][j - 1];
        }
      }
    }
  }

  printf("%u\n", c[len][len]);

  for (unsigned int i = 0; i <= len; i ++) {
    free(c[i]);
  }
  free(c);

  return 0;
}
