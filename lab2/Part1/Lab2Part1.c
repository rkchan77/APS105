#include <math.h>
#include <stdio.h>

int main() {
  double xvalue, yvalue, hypotenuse, angle;
  printf("Enter X: ");
  scanf("%lf", &xvalue);
  printf("Enter Y: ");
  scanf("%lf", &yvalue);

  hypotenuse = sqrt(pow(xvalue, 2) + pow(yvalue, 2));
  angle = asin(yvalue / hypotenuse) * 180 / M_PI;

  printf("The Hypotenuse Length is: %.1f\n", hypotenuse);
  printf("The Angle Theta is: %.1f degrees", angle);
}