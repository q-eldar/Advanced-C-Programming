#include <check.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "../hdr/frequencies.h"

START_TEST(test_calc_frequency){
  Frequencies freq = {0};
  Frequencies expected = {0};

  expected[(uchar)'t'] = 4;
  expected[(uchar)'h'] = 3;
  expected[(uchar)'i'] = 4;
  expected[(uchar)'s'] = 2;
  expected[(uchar)'c'] = 1;
  expected[(uchar)'o'] = 2;
  expected[(uchar)'m'] = 1;
  expected[(uchar)'a'] = 1;
  expected[(uchar)'n'] = 4;
  expected[(uchar)'e'] = 6;
  expected[(uchar)'g'] = 1;
  expected[(uchar)'f'] = 1;
  expected[(uchar)'v'] = 2;
  expected[10] = 1; 		/* new line character */
  expected[32] = 8;
  const char *err;
  bool res = calc_frequencies(freq, "/home/me/projects/Advanced-C-Programming/12.huffman_frequencies/tests/input.txt", &err);
  ck_assert_int_eq(res, 1);
  
  ck_assert_int_eq(expected[(uchar)'t'], freq[(uchar)'t']);
  ck_assert_int_eq(expected[(uchar)'h'], freq[(uchar)'h']);
  ck_assert_int_eq(expected[(uchar)'i'], freq[(uchar)'i']);
  ck_assert_int_eq(expected[(uchar)'s'], freq[(uchar)'s']);
  ck_assert_int_eq(expected[(uchar)'c'], freq[(uchar)'c']);
  ck_assert_int_eq(expected[(uchar)'o'], freq[(uchar)'o']);
  ck_assert_int_eq(expected[(uchar)'m'], freq[(uchar)'m']);
  ck_assert_int_eq(expected[(uchar)'a'], freq[(uchar)'a']);
  ck_assert_int_eq(expected[(uchar)'n'], freq[(uchar)'n']);
  ck_assert_int_eq(expected[(uchar)'e'], freq[(uchar)'e']);
  ck_assert_int_eq(expected[(uchar)'g'], freq[(uchar)'g']);
  ck_assert_int_eq(expected[(uchar)'f'], freq[(uchar)'f']);
  ck_assert_int_eq(expected[(uchar)'v'], freq[(uchar)'v']);
  
  for(int i = 0; i < 256; i++){
    ck_assert_int_eq(expected[i], freq[i]);
  }
  
}END_TEST

Suite *test_suite(void){
  Suite *s = suite_create("freq");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_calc_frequency);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(){
  Suite *s = test_suite();
  SRunner *runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  int no_failed = srunner_ntests_failed(runner);

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

