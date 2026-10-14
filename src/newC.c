#include "newHeader.h"
#include <stdbool.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

void insideMainLoop(char c) {
    if (c <= 'z' && c >= 'a') putchar(c - 32);
    else if (c >= 'A' && c <= 'Z') putchar(c + 32);
    else putchar(c);
}

void insideBlinkLoop(int *count, bool *on) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);
    // Evaluates the current value of count with the modulo, then increments count afterward.
    // If count is anything but a multiple of 11 then this evaluates to true.  Multiples of 11 (0, 11, 22, 33, ...) evaluate to false.
    if ((*count)++ % 11) *on = !*on;
    vTaskDelay(500);
}