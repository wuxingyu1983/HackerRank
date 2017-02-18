#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main() {
  unsigned int t;
  unsigned long long days[100];

  scanf("%d", &t);

  for (unsigned int i = 0; i < t; i++) {
    unsigned long long day;
    scanf("%llu", &day);
    days[i] = day;
  }

  for (unsigned int i = 0; i < t; i ++) {
    unsigned long long middle = sqrtl(days[i]);
//    printf("the middle is %llu\n", middle);
    if (1 == middle) {
      printf("odd\n");
    }
    else {
      if ( 0 == middle % 2) {
        printf("event\n");
      }
      else {
        printf("odd\n");
      }
    }
  }

  return 0;
}
