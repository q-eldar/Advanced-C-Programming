#include "../hdr/huffman.h"
#include <stdio.h>
#include <stdlib.h>

Node *pq_enqueue(Node **head_ref, void *value,
                 int (*cmp)(const void *, const void *)){
  Node* new_node = (Node*)malloc(sizeof(Node));
  new_node->value = value;
  new_node->next = *head_ref;
  
  if( cmp == NULL || *head_ref == NULL || cmp(value, (*head_ref)->value) < 0){
    (*head_ref) = new_node;
  }else{
    new_node->next = (*head_ref)->next;
    (*head_ref)->next = new_node;
    Node* temp = *head_ref;
    while(new_node->next != NULL && cmp(new_node->value, new_node->next->value) >= 0){
      temp->next = new_node->next;
      new_node->next = temp->next->next;
      temp->next->next = new_node;
      temp = temp->next;
    }
  }
  return new_node;
}

Node *pq_dequeue(Node **head_ref){
  Node* removed_node = *head_ref;
  if(*head_ref != NULL ){
    *head_ref = (*head_ref)->next;
    removed_node->next = NULL;
  }
  return removed_node;
}

void destroy_list(Node **head_ref, void(*destroy_value)(void*)){
  while(*head_ref != NULL){
    Node* temp = pq_dequeue(head_ref);
    destroy_value(temp->value);
    free(temp);
    temp = NULL;
  }
}
