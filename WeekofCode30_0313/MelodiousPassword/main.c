#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

// flag - 0; 1 - last v; 2 - last c
void print_pwd(char *p, int flag, int pos, int last) {
  char v[] = "aeiou";
  char c[] = "bcdfghjklmnpqrstvwxz";

  if (0 == flag) {
    for (int i = 0; i < 5; i ++) {
      p[pos] = v[i];
      if (pos < last) {
        print_pwd(p, 1, pos + 1, last);
      }
      else {
        printf("%s\n", p);
      }
    }
    for (int i = 0; i < 20; i ++) {
      p[pos] = c[i];
      if (pos < last) {
        print_pwd(p, 2, pos + 1, last);
      }
      else {
        printf("%s\n", p);
      }
    }
  }
  else if (1 == flag) {
    for (int i = 0; i < 20; i ++) {
      p[pos] = c[i];
      if (pos < last) {
        print_pwd(p, 2, pos + 1, last);
      }
      else {
        printf("%s\n", p);
      }
    }
  }
  else {
    // 2 == flag
    for (int i = 0; i < 5; i ++) {
      p[pos] = v[i];
      if (pos < last) {
        print_pwd(p, 1, pos + 1, last);
      }
      else {
        printf("%s\n", p);
      }
    }
  }
}

int main(){
    int n;
    scanf("%d",&n);

    char p[7];
    memset(p, 0, 7);

    print_pwd(p, 0, 0, n - 1);

    return 0;
}
