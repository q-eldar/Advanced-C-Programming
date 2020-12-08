#pragma once

#include <stdlib.h> 		/* size_t */

#include "frequencies.h"
#include "priority_queue.h"

typedef struct TreeNode {
  uchar character;
  size_t frequency;
  struct TreeNode* left;	/* left child */
  struct TreeNode* right;	/* right child */
}TreeNode;

/**
   Create a priority queue where the value at each node is a tree node
   containing a character and its frequency. Caller is responsible to
   destroy linked list.
   @freqs: precalculated array of characters frequencies
   @returns: head pointer to the linked list
*/
Node* make_huffman_pq(Frequencies freqs);
