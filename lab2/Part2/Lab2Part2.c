#include <math.h>
#include <stdio.h>

int main() {
  double xcoordinate, ycoordinate;
  printf("Enter the x-coordinate in floating point: ");
  scanf("%lf", &xcoordinate);
  printf("Enter the y-coordinate in floating point: \n");
  scanf("%lf", &ycoordinate);

  xcoordinate = round(xcoordinate * 100) / 100;
  ycoordinate = round(ycoordinate * 100) / 100;

  if (xcoordinate > 0 && ycoordinate > 0) {
    printf("(%.2f, %.2f) is in quadrant I.", xcoordinate, ycoordinate);
  } else if (xcoordinate < 0 && ycoordinate > 0) {
    printf("(%.2f, %.2f) is in quadrant II.", xcoordinate, ycoordinate);
  } else if (xcoordinate < 0 && ycoordinate < 0) {
    printf("(%.2f, %.2f) is in quadrant III.", xcoordinate, ycoordinate);
  } else if (xcoordinate > 0 && ycoordinate < 0) {
    printf("(%.2f, %.2f) is in quadrant IV.", xcoordinate, ycoordinate);
  } else if (xcoordinate == 0 && ycoordinate != 0) {
    printf("(%.2f, %.2f) is on the y axis.", xcoordinate, ycoordinate);
  } else if (xcoordinate != 0 && ycoordinate == 0) {
    printf("(%.2f, %.2f) is on the x axis.", xcoordinate, ycoordinate);
  } else {
    printf("(%.2f, %.2f) is at the origin.", xcoordinate, ycoordinate);
  }
}