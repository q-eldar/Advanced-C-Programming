#include <string.h>		/* strcmp() */

#include "../hdr/cake.h"

/** 
   List node struncture
   @val: capital letter [A-Z]
   @next: pointer to the next node
 */
struct Node {
  char val;
  struct Node *next;
};
