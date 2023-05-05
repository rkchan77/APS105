#include <stdio.h>

int main() {
  double conversionRate;
  printf("Enter the conversion rate: ");
  scanf("%lf", &conversionRate);

  double amountConverted;
  printf("Enter the amount to be converted (in foreign currency): ");
  scanf("%lf", &amountConverted);

  printf("The amount in Canadian Dollars is: %.2lf",
         conversionRate * amountConverted);
}
