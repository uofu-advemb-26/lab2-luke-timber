/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

#include "newHeader.h"

int count = 0;
bool on = false;

#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2UL )
#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define BLINK_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

void blink_task(__unused void *params) {
    hard_assert(cyw43_arch_init() == PICO_OK);
    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);
        insideBlinkLoop(&count, &on);
        vTaskDelay(500);
        // cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);
        // // Evaluates the current value of count with the modulo, then increments count afterward.
        // // If count is anything but a multiple of 11 then this evaluates to true.  Multiples of 11 (0, 11, 22, 33, ...) evaluate to false.
        // if (count++ % 11) on = !on;
        // vTaskDelay(500);
    }
}

void main_task(__unused void *params) {
    // Create a side task "blink"
    xTaskCreate(blink_task, "BlinkThread",
                BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);
    char c;
    // While there is a char from the standard input, if the char is lowercase
    // print it as uppercase, if the char is uppercase print it as lowercase.
    // If it is not a standard char then just print the same char back out.
    while(c = getchar()) {
        insideMainLoop(c);
        // if (c <= 'z' && c >= 'a') putchar(c - 32);
        // else if (c >= 'A' && c <= 'Z') putchar(c + 32);
        // else putchar(c);
    }
}

int main( void )
{
    stdio_init_all();
    const char *rtos_name;
    rtos_name = "FreeRTOS";
    TaskHandle_t task;
    // Create the main task and start the task scheduler.
    xTaskCreate(main_task, "MainThread",
                MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &task);
    vTaskStartScheduler();
    return 0;
}
