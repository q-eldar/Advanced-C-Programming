#include <check.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define _GNU_SOURCE
#include <unistd.h>
#include <fcntl.h>

#include "../hdr/mintf.h"
/* diff -w <(./prime_factor) test_prime_factor.txt */
/* https://stackoverflow.com/questions/17071702/c-language-read-from-stdout */
START_TEST(test_mintf_integer_no_prefix){
  // this is for stdout backup
  int stdout_bk = dup(fileno(stdout));

  int pipefd[2];
  pipe2(pipefd, 0);

  /* Whaat used to be stdout will now go to the pipe */
  dup2(pipefd[1], fileno(stdout));
  close(pipefd[1]);

  {
    mintf("%d",12);
    fflush(stdout);
    char buf[3];
    const int num_red = read(pipefd[0], buf, 3);
    char actual[num_red + 1];
    strncpy(actual, buf, num_red);
    actual[num_red] = '\0';
    ck_assert_str_eq(actual, "12");
  }

  {
    mintf("%d",INT_MAX);
    fflush(stdout);
    char buf[11];
    const int num_red = read(pipefd[0], buf, 11);
    char actual[num_red + 1];
    strncpy(actual, buf, num_red);
    actual[num_red] = '\0';
    ck_assert_str_eq(actual, "2147483647");
  }

  {
    mintf("%d",INT_MIN);
    fflush(stdout);
    char buf[12];
    const int num_red = read(pipefd[0], buf, 12);
    char actual[num_red + 1 ];
    strncpy(actual, buf, num_red);
    actual[num_red] = '\0';
    ck_assert_str_eq(actual, "-2147483648");
  }
  
  {
    mintf("%d",0);
    fflush(stdout);
    char buf[1];
    const int num_red = read(pipefd[0], buf, 1);
    char actual[num_red + 1];
    strncpy(actual, buf, num_red);
    actual[num_red] = '\0';
    ck_assert_str_eq(actual, "0");
  }
  
  dup2(stdout_bk, fileno(stdout));//restore
}END_TEST

START_TEST(test_mintf_integer_prefix_x){
  int stdout_bk = dup(fileno(stdout));

  int pipefd[2];
  pipe2(pipefd, 0);

  /* Whaat used to be stdout will now go to the pipe */
  dup2(pipefd[1], fileno(stdout));
  close(pipefd[1]);

  {
    mintf("%x",12);
    fflush(stdout);
    char buf[3];
    const int num_red = read(pipefd[0], buf, 3);
    char actual[num_red + 1];
    strncpy(actual, buf, num_red);
    actual[num_red] = '\0';
    ck_assert_str_eq(actual, "0xc");
  }

  {
    mintf("%x",INT_MAX);
    fflush(stdout);
    char buf[10];
    const int num_red = read(pipefd[0], buf, 10);
    char actual[num_red + 1];
    strncpy(actual, buf, num_red);
    actual[num_red] = '\0';
    ck_assert_str_eq(actual, "0x7fffffff");
  }

  {
    mintf("%x",INT_MIN);
    fflush(stdout);
    char buf[11];
    const int num_red = read(pipefd[0], buf, 11);
    char actual[num_red + 1 ];
    strncpy(actual, buf, num_red);
    actual[num_red] = '\0';
    ck_assert_str_eq(actual, "-0x80000000");
  }
  
  {
    mintf("%x",0);
    fflush(stdout);
    char buf[3];
    const int num_red = read(pipefd[0], buf, 3);
    char actual[num_red + 1];
    strncpy(actual, buf, num_red);
    actual[num_red] = '\0';
    ck_assert_str_eq(actual, "0x0");
  }

  dup2(stdout_bk, fileno(stdout));  
}END_TEST

START_TEST(test_mintf_integer_prefix_b){
  int stdout_bk = dup(fileno(stdout));

  int pipefd[2];
  pipe2(pipefd, 0);

  /* Whaat used to be stdout will now go to the pipe */
  dup2(pipefd[1], fileno(stdout));
  close(pipefd[1]);

  {
    mintf("this is binary %b format",12);
    fflush(stdout);
    char buf[100];
    const int num_red = read(pipefd[0], buf, 100);
    char actual[num_red + 1];
    strncpy(actual, buf, num_red);
    actual[num_red] = '\0';
    ck_assert_str_eq(actual, "this is binary 0b1100 format");
  }

  {
    mintf("%b",INT_MAX);
    fflush(stdout);
    char buf[34];
    const int num_red = read(pipefd[0], buf, 34);
    char actual[num_red + 1];
    strncpy(actual, buf, num_red);
    actual[num_red] = '\0';
    ck_assert_str_eq(actual, "0b1111111111111111111111111111111");
  }

  {
    mintf("%b",INT_MIN);
    fflush(stdout);
    char buf[35];
    const int num_red = read(pipefd[0], buf, 35);
    char actual[num_red + 1 ];
    strncpy(actual, buf, num_red);
    actual[num_red] = '\0';
    ck_assert_str_eq(actual, "-0b10000000000000000000000000000000");
  }
  
  {
    mintf("and %b zero",0);
    fflush(stdout);
    char buf[12];
    const int num_red = read(pipefd[0], buf, 12);
    char actual[num_red + 1];
    strncpy(actual, buf, num_red);
    actual[num_red] = '\0';
    ck_assert_str_eq(actual, "and 0b0 zero");
  }

  dup2(stdout_bk, fileno(stdout));  
}END_TEST

