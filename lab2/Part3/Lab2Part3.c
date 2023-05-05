#include <math.h>
#include <stdio.h>

int main() {
  double weight, height, bmi;
  char first, second, third, fourth;
  printf("Enter the body weight: ");
  scanf("%lf%c%c", &weight, &first, &second);
  printf("Enter the height: \n");
  scanf("%lf%c%c", &height, &third, &fourth);

  if (first == 'l' && second == 'b') {
    weight = weight * 0.4536;
  }
  if (third == 'f' && fourth == 't') {
    height = height / 3.28;
  } else if (third == 'i' && fourth == 'n') {
    height = height / 39.37;
  }

  bmi = weight / pow(height, 2);
  bmi = round(bmi * 10) / 10;

  printf("The Body Mass Index (BMI) is: %.1f\n", bmi);
  if (bmi < 18.5) {
    printf("Category: Underweight");
  } else if (18.5 <= bmi && bmi <= 24.9) {
    printf("Category: Healthy Weight");
  } else if (25 <= bmi && bmi <= 29.9) {
    printf("Category: Overweight");
  } else {
    printf("Category: Obesity");
  }
}
