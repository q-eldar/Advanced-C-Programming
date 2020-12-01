#include <check.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

Suite *cake_suite(void){
  Suite *s = suite_create("cacke");
  TCase *tc_core = tcase_create("Core");
  
  /* tcase_add_test(tc_core, ); */

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
