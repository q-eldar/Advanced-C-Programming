#include <stdio.h>

int main(){
  FILE *fp = fopen("Makefile", "r");
  if(!fp)
    printf("cant open the file\n");
  return 0;
}
