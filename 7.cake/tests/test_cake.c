#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../hdr/cake.h"

START_TEST(test_create_list){
  struct Node *list = create_list("1", "2", "3", "4", "5", "6", "7", NULL);
  struct Node *itr = list;
  int i = 1;
  do{
    static char buf[2];
    snprintf(buf, 2, "%d",i);
    ck_assert_str_eq(itr->val, buf);
    itr = itr->next;
    i++;
  }while(itr != list);
  
  static char buf[2];
  snprintf(buf, 2, "%d", 1);
  ck_assert_str_eq(itr->val, buf);
  
  destroy_list(&list);
}
END_TEST

START_TEST(test_has_name){
  Node *list = create_list("1", "2", "3", "4", "5", "6", "7", NULL);
  ck_assert_int_eq(has_name(list, "3"), 1);
  ck_assert_int_ne(has_name(list, "9"), 1);
}
END_TEST

Suite *cake_suite(void){
  Suite *s = suite_create("cacke");
  TCase *tc_core = tcase_create("Core");
  
  tcase_add_test(tc_core, test_create_list);
  tcase_add_test(tc_core, test_has_name);
  
  suite_add_tcase(s, tc_core);
  
  return s;
}

int main(){

  Suite *s = cake_suite(); 
  SRunner *runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  int no_failed  = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
