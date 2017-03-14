#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main(){
  int n;
  scanf("%d",&n);

  for (int i = 0; i < n - 1; i ++) {
    printf("min(int, ");
  }

  printf("int");

  for (int i = 0; i < n - 1; i ++) {
    printf(")");
  }

  printf("\n");

  return 0;
}
