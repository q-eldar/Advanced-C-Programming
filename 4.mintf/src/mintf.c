#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#include "../hdr/mintf.h"
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

void print_integer(int n, int radix, char *prefix){
  int is_negative = n < 0;
  int prefix_size = strlen(prefix);

  char buf[33];
  char *tmp = itoa(n, buf, radix);
  const int numof_digits = strlen(tmp);
  
  const int size = is_negative + prefix_size + numof_digits + 1; 
  char *res = calloc(size, sizeof(char));

  if(is_negative){
    res[0] = '-';
  }

  if(prefix_size > 0){
    strncat(res, prefix, strlen(prefix));
  }

  strncat(res, tmp, numof_digits);
  /* res[size-1] = '\0'; */

  fputs(res, stdout);
  free(res);
}

void mintf(const char *format, ...){
  va_list varlist;
  va_start(varlist, format);

  const char *ptr;
  for(ptr = format; *ptr; ptr++){
    if(*ptr == '%'){
      ptr++;
      switch(*ptr){
      case 'd':
	print_integer(va_arg(varlist, int), 10, "");
	break;
      case 'x':
	print_integer(va_arg(varlist, int), 16, "0x");
	break;
      case 'b':
	print_integer(va_arg(varlist, int), 2, "0b");
	break;
      case '$':
	{
	  double d = va_arg(varlist, double);
	  print_integer((int)d, 10, "$");
	  fputc('.', stdout);
	  print_integer(abs(((int)(d*100)%100)), 10, "");
	}
	break;
      case 's':
	fputs(va_arg(varlist, char*), stdout);
	break;
      case 'c':
	fputc((char)va_arg(varlist, int), stdout);
	break;
      case '%':
	fputc('%', stdout);
	break;
      default:
	fputc('%', stdout);
	fputc(*ptr, stdout);
	break;
      }
    } else {
      fputc(*ptr, stdout);
    }
  }
}

