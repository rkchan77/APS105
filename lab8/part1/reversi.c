//
// Author: Ryan Chan
//

#include "reversi.h"

#include <stdio.h>

void printBoard(char board[][26], int n);
bool positionInBounds(int n, int i, int j);
bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol);
void movesAvailable(char board[][26], int n, char colour);
bool validInput(char board[][26], int n, char colour, char row, char col);
void swapColours(char board[][26], int n, int row, int col, char colour);
void computerMove(char board[26][26], int n, char turn, int* compRow,
                  int* compCol);
bool endGame(char board[][26], int n);
int calculateScore(char board[][26], int n, int row, int col, char colour);
bool moves(char board[][26], int n, char colour);
void winner(char board[][26], int n);

int main(void) {
  int n;
  printf("Enter the board dimension: ");
  scanf("%d", &n);

  // Define computer and player colours
  char computer, player;
  printf("Computer plays (B/W): ");
  scanf(" %c", &computer);
  if (computer == 'B') {
    player = 'W';
  } else {
    player = 'B';
  }

  // Declare static 2D array of size nxn
  char board[n][26];

  // Initialize board
  int half_1 = n / 2 - 1;
  int half_2 = n / 2;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if ((i == half_1 && j == half_1) || (i == half_2 && j == half_2)) {
        board[i][j] = 'W';
      } else if ((i == half_1 && j == half_2) || (i == half_2 && j == half_1)) {
        board[i][j] = 'B';
      } else {
        board[i][j] = 'U';
      }
    }
  }
  printBoard(board, n);

  if (computer == 'B') {
    while (endGame(board, n) == false) {
      int compRow = 0;
      int compCol = 0;
      char userRow, userCol;

      if (moves(board, n, computer)) {
        computerMove(board, n, computer, &compRow, &compCol);
        printf("Computer places %c at %c%c.\n", computer, (char)(compRow + 97),
               (char)(compCol + 97));
        swapColours(board, n, compRow, compCol, computer);
        board[compRow][compCol] = computer;
        printBoard(board, n);
      } else {
        if (endGame(board, n) == false) {
          printf("%c player has no valid move.\n", computer);
        }
      }

      if (moves(board, n, player)) {
        printf("Enter move for colour %c (RowCol): ", player);
        scanf(" %c%c", &userRow, &userCol);
        if (validInput(board, n, player, userRow, userCol)) {
          swapColours(board, n, userRow - 'a', userCol - 'a', player);
          board[userRow - 'a'][userCol - 'a'] = player;
        } else {
          printf("Invalid move.\n");
          printf("%c player wins.\n", computer);
          break;
        }
        printBoard(board, n);
      } else {
        if (endGame(board, n) == false) {
          printf("%c player has no valid move.\n", player);
        }
      }
    }
  } else {
    while (endGame(board, n) == false) {
      int compRow, compCol;
      char userRow, userCol;

      if (moves(board, n, player)) {
        printf("Enter move for colour %c (RowCol): ", player);
        scanf(" %c%c", &userRow, &userCol);
        if (validInput(board, n, player, userRow, userCol)) {
          swapColours(board, n, userRow - 'a', userCol - 'a', player);
          board[userRow - 'a'][userCol - 'a'] = player;
        } else {
          printf("Invalid move.\n");
          printf("%c player wins.\n", computer);
          break;
        }
        printBoard(board, n);
      } else {
        if (endGame(board, n) == false) {
          printf("%c player has no valid move.\n", player);
        }
      }

      if (moves(board, n, computer)) {
        computerMove(board, n, computer, &compRow, &compCol);
        printf("Computer places %c at %c%c.\n", computer, (char)(compRow + 97),
               (char)(compCol + 97));
        swapColours(board, n, compRow, compCol, computer);
        board[compRow][compCol] = computer;
        printBoard(board, n);
      } else {
        if (endGame(board, n) == false) {
          printf("%c player has no valid move.\n", computer);
        }
      }
    }
  }
  if (endGame(board, n) == true) {
    winner(board, n);
  }
  return 0;
}

