#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
int main(void) {
  char userChar[255];
  char op;
  int sum = 0, sign = 1, value;
  bool number = true;
  printf("Enter sequence of characters with numbers to add: ");

  do {
    while (number == false) {
      scanf(" %c", &op);
      if (op == '+' || op == '-') {
        number = true;
        if (op == '+') {
          sign = +1;
        } else {
          sign = -1;
        }
      } else {
        printf("Invalid! Re-enter sign.\n");
      }
    }
    while (number == true) {
      scanf(" %s", &userChar);
      value = atoi(userChar);
      if (value > 0 && value <= 9) {
        number = false;
        sum = sum + value * sign;
      } else {
        printf("Invalid! Re-enter number.\n");
      }
    }
  } while (sum > 0);
  printf("Sum fell below zero.\n");
  return 0;
}