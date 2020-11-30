#include <stdio.h>
#include <stdlib.h>

#include "hdr/hw02.h"

int main(){
  char* res = print_integer(12, 10, "");
  free(res);
}
