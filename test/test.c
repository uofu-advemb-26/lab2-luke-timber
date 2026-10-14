#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>

void setUp(void) {}

void tearDown(void) {}

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
        sleep_ms(5000);
        UNITY_END();
    }
}