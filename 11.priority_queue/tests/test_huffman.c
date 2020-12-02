#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "../hdr/huffman.h"

/**
   Compares generic values
*/
static int cmp(const void *p1, const void* p2){
  return *(const int*)p1 - *(const int*)p2;
}

/**
   Setup for check framework
*/
Node* pq = NULL;
void setup(){
  int arr[] = {2, 3, 9, 7, 1, 2, 0, 6, 5};
  for(int i = 0; i < 9; i++){
    int *value = malloc(sizeof(int));
    *value = arr[i];
    pq_enqueue(&pq, value, cmp);
  }
}

/**
   Teardown for check framework
*/
void teardown(void) {
  destroy_list(&pq, free);
}

START_TEST(test_pq_enqueue) {
  int exp[] = {0, 1, 2, 2, 3, 5, 6, 7, 9};  
  int i = 0;
  while (pq) {
    ck_assert_int_eq(*(int*)pq->value, exp[i++]);
    pq = pq->next;
  }
}END_TEST

START_TEST(test_pq_denqueue) {
  int exp[] = {0, 1, 2, 2, 3, 5, 6, 7, 9};
  Node *itr = pq;
  int i = 0;
  while(itr != NULL){
    Node* temp = pq_dequeue(&pq);
    ck_assert_int_eq(*(int*)temp->value, exp[i++]);
    itr = itr->next;
  }
}END_TEST

START_TEST(test_destroy_list) {
  destroy_list(&pq, free);
  ck_assert_ptr_eq(pq, NULL);
}
END_TEST


Suite *priority_queue_suite(void){
  Suite *s = suite_create("priority queue");
  TCase *tc_core = tcase_create("Core");
  
  tcase_add_checked_fixture(tc_core, setup, teardown);
  tcase_add_test(tc_core, test_pq_enqueue);
  tcase_add_test(tc_core, test_pq_denqueue);
  tcase_add_test(tc_core, test_destroy_list);
  
  suite_add_tcase(s, tc_core);

  return s;
}

int main() {
  Suite *s = priority_queue_suite();
  SRunner *runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  int no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
