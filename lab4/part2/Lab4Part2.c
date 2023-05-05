#include <math.h>
#include <stdio.h>

int main() {
  int order = 0, coefficient;

  while (order != -1) {
    printf("Enter the order of the function: ");
    scanf("%d", &order);

    if (order == -1) {
      break;
    } else if (order >= 0 && order <= 3) {
      int coefficients[order];

      for (int i = 0; i <= order; i++) {
        printf("Enter coefficient of x^%d: ", i);
        scanf("%d", &coefficient);
        coefficients[i] = coefficient;
      }

      int length = sizeof(coefficients) / sizeof(coefficients[0]);

      for (int j = length + 1; j <= 3; j++) {
        coefficients[j] = 0;
      }
      for (int i = -10; i <= 10; i++) {
        for (int x = -10; x <= 10; x++) {
          int y;

          if (order == 0) {
            y = -1 * (coefficients[0]);
          } else {
            y = -1 *
                (coefficients[3] * pow(x, 3) + coefficients[2] * pow(x, 2) +
                 coefficients[1] * x + coefficients[0]);
          }

          if (i == y) {
            printf(" * ");
          } else if (x == 0 && i != y) {
            printf(" | ");
          } else if (i == 0 && i != y) {
            printf(" - ");
          } else {
            printf("   ");
          }
        }
        printf("\n");
      }

    } else {
      printf("The order must be between [0, 3].\n");
    }
  }
  return 0;
}
