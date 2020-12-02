#pragma once

#include <stdio.h>		/* size_t */
/** 
   List node struncture
   @val: string 
   @next: pointer to the next node
 */
typedef struct Node {
  char* val;
  struct Node *next;
} Node;

/**
   Removes nth node starting at *node repeatedly until just one node
   remains.
   @node: reference to head pointer
   @n: element position to be remove [1-INT_MAX]
   $return: void
  */
void choose_winner(struct Node **node, int n);

/**
   Creates a circular linked list of struct Node objects. 
   @paramaters: variable sized arguments (0 >= )
   $return: pointer to the list head or NULL
  */
struct Node* create_list(const char *first_name, ...);

/**
   Return true if and only if the list containing node includes a node
   having a string that matches name.
   @node: pointer to the list head
   @name: string that function looks for
   $return: True, False
  */
int has_name(const struct Node *node, const char *name);

/**
   Return true if and only if the given circular list contains nodes
   with strings that match every string in names in order starting
   head pointer to the list 
   @node: pointer to the list head
   @num_names: number of strings in @names 
   @name: array of names (>=1)
   $return: True, False
  */
int is_names(const struct Node *node, size_t num_names, const char **names);

/**
   Detach and free(…) every node in the circular linked list
   containing @node.
   @node: pointer to the list head
   $return: void(no fail is assumed)
  */
void destroy_list(struct Node **node);

/**
   Return the nth node in a circular linked list, starting with @node.
   @node: pointer to the list head
   @n: nth position function looks for (>=0) 
   #return: pointer to nth node, NULL
  */
Node* get_nth_node(struct Node *node, int n);

/**
   Detachs and return (*node) -> next. 
   @node: address of a node in a circular linked list
   #return: circular list of size 1, NULL
 */
Node* detach_next_node(struct Node **node);

/**
   Prints the circular linked list beginning with node in the format
   illustrated below or '\n';
   ┌["Avery"]─["Bob"]─["Chris"]┐
   └───────────────────────────┘
   @node: pointer to the list head 
   #return: void
  */
void print_list(const struct Node *node); 

