#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../hdr/hw02.h"

/** 
 * http://www.strudel.org.uk/itoa/
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.

 */
static char* itoa(int value, char* result, int base) {
  // check that the base if valid
  if (base < 2 || base > 36) { *result = '\0'; return result; }

  char* ptr = result, *ptr1 = result, tmp_char;
  int tmp_value;

  do {
    tmp_value = value;
    value /= base;
    *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
  } while ( value );

  *ptr-- = '\0';
  while(ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr--= *ptr1;
    *ptr1++ = tmp_char;
  }
  return result;
}

char* print_integer(int n, int radix, char *prefix){
  int is_negative = n < 0;

  const int numof_digits = 32;
  int prefix_size = strlen(prefix);
  const int size = is_negative + prefix_size + numof_digits + 1; 

  char *res = calloc(size, sizeof(char));
  char *tmp = res;

  if(is_negative){
    tmp[0] = '-';
    tmp++;
  }

  if(prefix_size > 0){
    strncpy(tmp, prefix, prefix_size);
    tmp += prefix_size;
  }

  tmp = itoa(n, tmp, radix);  
  res[size-1] = '\0';
  
  return res;
}
