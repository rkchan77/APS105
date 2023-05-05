#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  char oper = '\0';
  while (oper != '$') {
    int base1, base2, entry1, entry2;
    printf("Give input ($ to stop): ");
    scanf(" %c %d %d %d %d", &oper, &base1, &entry1, &entry2, &base2);

    if (oper == '$') {
      return 0;
    }

    if (oper == '+' || oper == '-' || oper == '*' || oper == '/') {
      if (base1 >= 2 && base1 <= 10 && base2 >= 2 && base2 <= 10) {
        int entry1_b10, entry2_b10, entry1_inner, entry2_inner, entry_final, i,
            j, k, newbase, working;
        entry1_b10 = entry2_b10 = i = j = newbase = working = 0;
        entry1_inner = entry1;
        entry2_inner = entry2;
        k = 1;

        while (entry1_inner > 0) {
          int digit = entry1_inner % 10;

          if (digit >= base1) {
            printf("Invalid digits in operand\n");
            working = 1;
          }

          digit = digit * pow(base1, i);
          entry1_b10 = entry1_b10 + digit;
          i++;
          entry1_inner = entry1_inner / 10;
        }

        while (entry2_inner > 0) {
          int digit = entry2_inner % 10;

          if (digit >= base1) {
            printf("Invalid digits in operand\n");
            working = 1;
          }

          digit = digit * pow(base1, j);
          entry2_b10 = entry2_b10 + digit;
          j++;
          entry2_inner = entry2_inner / 10;
        }

        switch (oper) {
          case '+':
            entry_final = entry1_b10 + entry2_b10;
            break;
          case '-':
            entry_final = entry1_b10 - entry2_b10;
            break;
          case '*':
            entry_final = entry1_b10 * entry2_b10;
            break;
          case '/':
            entry_final = entry1_b10 / entry2_b10;
            break;
        }

        while (entry_final > 0) {
          int digit = entry_final % base2 * k;

          newbase = newbase + digit;

          k = k * 10;
          entry_final = entry_final / base2;
        }

        if (working == 0) {
          printf("%d %c %d (base %d) = %d %c %d = %d (base %d)\n", entry1, oper,
                 entry2, base1, entry1_b10, oper, entry2_b10, newbase, base2);
        }

      } else {
        printf("Invalid base\n");
      }
    } else {
      printf("Invalid operator\n");
    }
  }
}
