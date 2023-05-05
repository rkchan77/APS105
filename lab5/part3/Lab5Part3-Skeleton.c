#include <stdbool.h>
#include <stdio.h>
void calculateScore(int[], const int, int[], int[], const int, int*,
                    int*);  // calculate the score of each user
int main(void) {
  const int BoxesNum = 20;
  const int ChoicesNum = 5;
  int boxes[BoxesNum], userOne[ChoicesNum], userTwo[ChoicesNum];
  printf("Enter boxes content: ");
  for (int i = 0; i < BoxesNum; i++) {
    scanf("%d", &boxes[i]);
  }
  printf("Enter player 1 choices: ");
  for (int i = 0; i < ChoicesNum; i++) {
    scanf("%d", &userOne[i]);
  }
  printf("Enter player 2 choices: ");
  for (int i = 0; i < ChoicesNum; i++) {
    scanf("%d", &userTwo[i]);
  }
  int userOneScore = 0, userTwoScore = 0;
  calculateScore(boxes, BoxesNum, userOne, userTwo, ChoicesNum, &userOneScore,
                 &userTwoScore);
  printf("Player 1: %d.\nPlayer 2: %d.\n", userOneScore, userTwoScore);
  return 0;
}

void calculateScore(int boxes[], const int BoxesNum, int userOne[],
                    int userTwo[], const int ChoicesNum, int* score1,
                    int* score2) {
  for (int j = 0; j < BoxesNum; j++) {
    if (boxes[j] != 0) {
      printf("Found %d in boxes[%d].\n", boxes[j], j);

      // check if one or both users input a value
      int counter[BoxesNum];
      for (int i = 0; i < BoxesNum; i++) {
        counter[i] = 0;
      }

      for (int i = 0; i < ChoicesNum; i++) {
        if (j == userOne[i]) {
          counter[j]++;
        }
        if (j == userTwo[i]) {
          counter[j]++;
        }
      }

      if (counter[j] == 1) {
        for (int i = 0; i < ChoicesNum; i++) {
          if (j == userOne[i]) {
            printf("Found index %d in player 1.\n", j);
            if (boxes[j] == 10) {
              printf("+10 to player 1 score.\n");
            } else {
              printf("%d from player 1 score.\n", boxes[j]);
            }
            *score1 = *score1 + boxes[j];
          } else if (j == userTwo[i]) {
            printf("Found index %d in player 2.\n", j);
            if (boxes[j] == 10) {
              printf("+10 to player 2 score.\n");
            } else {
              printf("%d from player 2 score.\n", boxes[j]);
            }
            *score2 = *score2 + boxes[j];
          }
        }
      }
      if (counter[j] == 2) {
        printf("Found index %d in player 1.\n", j);
        printf("Found index %d in player 2.\n", j);
        if (boxes[j] == 10) {
          printf("+5 to players 1 and 2 scores.\n");
          *score1 = *score1 + 5;
          *score2 = *score2 + 5;
        } else {
          printf("%d from player 1 score.\n", boxes[j]);
          printf("%d from player 2 score.\n", boxes[j]);
          *score1 = *score1 + boxes[j];
          *score2 = *score2 + boxes[j];
        }
      }
    }
  }
}
