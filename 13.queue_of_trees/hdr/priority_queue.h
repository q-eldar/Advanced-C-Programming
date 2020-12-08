#pragma once

/**
   Linked list node Structure for priority queue
   @a_value: generic value
   @@next: pointer to next node
*/
typedef struct Node {
	void* value;
	struct Node *next;
} Node;

/**
   Add a new node with value a_value to a priority queue, using
   function cmp_fn(…) to determine the ordering of the priority queue.
   @head_ref: reference to the head of the linked list
   @value: address of any value
   @cmp: function pointer that defiens order of nodes in a linked list
   @return: pointer to linked list head
*/
Node *pq_enqueue(Node **head_ref, void *value, int(*cmp)(const void*, const void*));

/**
   Detachs and returns the head
   @head_ref: reference to the head of the linked list
   @return: detached head pointer
*/
Node *pq_dequeue(Node **head_ref);

/**
   Destroys all nodes from the linked list with according @value
   @head_ref: reference to the head of the linked list
   @destroy_value: function pointer deallocates predifined generic value
*/
void destroy_list(Node **head_ref, void(*destroy_value)(void*));
