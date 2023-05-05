#include <math.h>
#include <stdio.h>

int main() {
  int radius, i, j;
  double distance;
  printf("Enter the radius of the circle: ");
  scanf("%d", &radius);

  for (i = 0; i <= 2 * radius; i++) {
    for (j = 0; j <= 2 * radius; j++) {
      distance = sqrt(pow(i - radius, 2) + pow(j - radius, 2));
      if (distance <= radius) {
        printf("o");
      } else {
        printf(".");
      }
    }
    printf("\n");
  }
  return 0;
}
