#include <stdio.h>

int getAscendingOrderedDigits(int);
int getDescendingOrderedDigits(int);

int main() {
  int number = 0;
  while (number != -1) {
    printf("Enter a number (-1 to stop): ");
    scanf("%d", &number);
    if (number == -1) {
      break;
    } else if (number < 1000) {
      printf("Error: The number is too small.\n");
    } else if (number > 9999) {
      printf("Error: The number is too large.\n");
    } else {
      int difference = number, k = 0;
      while (difference != 6174) {
        k++;
        printf("Number %d: %d\n", k, difference);
        int ascend = getAscendingOrderedDigits(difference);
        int descend = getDescendingOrderedDigits(ascend);
        if (descend < 10) {
          descend *= 1000;
        } else if (descend < 100) {
          descend *= 100;
        } else if (descend < 1000) {
          descend *= 10;
        }

        difference = descend - ascend;
      }
      k++;
      printf("Number %d: %d\n", k, difference);
      k--;
      printf("Kaprekar's Constant was reached in %d iteration(s)\n", k);
    }
  }
}

// Function returns digits in number in descending order
int getDescendingOrderedDigits(int number) {
  int digit, descending = 0;
  while (number > 0) {
    digit = number % 10;
    descending = descending * 10 + digit;
    number /= 10;
  }
  return descending;
}
// Function returns digits in number in ascending order
int getAscendingOrderedDigits(int number) {
  int digits[10] = {0};
  while (number > 0) {
    digits[number % 10]++;
    number /= 10;
  }
  int i = 0;
  while (i < 10) {
    if (digits[i] > 0) {
      number *= 10;
      number += i;
      digits[i]--;
    } else {
      i++;
    }
  }
  return number;
}
