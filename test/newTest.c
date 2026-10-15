#include <stdio.h>
#include <stdint.h>
#include "newHeader.h"
#include "unity.h"
#include "pico/stdlib.h"

void setUp(void) {}

void tearDown(void) {}

// Test that count increments properly.
void test_count_increment()
{
    int count = 0;
    bool on = false;
    insideBlinkLoop(&count, &on);
    TEST_ASSERT_TRUE_MESSAGE(count == 1, "Count did not increment");
    insideBlinkLoop(&count, &on);
    TEST_ASSERT_TRUE_MESSAGE(count == 2, "Count did not increment");
    insideBlinkLoop(&count, &on);
    TEST_ASSERT_TRUE_MESSAGE(count == 3, "Count did not increment");
    insideBlinkLoop(&count, &on);
    TEST_ASSERT_TRUE_MESSAGE(count == 4, "Count did not increment");
}

// Test that on changes properly.
void test_count_again()
{
    int count = 0;
    bool on = false;
    insideBlinkLoop(&count, &on);
    TEST_ASSERT_TRUE_MESSAGE(on == false, "On changed on the first iteration");
    insideBlinkLoop(&count, &on);
    TEST_ASSERT_TRUE_MESSAGE(on == true, "On didn't change");
    insideBlinkLoop(&count, &on);
    TEST_ASSERT_TRUE_MESSAGE(on == false, "On didn't change");
    insideBlinkLoop(&count, &on);
    TEST_ASSERT_TRUE_MESSAGE(on == true, "On didn't change");
}

// Test that on changes properly at count = 11.
void test_on_variable_changes()
{
    int count = 10;
    bool on = false;
    insideBlinkLoop(&count, &on);
    TEST_ASSERT_TRUE_MESSAGE(on == true, "On didn't change correctly");
    insideBlinkLoop(&count, &on);
    TEST_ASSERT_TRUE_MESSAGE(on == true, "On didn't change correctly");
    insideBlinkLoop(&count, &on);
    TEST_ASSERT_TRUE_MESSAGE(on == false, "On didn't change correctly");
    insideBlinkLoop(&count, &on);
    TEST_ASSERT_TRUE_MESSAGE(on == true, "On didn't change correctly");
}

// This is basically an existance test
void test_variable_assignment()
{
    int x = 1;
    TEST_ASSERT_TRUE_MESSAGE(x == 1,"Variable assignment failed.");
}

// This is also a very simple test
void test_multiplication(void)
{
    int x = 5;
    int y = 6;
    int z = x * y;
    TEST_ASSERT_TRUE_MESSAGE(z == 30, "Multiplication of two integers returned incorrect value.");
}

// Entry Point: Loop forever, and each loop iteration wait 5 seconds,
// run the tests, and wait another 5 seconds.
int main (void)
{
    stdio_init_all();

    while (1) {
        sleep_ms(5000); // Give time for TTY to attach.
        printf("Start tests\n");
        UNITY_BEGIN();
        RUN_TEST(test_variable_assignment);
        RUN_TEST(test_multiplication);
        RUN_TEST(test_count_increment);
        RUN_TEST(test_count_again);
        RUN_TEST(test_on_variable_changes);
        sleep_ms(5000);
        UNITY_END();
    }
}