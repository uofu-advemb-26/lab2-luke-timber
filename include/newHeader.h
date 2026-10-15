#ifndef BLINK_H
#define BLINK_H

#include <stdbool.h>

void insideMainLoop(char c);

void insideBlinkLoop(int *count, bool *on);

#endif