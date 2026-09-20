#include "testHarness.h"

#include <stdbool.h>

void blink(int *count, bool *on) {
  if (*count >= 11) {
    *count = 0;
  } else {
    *on = !(*on);
    (*count)++;
  }
}

char swapCase(char c) {
  if (c <= 'z' && c >= 'a')
    return (c - 32);
  else if (c >= 'A' && c <= 'Z')
    return (c + 32);
  else
    return (c);
}