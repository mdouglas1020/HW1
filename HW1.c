// Michael Douglas Lab Section: Wednesday TA: Jacob Zimmer
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 100
#define MAX_NAME 30

int countLinesInFile(FILE* fPtr); //CHECK
int findPlayerByName(char** names, char* target, int size);
int findMVP(int* goals, int* assists, int size);
void printPlayers(int* goals, int* assists, char** names, int size);  //CHECK
void allocateMemory(int** goals, int** assists, char*** names, int size); //CHECK
void sortPlayersByGoals(int* goals, int* assists, char** names, int size);
void writeToFile(FILE* fPtr, int* goals, int* assists, char** names, int size);
void readLinesFromFile(FILE* fPtr, int* goals, int* assists, char** names, int numLines);  //CHECK


int main(int argc, char** argv)
{
  if(argc != 2)  //Checks for correct command line
  {
    printf("Incorrect number of arguments\n");
    return 0;
  }
  FILE* fptr = fopen(*(argv +1), "r");

  if(fptr == NULL)
  {
    printf("File could not be opened\n");
    return 0;
  }
  int lines = countLinesInFile(fptr);

  int* goals = NULL;
  int* assists = NULL;
  char** names = NULL;

  allocateMemory(&goals, &assists, &names, lines);
  readLinesFromFile(fptr, goals, assists, names, lines);
  printPlayers(goals, assists, names, lines);
  sortPlayersByGoals(goals, assists, names, lines);
  printPlayers(goals, assists, names, lines);

  int mvp = findMVP(goals, assists, lines);
  int points = *(goals + mvp) + *(assists + mvp);
  printf("MVP is %s with %d\n", *(names + mvp), points);


  return 0;
}

int countLinesInFile(FILE* fptr)
{
  char c;
  int lines = 0;

  while((c = fgetc(fptr))!= EOF)
  {
    if(c == '\n')
    ++lines;
  }
  rewind(fptr);

  return lines;
}

void allocateMemory(int** goals, int** assists, char*** names, int lines)
{
  *goals = malloc(sizeof(int)*lines);
*assists = malloc(sizeof(int)*lines);
 *names = malloc(sizeof(char*)*lines);
  int i;

  for(i=0; i < lines; i++)
  {
    *(*names + i) = malloc(sizeof(char)*MAX_NAME);
  }
}

void readLinesFromFile(FILE* fptr, int* goals, int* assists, char** names, int size)
{
  char *line= malloc(sizeof(char)*MAX_LINE);
  int i;
  char* hold = NULL;
  for(i = 0; i < size; i++)
  {
    if(fgets(line,MAX_LINE, fptr)!=NULL)
     {
       hold=strtok(line," ");
       strcpy(*(names + i),hold);
       hold=strtok(NULL," ");
       goals[i]=atoi(hold);
       hold=strtok(NULL," ");
       assists[i]=atoi(hold);
     }
  }
free(line);
}
void swap(int* x, int* y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}

void sortPlayersByGoals(int* goals, int* assists, char** names, int size)
{
  int i, key, j;

  for(i = 0; i < size; i ++)
  {
    key = i;

    for(j = i+1; j<size; j++)
    {
      if (*(goals + j) > *(goals + key))
      {
        key = j;
      }
    }
    swap((goals + key), (goals + i));
    swap((assists + key), (assists + i));
    char* temp = malloc(sizeof(char*)*MAX_NAME);
    strcpy(temp, *(names + key));
    strcpy(*(names + key), *(names + i));
    strcpy(*(names + i), temp);

  }

}

void printPlayers(int* goals, int* assists, char** names, int size)
{
  int i;

  for(i = 0; i < size; i++)
  {
    printf("%s %d %d\n", *(names + i), *(goals + i), *(assists + i));
  }

  printf("\n\n");
}

int findMVP(int* goals, int* assists, int size)
{
  int i;
  int mvp = 0;
  int index;
  for (i = 0; i < size; i++)
  {
    if(*(goals + i) + *(assists + i) > mvp )
    {
      mvp = *(goals + i) + *(assists + i);
      index = i;
    }

  }
  return index;
}
