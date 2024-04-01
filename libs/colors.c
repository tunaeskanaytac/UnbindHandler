#include <stdio.h>
void redColor() {
  printf("\033[1;31m");
}

void yellowColor() {
  printf("\033[1;33m");
}

void resetColor() {
  printf("\033[0m");
}
