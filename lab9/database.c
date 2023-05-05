#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/* DO NOT EDIT THE LINES BELOW */

#define STRING_MAX 1024

typedef struct node {
  char *name;
  int lines;
  int runtime;
  int memory_usage;
  struct node *next;
} Node;

typedef struct linked_list {
  Node *head;
} LinkedList;

void readInputString(char *, int);
void readInputNumber(int *);
void readInputChar(char *);
LinkedList *newList();
char getCommand();
void handleInsert(LinkedList *);
void handleDelete(LinkedList *);
void handleSearch(LinkedList *);
void handlePrint(LinkedList *);
void handleQuit(LinkedList *);

int main() {
  LinkedList *list = newList();
  char command = '\0';
  printf("Experimental database entry\n");
  while (command != 'Q') {
    command = getCommand();
    switch (command) {
      case 'I':
        handleInsert(list);
        break;
      case 'D':
        handleDelete(list);
        break;
      case 'S':
        handleSearch(list);
        break;
      case 'P':
        handlePrint(list);
        break;
      case 'Q':
        handleQuit(list);
        break;
    }
  }
  free(list);
  return 0;
}
/* DO NOT EDIT THE LINES ABOVE */

void handleInsert(LinkedList *list) {
  int value, lines, runtime, memory_usage;

  printf("\nNumber of characters in file name: ");
  readInputNumber(&value);

  char *name = (char *)malloc(sizeof(char) * (value + 1));
  printf("File name: ");
  readInputString(name, value + 1);

  printf("Number of lines in CSV file: ");
  readInputNumber(&lines);

  printf("Experiment runtime (ms): ");
  readInputNumber(&runtime);

  printf("Experiment memory usage (B): ");
  readInputNumber(&memory_usage);

  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->name = name;
  newNode->lines = lines;
  newNode->runtime = runtime;
  newNode->memory_usage = memory_usage;

  Node *lastNode = NULL;
  Node *currentNode = list->head;
  while (currentNode != NULL && strcmp(currentNode->name, name) < 0) {
    lastNode = currentNode;
    currentNode = currentNode->next;
  }
  if (currentNode != NULL && strcmp(currentNode->name, name) == 0) {
    printf("\nAn entry with that file name already exists.\n");
    free(newNode->name);
    free(newNode);
    return;
  }
  newNode->next = currentNode;
  if (lastNode == NULL) {
    list->head = newNode;
  } else {
    lastNode->next = newNode;
  }
}
void handleDelete(LinkedList *list) {
  printf("\nEnter file name to delete: ");
  char name[STRING_MAX];
  readInputString(name, STRING_MAX);

  Node *lastNode = NULL;
  Node *currentNode = list->head;
  while (currentNode != NULL) {
    if (strcmp(currentNode->name, name) == 0) {
      if (lastNode == NULL) {  // removing the head node
        list->head = currentNode->next;
      } else {
        lastNode->next = currentNode->next;
      }
      free(currentNode->name);
      free(currentNode);
      printf("Deleting entry for CSV file <%s>\n", name);
      return;
    }
    lastNode = currentNode;
    currentNode = currentNode->next;
  }

  printf("An entry for file <%s> does not exist.\n", name);
}
void handleSearch(LinkedList *list) {
  printf("\nEnter file name to find: ");
  char name[STRING_MAX];
  readInputString(name, STRING_MAX);

  Node *currentNode = list->head;
  while (currentNode != NULL) {
    if (strcmp(currentNode->name, name) == 0) {
      double runtime = (double)currentNode->runtime / 1000;
      double throughput = (double)currentNode->lines / runtime;
      printf("File <%s>\n", currentNode->name);
      printf("Lines: %d\n", currentNode->lines);
      printf("Runtime (ms): %d\n", currentNode->runtime);
      printf("Memory usage (B): %d\n", currentNode->memory_usage);
      printf("Throughput: %0.2f\n", throughput);
      return;
    }
    currentNode = currentNode->next;
  }
  printf("An entry for file <%s> does not exist.\n", name);
}

void handlePrint(LinkedList *list) {
  Node *newNode = list->head;
  printf("\nData entries:\n");
  if (newNode == NULL) {
    printf("There are no data entries.\n");
  } else {
    while (newNode != NULL) {
      double runtime = (double)newNode->runtime / 1000;
      double throughput = (double)newNode->lines / runtime;
      printf("\nFile <%s>\n", newNode->name);
      printf("Lines: %d\n", newNode->lines);
      printf("Runtime (ms): %d\n", newNode->runtime);
      printf("Memory usage (B): %d\n", newNode->memory_usage);
      printf("Throughput: %0.2f\n", throughput);
      newNode = newNode->next;
    }
  }
}

void handleQuit(LinkedList *list) {
  Node *currentNode = list->head;
  while (currentNode != NULL) {
    Node *lastNode = currentNode;
    currentNode = currentNode->next;
    printf("Deleting entry for CSV file <%s>\n", lastNode->name);
    free(lastNode->name);
    free(lastNode);
  }
  free(list);
  exit(0);
}

/* DO NOT EDIT THE LINES BELOW */
void readInputString(char *str, int length) {
  int i = 0;
  char c;
  while (i < length && (c = getchar()) != '\n') {
    str[i++] = c;
  }
  str[i] = '\0';
}
void readInputNumber(int *number) {
  char buf[STRING_MAX];
  readInputString(buf, STRING_MAX);
  *number = (int)strtol(buf, (char **)NULL, 10);
}
void readInputChar(char *character) {
  char buf[2];
  readInputString(buf, 3);
  *character = buf[0];
}
LinkedList *newList() {
  LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
  list->head = NULL;
  return list;
}
char getCommand() {
  char command;
  printf("\nSupported commands are:\n");
  printf(" I - Insert\n");
  printf(" D - Delete\n");
  printf(" S - Search\n");
  printf(" P - Print\n");
  printf(" Q - Quit\n");
  printf("\nPlease select a command: ");
  readInputChar(&command);
  while (command != 'I' && command != 'D' && command != 'S' && command != 'P' &&
         command != 'Q') {
    printf("Invalid command <%c>, please select a command: ", command);
    readInputChar(&command);
  }
  return command;
}
/* DO NOT EDIT THE LINES ABOVE */
