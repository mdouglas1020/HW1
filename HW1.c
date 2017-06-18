// Michael Douglas Lab Section: Wednesday TA: Jacob Zimmer
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 100
#define MAX_NAME 30

int countLinesInFile(FILE* fPtr);
int findPlayerByName(char** names, char* target, int size);
int findMVP(int* goals, int* assists, int size);
void printPlayers(int* goals, int* assists, char** names, int size);
void allocateMemory(int** goals, int** assists, char*** names, int size);
void sortPlayersByGoals(int* goals, int* assists, char** names, int size);
void writeToFile(FILE* fPtr, int* goals, int* assists, char** names, int size);
void readLinesFromFile(FILE* fPtr, int* goals, int* assists, char** names, int numLines);


int main(int argc, char* argv[])
{
  if(argc != 3)  //Checks for correct command line
  {
    printf("Incorrect number of arguments\n");
    return 0;
  }
  FILE* fptr = fopen(fptr, "r");

  if(fptr == NULL)
  {
    printf("File could not be opened\n");
    return 0;
  }
  int lines = countLinesInFile(fptr);

  // int* goals = malloc(sizeof(int)*lines);
  // int* assists = malloc(sizeof(int)*lines);
  // char** names = malloc(sizeof(char)*MAX_NAME);

  printf("The amount of lines are %d\n", lines);
  return 0;
}

int countLinesInFile(FILE* fptr)
{
  char c;
  int lines = 0;

  while((c = fgets(fptr))!= feof(fptr))
  {
    if(c == '\n')
    ++lines;
  }
  fclose(fptr);
  return lines;
}

// void readLinesFromFile(FILE* fptr, int* goals, int* assists, char** names, int numLines)
// {
//
//
// }