START_TEST(test_mintf_double_prefix_$){
  int stdout_bk = dup(fileno(stdout));

  int pipefd[2];
  pipe2(pipefd, 0);

  /* Whaat used to be stdout will now go to the pipe */
  dup2(pipefd[1], fileno(stdout));
  close(pipefd[1]);

  {
    mintf("%$",-12.12);
    fflush(stdout);
    char buf[7];
    const int num_red = read(pipefd[0], buf, 7);
    char actual[num_red + 1];
    strncpy(actual, buf, num_red);
    actual[num_red] = '\0';
    ck_assert_str_eq(actual, "-$12.12");
  }

  {
    mintf("%$",21474836.21876);
    fflush(stdout);
    char buf[14];
    const int num_red = read(pipefd[0], buf, 14);
    char actual[num_red + 1];
    strncpy(actual, buf, num_red);
    actual[num_red] = '\0';
    ck_assert_str_eq(actual, "$21474836.21");
  }

  {
    mintf("%$",-21474836.21876);
    fflush(stdout);
    char buf[36];
    const int num_red = read(pipefd[0], buf, 36);
    char actual[num_red + 1 ];
    strncpy(actual, buf, num_red);
    actual[num_red] = '\0';
    ck_assert_str_eq(actual, "-$21474836.21");
  }
  
  {
    mintf("%$",0);
    fflush(stdout);
    char buf[4];
    const int num_red = read(pipefd[0], buf, 4);
    char actual[num_red + 1];
    strncpy(actual, buf, num_red);
    actual[num_red] = '\0';
    ck_assert_str_eq(actual, "$0.0");
  }

  dup2(stdout_bk, fileno(stdout));  
}END_TEST

START_TEST(test_mintf_string){
  int stdout_bk = dup(fileno(stdout));

  int pipefd[2];
  pipe2(pipefd, 0);

  /* Whaat used to be stdout will now go to the pipe */
  dup2(pipefd[1], fileno(stdout));
  close(pipefd[1]);

  {
    mintf("%s","hello");
    fflush(stdout);
    char buf[5];
    const int num_red = read(pipefd[0], buf, 5);
    char actual[num_red + 1];
    strncpy(actual, buf, num_red);
    actual[num_red] = '\0';
    ck_assert_str_eq(actual, "hello");
  }
  
  dup2(stdout_bk, fileno(stdout));
}END_TEST

START_TEST(test_mintf_char){
  int stdout_bk = dup(fileno(stdout));

  int pipefd[2];
  pipe2(pipefd, 0);

  /* Whaat used to be stdout will now go to the pipe */
  dup2(pipefd[1], fileno(stdout));
  close(pipefd[1]);

  {
    mintf("%c",'c');
    fflush(stdout);
    char buf[1];
    const int num_red = read(pipefd[0], buf, 1);
    char actual[num_red + 1];
    strncpy(actual, buf, num_red);
    actual[num_red] = '\0';
    ck_assert_str_eq(actual, "c");
  }
  
  dup2(stdout_bk, fileno(stdout));  
}END_TEST

START_TEST(test_mintf_percent){
  int stdout_bk = dup(fileno(stdout));

  int pipefd[2];
  pipe2(pipefd, 0);

  /* Whaat used to be stdout will now go to the pipe */
  dup2(pipefd[1], fileno(stdout));
  close(pipefd[1]);

  {
    mintf("%%");
    fflush(stdout);
    char buf[1];
    const int num_red = read(pipefd[0], buf, 1);
    char actual[num_red + 1];
    strncpy(actual, buf, num_red);
    actual[num_red] = '\0';
    ck_assert_str_eq(actual, "%");
  }
  
  dup2(stdout_bk, fileno(stdout));
}END_TEST

START_TEST(test_mintf_not_format_string){
  int stdout_bk = dup(fileno(stdout));

  int pipefd[2];
  pipe2(pipefd, 0);

  /* Whaat used to be stdout will now go to the pipe */
  dup2(pipefd[1], fileno(stdout));
  close(pipefd[1]);

  {
    mintf("%z");
    fflush(stdout);
    char buf[2];
    const int num_red = read(pipefd[0], buf, 2);
    char actual[num_red + 1];
    strncpy(actual, buf, num_red);
    actual[num_red] = '\0';
    ck_assert_str_eq(actual, "%z");
  }
  
  dup2(stdout_bk, fileno(stdout));
}END_TEST

Suite *mintf_suite(void){
  Suite *s;
  TCase *tc_core;
  s = suite_create("mintf");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_mintf_integer_no_prefix);
  tcase_add_test(tc_core, test_mintf_integer_prefix_b);
  tcase_add_test(tc_core, test_mintf_integer_prefix_x);
  tcase_add_test(tc_core, test_mintf_double_prefix_$);
  tcase_add_test(tc_core, test_mintf_string);
  tcase_add_test(tc_core, test_mintf_char);
  tcase_add_test(tc_core, test_mintf_percent);
  tcase_add_test(tc_core, test_mintf_not_format_string);

  suite_add_tcase(s, tc_core);
  
  return s;
}
int main(){
  int no_failed = 0;
  Suite *s;
  SRunner *runner;

  s = mintf_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;  
}
