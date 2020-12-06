#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "../hdr/frequencies.h"

bool calc_frequencies(Frequencies freqs, const char *path, const char **error){
  FILE *fptr = fopen(path, "r");
  /*Check valid path to the file */
  if (fptr == NULL) {
    *error = strerror(errno);
    return false;
  }
  for (uchar ch = fgetc(fptr); !feof(fptr); ch = fgetc(fptr)) {
    freqs[(int)ch] += 1;
  }

  fclose(fptr);
  return true;
}



