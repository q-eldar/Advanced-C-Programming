#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>

#include "../hdr/smintf.h"
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

const int print_integer(char *arr, int n, int radix, char *prefix){
  int is_negative = n < 0;
  int prefix_size = strlen(prefix);

  char buf[33];
  char *tmp = itoa(n, buf, radix);
  const int numof_digits = strlen(tmp);
  
  const int size = is_negative + prefix_size + numof_digits; 
  /* char *res = calloc(size, sizeof(char)); */

  if(is_negative){
    arr[0] = '-';
  }

  if(prefix_size > 0){
    strncat(arr, prefix, strlen(prefix));
  }

  strncat(arr, tmp, numof_digits);
  /* res[size-1] = '\0'; */

  /* fputs(res, stdout); */
  return size;
}

const char* smintf(const char *format, ...){
  va_list varlist;
  va_start(varlist, format);
  
  char *tmp = malloc(1024);
  char *buf = tmp;
  const char *ptr;
  
  for(ptr = format; *ptr; ptr++){
    if(*ptr == '%'){
      ptr++;
      switch(*ptr){
      case 'd':
	{
	  int n = print_integer(buf, va_arg(varlist, int), 10, "");
	  buf += n;
	}
	break;
      case 'x':
	{
	  int n = print_integer(buf, va_arg(varlist, int), 16, "0x");
	  buf += n;
	}
	break;
      case 'b':
	{
	  int n =print_integer(buf, va_arg(varlist, int), 2, "0b");
	  buf += n;
	}
	break;
      case '$':
	{
	  double d = va_arg(varlist, double);
	  int n = print_integer(buf, (int)d, 10, "$");
	  buf += n;
	  *(buf + n) = '.';
	  buf += 1;
	  n = print_integer(buf, abs(((int)(d*100)%100)), 10, "");
	  buf += n;
	}
	break;
      case 's':
	{
	  char *s = va_arg(varlist, char*);
	  int n = strlen(s);
	  strncat(buf, s, n);
	  buf += n;
	}
	break;
      case 'c':
	{
	  *buf = (char)va_arg(varlist, int);
	  buf += 1;
	}
	break;
      case '%':
	{
	  *buf = '%';
	  buf += 1;
	}
	break;
      default:
	*buf = '%';
	buf += 1;
	*buf = *ptr;
	buf += 2;
	break;
      }
    } else {
	*buf = *ptr;
	buf += 2;
    }
  }
  return tmp;
}

