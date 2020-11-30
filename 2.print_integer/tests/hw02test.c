#include <check.h>
#include <stdlib.h>
#include <limits.h>

#include "../hdr/hw02.h"

START_TEST(test_base_2){
  char* res = print_integer(INT_MIN, 2, "$");
  ck_assert_str_eq(res, "-$10000000000000000000000000000000");
  
  res = print_integer(0, 2, "$$$");
  ck_assert_str_eq(res, "$$$0");

  res = print_integer(INT_MAX, 2, "");
  ck_assert_str_eq(res, "1111111111111111111111111111111");
  free(res);
} END_TEST

START_TEST(test_base_3){
  char* res = print_integer(INT_MIN, 3, "$");
  ck_assert_str_eq(res, "-$12112122212110202102");
  
  res = print_integer(0, 3, "$$$");
  ck_assert_str_eq(res, "$$$0");

  res = print_integer(INT_MAX, 3, "");
  ck_assert_str_eq(res, "12112122212110202101");
  free(res);
} END_TEST

START_TEST(test_base_10){
  char* res = print_integer(INT_MIN, 10, "$");
  ck_assert_str_eq(res, "-$2147483648");
  
  res = print_integer(0, 10, "$$$");
  ck_assert_str_eq(res, "$$$0");

  res = print_integer(INT_MAX, 10, "");
  ck_assert_str_eq(res, "2147483647");
  free(res);
} END_TEST

Suite *print_integer_suite(void){
  Suite *s;
  TCase *tc_core;
  s = suite_create("print_integer");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_base_10);
  tcase_add_test(tc_core, test_base_2);
  tcase_add_test(tc_core, test_base_3);
  
  suite_add_tcase(s, tc_core);
  return s;
}

int main(){
  int no_failed = 0;
  Suite *s;
  SRunner *runner;

  s = print_integer_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
