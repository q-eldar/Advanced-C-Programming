#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>		/* strcmp() */
#include <sys/types.h>

#include "../hdr/cake.h"

/**
https://codereview.stackexchange.com/questions/104278/creating-a-linked-list-of-n-length
*/
struct Node* create_list(const char *first_name, ...){
  va_list ap;
  va_start(ap, first_name);
  Node list;
  list.next = NULL;
  Node *itr = &list;
  for(const char *val = first_name;  val != NULL; val = va_arg(ap, char*)){
    
    itr->next = malloc(sizeof(Node));
    itr = itr->next;
    
    size_t sz = strlen(val);
    itr->val = malloc(sz + 1);
    itr->val[sz] = '\0';
    strncpy(itr->val, val, sz);
    
  }
  va_end(ap);
  itr->next = list.next;
  return list.next;
}

void destroy_list(struct Node **node){
  struct Node *itr = *node;
  do{
    Node *temp = *node;
    *node = (*node)->next;
    free(temp->val);
    free(temp);
    temp = NULL;
  }while(itr != *node);
}

int has_name(const struct Node *node, const char *name){
  const Node *itr = node;
  int found = 0;
  do{
    if(strcmp(itr->val, name) == 0){
      found = 1;
      break;
    }
    itr = itr->next;
  }while(itr != node);
  
  return found;
}
