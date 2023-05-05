#include <stdio.h>

int main() {
  int number;
  printf("Enter number to convert to base 2: ");
  scanf("%d", &number);

  int fourthDigit, thirdDigit, secondDigit, firstDigit, remainder;
  fourthDigit = number % 2;
  remainder = number / 2;

  thirdDigit = remainder % 2;
  remainder = remainder / 2;

  secondDigit = remainder % 2;
  remainder = remainder / 2;

  firstDigit = remainder % 2;

  printf("The four digits of that number are as follows:\n");
  printf("Most significant digit: %d\n", firstDigit);
  printf("Next digit: %d\n", secondDigit);
  printf("Next digit: %d\n", thirdDigit);
  printf("Least significant digit: %d\n", fourthDigit);
}