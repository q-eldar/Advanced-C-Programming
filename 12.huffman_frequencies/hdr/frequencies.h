#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef unsigned char uchar;
typedef uint64_t Frequencies[256];

/**
   Open a file at path and either store the character frequencies in
   freq or set *error to strerror(errno).
   @freqs: initialized Frequencies of character to 0;
   @path: file location
   @error: error identifier of stderror(errno)
   @return: True, False
*/
bool calc_frequencies(Frequencies freqs, const char *path, const char **error);