void printBoard(char board[][26], int n) {
  printf("  ");
  for (int k = 0; k < n; k++) {
    int header = k + 97;
    printf("%c", (char)header);
  }

  printf("\n");

  for (int i = 0; i < n; i++) {
    int header = i + 97;
    printf("%c ", (char)header);
    for (int j = 0; j < n; j++) {
      printf("%c", board[i][j]);
    }
    printf("\n");
  }
}
bool positionInBounds(int n, int i, int j) {
  if (i < 0 || j < 0 || i >= n || j >= n) {
    return false;
  } else {
    return true;
  }
}
bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol) {
  char opp;
  if (colour == 'B') {
    opp = 'W';
  } else if (colour == 'W') {
    opp = 'B';
  }

  // If selected space is not empty OR if space directly touching selected space
  // is the same colour OR if selected space is not within the bounds
  if (board[row][col] != 'U' || !positionInBounds(n, row, col)) {
    return false;
  }

  // Make space counter for different radii
  int step = 1;

  while ((positionInBounds(n, row + deltaRow * step, col + deltaCol * step)) &&
         board[row + deltaRow * step][col + deltaCol * step] == opp) {
    step++;
    if (!positionInBounds(n, row + deltaRow * step, col + deltaCol * step) ||
        board[row + deltaRow * step][col + deltaCol * step] == 'U') {
      return false;
    }
    if (positionInBounds(n, row + deltaRow * step, col + deltaCol * step) &&
        board[row + deltaRow * step][col + deltaCol * step] == colour) {
      return true;
    }
  }
  return false;
}
void movesAvailable(char board[][26], int n, char colour) {
  // Go through each column in every row
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      // Check all positions touching empty space

      if (validInput(board, n, colour, (char)(i + 97), (char)(j + 97))) {
        printf("%c%c\n", (char)(i + 97), (char)(j + 97));
      }
    }
  }
}
bool validInput(char board[][26], int n, char colour, char row, char col) {
  if (positionInBounds(n, row - 'a', col - 'a') == false ||
      board[row - 'a'][col - 'a'] != 'U') {
    return false;
  }
  for (int k = -1; k <= 1; k++) {
    for (int l = -1; l <= 1; l++) {
      if (k == 0 && l == 0) {
        continue;
      }
      if (checkLegalInDirection(board, n, row - 'a', col - 'a', colour, k, l)) {
        return true;
      }
    }
  }
  return false;
}
void swapColours(char board[][26], int n, int row, int col, char colour) {
  for (int k = -1; k <= 1; k++) {
    for (int l = -1; l <= 1; l++) {
      if (k == 0 && l == 0) {
        continue;
      }
      if (checkLegalInDirection(board, n, row, col, colour, k, l)) {
        int tempk = k;
        int templ = l;
        while (positionInBounds(n, row + tempk, col + templ) &&
               board[row + tempk][col + templ] != 'U' &&
               board[row + tempk][col + templ] != colour) {
          board[row + tempk][col + templ] = colour;
          tempk += 1 * k;
          templ += 1 * l;
        }
      }
    }
  }
}

void computerMove(char board[26][26], int n, char turn, int* compRow,
                  int* compCol) {
  int score = 0;
  int highRow = 0;
  int highCol = 0;
  // Check available moves for colour
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      // Check all positions touching empty space
      if (validInput(board, n, turn, (char)(i + 97), (char)(j + 97))) {
        int testScore = calculateScore(board, n, i, j, turn);
        if (testScore > score) {
          score = testScore;
          highRow = i;
          highCol = j;
        }
      }
    }
  }
  *compRow = highRow;
  *compCol = highCol;
}

bool endGame(char board[][26], int n) {
  int U_count = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (board[i][j] == 'U') {
        U_count++;
      }
    }
  }
  if (U_count == 0) {
    return true;
  } else {
    return false;
  }
}
void winner(char board[][26], int n) {
  int W_count = 0;
  int B_count = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (board[i][j] == 'W') {
        W_count++;
      } else if (board[i][j] == 'B') {
        B_count++;
      }
    }
  }
  if (W_count > B_count) {
    printf("W player wins.");
    return;
  } else if (W_count < B_count) {
    printf("B player wins.");
    return;
  } else {
    printf("Draw.");
  }
}

int calculateScore(char board[][26], int n, int row, int col, char colour) {
  int score = 0;
  for (int k = -1; k <= 1; k++) {
    for (int l = -1; l <= 1; l++) {
      if (k == 0 && l == 0) {
        continue;
      }
      if (checkLegalInDirection(board, n, row, col, colour, k, l)) {
        int tempk = k;
        int templ = l;
        while (positionInBounds(n, row + tempk, col + templ) &&
               board[row + tempk][col + templ] != 'U' &&
               board[row + tempk][col + templ] != colour) {
          score++;
          tempk += 1 * k;
          templ += 1 * l;
        }
      }
    }
  }
  return score;
}

bool moves(char board[][26], int n, char colour) {
  // Go through each column in every row
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      // Check all positions touching empty space

      if (validInput(board, n, colour, (char)(i + 97), (char)(j + 97))) {
        return true;
      }
    }
  }
  return false;
}
