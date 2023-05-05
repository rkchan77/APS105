/**
 * @file reversi.c
 * @author Ryan Chan
 * @brief This file is used for APS105 Lab 8. 2023W version
 * @date 2023-03-14
 *
 */
// DO NOT REMOVE THE FOLLOWING LINE
#if !defined(TESTER_P1) && !defined(TESTER_P2)
// DO NOT REMOVE THE ABOVE LINE
#include "reversi.h"
// DO NOT REMOVE THE FOLLOWING LINE
#endif
// DO NOT REMOVE THE ABOVE LINE
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>

void printBoard(char board[][26], int n);
bool positionInBounds(int n, int i, int j);
bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol);
int makeMove(char board[26][26], int n, char turn, int* row, int* col);
bool validInput(char board[][26], int n, char colour, char row, char col);
void copyArray(char board[][26], char boardCopy[][26], int n);
void completeTurn(char boardCopy[][26], int n, char colour, int row, int col);
int calculateScore(char boardCopy[][26], int n, char colour);
int minimax(char board[][26], int n, int depth, int alpha, int beta,
            char colour, bool max);

int makeMove(char board[26][26], int n, char turn, int* row, int* col) {
  int best = -1000;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (validInput(board, n, turn, (char)(i + 'a'), (char)(j + 'a'))) {
        char boardCopy[n][26];
        copyArray(board, boardCopy, n);
        completeTurn(boardCopy, n, turn, i, j);
        int childValue = minimax(boardCopy, n, 10, -1000, 1000, turn, false);
        if (childValue > best) {
          best = childValue;
          *row = i;
          *col = j;
        }
      }
    }
  }
  return 0;
}

void copyArray(char board[][26], char boardCopy[][26], int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      boardCopy[i][j] = board[i][j];
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

int calculateScore(char boardCopy[][26], int n, char colour) {
  int score = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (boardCopy[i][j] == colour) {
        score++;
      } else if (boardCopy[i][j] != 'U') {
        score--;
      }
    }
  }
  return score;
}

void completeTurn(char boardCopy[][26], int n, char colour, int row, int col) {
  boardCopy[row][col] = colour;
  for (int k = -1; k <= 1; k++) {
    for (int l = -1; l <= 1; l++) {
      if (k == 0 && l == 0) {
        continue;
      }
      if (checkLegalInDirection(boardCopy, n, row, col, colour, k, l)) {
        int tempk = k;
        int templ = l;
        while (positionInBounds(n, row + tempk, col + templ) &&
               boardCopy[row + tempk][col + templ] != 'U' &&
               boardCopy[row + tempk][col + templ] != colour) {
          boardCopy[row + tempk][col + templ] = colour;
          tempk += 1 * k;
          templ += 1 * l;
        }
      }
    }
  }
}

int minimax(char board[][26], int n, int depth, int alpha, int beta,
            char colour, bool max) {
  if (depth == 0) {
    return calculateScore(board, n, max ? colour : (colour == 'B' ? 'W' : 'B'));
  }
  int best;
  if (max) {
    best = -1000;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (validInput(board, n, colour, (char)(i + 'a'), (char)(j + 'a'))) {
          char boardCopy[n][26];
          copyArray(board, boardCopy, n);
          completeTurn(boardCopy, n, colour, i, j);
          int childValue =
              minimax(boardCopy, n, depth - 1, alpha, beta, colour, false);
          if (childValue > best) {
            best = childValue;
          }
          if (best > alpha) {
            alpha = best;
          }
          if (alpha >= beta) {
            return best;
          }
        }
      }
    }
  } else {
    best = 1000;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (validInput(board, n, colour == 'B' ? 'W' : 'B', (char)(i + 'a'),
                       (char)(j + 'a'))) {
          char boardCopy[n][26];
          copyArray(board, boardCopy, n);
          completeTurn(boardCopy, n, colour == 'B' ? 'W' : 'B', i, j);
          int childValue =
              minimax(boardCopy, n, depth - 1, alpha, beta, colour, false);
          if (childValue < best) {
            best = childValue;
          }
          if (best < beta) {
            beta = best;
          }
          if (alpha >= beta) {
            return best;
          }
        }
      }
    }
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

//*******************************************************
// Note: Please only put your main function below
// DO NOT REMOVE THE FOLLOWING LINE
#ifndef TESTER_P2
// DO NOT REMOVE THE ABOVE LINE
int main(void) {
  // Write your own main function here
  return 0;
}
// DO NOT REMOVE THE FOLLOWING LINE
#endif
// DO NOT REMOVE THE ABOVE LINE
//*******************************************************
