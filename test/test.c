#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"

#include "testHarness.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_variable_assignment() {
  int x = 1;
  TEST_ASSERT_TRUE_MESSAGE(x == 1, "Variable assignment failed.");
}

void test_multiplication(void) {
  int x = 30;
  int y = 6;
  int z = x / y;
  TEST_ASSERT_TRUE_MESSAGE(
      z == 5, "Multiplication of two integers returned incorrect value.");
}

void test_blinkNormal(void) {
  int count = 0;
  bool on = false;

  blink(&count, &on);
  TEST_ASSERT_TRUE_MESSAGE(count == 1, "Count was not incremented.");
  TEST_ASSERT_TRUE_MESSAGE(on == true, "'on' was not swapped.");

  blink(&count, &on);
  TEST_ASSERT_TRUE_MESSAGE(count == 2, "Count was not incremented.");
  TEST_ASSERT_TRUE_MESSAGE(on == false, "'on' was not swapped.");
}

void test_blinkSkip(void) {
  int count = 10;
  bool on = false;

  blink(&count, &on);
  TEST_ASSERT_TRUE_MESSAGE(count == 11,
                           "Count was not incremented from 10 to 11.");
  TEST_ASSERT_TRUE_MESSAGE(on == true,
                           "'on' was not swapped on 10th iteration.");

  blink(&count, &on);
  TEST_ASSERT_TRUE_MESSAGE(count == 0,
                           "Count was not reset from 11 to 0.");
  TEST_ASSERT_TRUE_MESSAGE(
      on == true, "'on' was incorrectly swapped on 11th iteration.");
}

void test_swapCaseLower(void) {
  TEST_ASSERT_TRUE_MESSAGE(swapCase('a') == 'A',
                           "'a' was not swapped to 'A'.");

  TEST_ASSERT_TRUE_MESSAGE(swapCase('z') == 'Z',
                           "'a' was not swapped to 'A'.");
}

void test_swapCaseUpper(void) {
  TEST_ASSERT_TRUE_MESSAGE(swapCase('A') == 'a',
                           "'A' was not swapped to 'a'.");
  TEST_ASSERT_TRUE_MESSAGE(swapCase('Z') == 'z',
                           "'Z' was not swapped to 'z'.");
}

void test_swapCaseIgnore(void) {
  TEST_ASSERT_TRUE_MESSAGE(
      swapCase('@') == '@',
      "'@' was incorrectly swapped for something else.");

  TEST_ASSERT_TRUE_MESSAGE(
      swapCase('[') == '[',
      "'[' was incorrectly swapped for something else.");

  TEST_ASSERT_TRUE_MESSAGE(
      swapCase('`') == '`',
      "'`' was incorrectly swapped for something else.");

  TEST_ASSERT_TRUE_MESSAGE(
      swapCase('{') == '{',
      "'{' was incorrectly swapped for something else.");
}

int main(void) {
  stdio_init_all();
  while (1) {
    sleep_ms(5000); // Give time for TTY to attach.
    printf("Start tests\n");
    UNITY_BEGIN();
    RUN_TEST(test_variable_assignment);
    RUN_TEST(test_multiplication);
    RUN_TEST(test_blinkNormal);
    RUN_TEST(test_blinkSkip);
    RUN_TEST(test_swapCaseLower);
    RUN_TEST(test_swapCaseUpper);
    RUN_TEST(test_swapCaseIgnore);
    sleep_ms(5000);
    UNITY_END();
  }
}
