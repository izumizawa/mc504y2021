#include <pthread.h>
#include <stdio.h>
#include <ctype.h>
/* Minesweeper board meanings
  0: Blank space = no bombs around
  1 ~ 8: Number of bombs around the space
  9: Flag where player thinks there is a bomb
  10: Bomb (B)
  11: Closed space (' ')
*/

#define MAX_HEIGHT 9
#define MAX_WIDTH 9

int AnswersBoard[MAX_WIDTH][MAX_HEIGHT]; // Board with answers
int UserBoard[MAX_WIDTH][MAX_HEIGHT];    // Board player can see

typedef struct Quadrant {
  int start_row;
  int start_column;
  int end_row;
  int end_column;
  int return_thread;
} Quadrant;

void setAnswersBoard();
void setUserBoard();
void printBoard();
void openBoard(int column, int row);
int isBoardCompleted();

int main()
{
  char command;
  char cell[3];
  int row, column;
  printf(" Welcome to Minesweeer!\n");
  setAnswersBoard();
  setUserBoard();
  do
  {
    printBoard();
    printf(" Use the command 'o' to open a cell, 'f' to flag a cell or 'q' to quit\n");
    printf("Command--> ");
    scanf(" %c", &command);

    if (command == 'o')
    {
      printf(" Choose one cell to continue (ie. a1):\n");
      printf("Cell--> ");
      scanf(" %s", cell);
      cell[0] = toupper(cell[0]);
      row = (int)cell[1] - 49;
      column = (int)cell[0] - 65;
      if (row < MAX_HEIGHT && row >= 0 && column < MAX_WIDTH && column >= 0)
      {
        UserBoard[row][column] = AnswersBoard[row][column];
        if (UserBoard[row][column] == 10) {
          printf("\n GAME OVER :(\n\n");
          break;
          printf("\n GAME OVER :(\n\n");
        } 
        else if (UserBoard[row][column] == 0) 
        {
          openBoard(column, row);
        }
      }
      else
      {
        printf("Invalid command\n");
      }
    }
    else if (command == 'f')
    {
      printf(" Choose one cell to continue (ie. a1):\n");
      printf("Cell--> ");
      scanf(" %s", cell);
      cell[0] = toupper(cell[0]);
      row = (int)cell[1] - 49;
      column = (int)cell[0] - 65;
      if (row < MAX_HEIGHT && row >= 0 && column < MAX_WIDTH && column >= 0)
      {
        UserBoard[row][column] = 9;
      }
      else
      {
        printf("Invalid command\n");
      }
    }
    else if (command == 'q')
    {
      break;
    }
    else
    {
      printf("Invalid command\n");
    }

  } while (isBoardCompleted());

  printBoard();
  return 0;
}

void setBombs()
{
  // Set bombs
  AnswersBoard[0][7] = 10;
  AnswersBoard[1][0] = 10;
  AnswersBoard[1][6] = 10;
  AnswersBoard[2][8] = 10;
  AnswersBoard[3][7] = 10;
  AnswersBoard[4][1] = 10;
  AnswersBoard[4][4] = 10;
  AnswersBoard[5][3] = 10;
  AnswersBoard[7][8] = 10;
  AnswersBoard[8][2] = 10;
};

// set a closed board
void setBlankSpaces()
{
  for (int i = 0; i < MAX_WIDTH; i++)
  {
    for (int j = 0; j < MAX_HEIGHT; j++)
    {
      AnswersBoard[i][j] = 0;
    }
  }
}

// Create fixed board
void setAnswersBoard()
{
  setBlankSpaces();
  setBombs();
  AnswersBoard[0][0] = 1;
  AnswersBoard[0][1] = 1;
  AnswersBoard[0][5] = 1;
  AnswersBoard[0][6] = 2;
  AnswersBoard[0][8] = 1;
  AnswersBoard[1][1] = 1;
  AnswersBoard[1][5] = 1;
  AnswersBoard[1][7] = 3;
  AnswersBoard[1][8] = 2;
  AnswersBoard[2][0] = 1;
  AnswersBoard[2][1] = 1;
  AnswersBoard[2][5] = 1;
  AnswersBoard[2][6] = 2;
  AnswersBoard[2][7] = 3;
  for (int i = 0; i < 7; i++)
    AnswersBoard[3][i] = 1;
  AnswersBoard[3][8] = 2;
  AnswersBoard[4][0] = 1;
  AnswersBoard[4][2] = 2;
  AnswersBoard[4][3] = 2;
  AnswersBoard[4][5] = 1;
  AnswersBoard[4][6] = 1;
  AnswersBoard[4][7] = 1;
  AnswersBoard[4][8] = 1;
  AnswersBoard[5][0] = 1;
  AnswersBoard[5][1] = 1;
  AnswersBoard[5][2] = 2;
  AnswersBoard[5][4] = 2;
  AnswersBoard[5][5] = 1;
  AnswersBoard[6][2] = 1;
  AnswersBoard[6][3] = 1;
  AnswersBoard[6][4] = 1;
  AnswersBoard[6][7] = 1;
  AnswersBoard[6][8] = 1;
  AnswersBoard[7][1] = 1;
  AnswersBoard[7][2] = 1;
  AnswersBoard[7][3] = 1;
  AnswersBoard[7][7] = 1;
  AnswersBoard[8][1] = 1;
  AnswersBoard[8][3] = 1;
  AnswersBoard[8][7] = 1;
  AnswersBoard[8][8] = 1;
};

void setUserBoard()
{
  for (int i = 0; i < MAX_HEIGHT; i++)
  {
    for (int j = 0; j < MAX_WIDTH; j++)
    {
      UserBoard[i][j] = 11;
    }
  }
}

void printBoard()
{
  for (int i = 0; i <= MAX_WIDTH; i++)
  {
    if (i == MAX_WIDTH)
      printf("   ");
    else
      printf(" %d ", i + 1);
    for (int j = 0; j < MAX_HEIGHT; j++)
    {
      if (i == MAX_WIDTH)
        printf(" %c ", j + 65);
      else if (UserBoard[i][j] == 11)
        printf("[ ]");
      else if (UserBoard[i][j] == 10)
        printf("[B]");
      else if (UserBoard[i][j] == 9)
        printf("[F]");
      else
        printf("[%d]", UserBoard[i][j]);
    }
    printf("\n");
  }
};

void openBoard(int column, int row) {
  pthread_t thr1;
  

};

void* f_thread(void *v) {
  Quadrant *id = (Quadrant*)v;
  for (int i = id->start_row; i <= id->end_row; i++) {
    for (int j = id->start_column; j <= id->end_column; j++)
    {
      if(UserBoard[i][j] == 11 || UserBoard[i][j] == 9) 
          id->return_thread++; 
    }
  }
  return NULL; 
} 

int isBoardCompleted()
{
  int flags_and_spaces;
  int middle_width = (int)MAX_WIDTH/2;
  int middle_height = (int)MAX_HEIGHT/2;
  pthread_t thr1, thr2, thr3, thr4;
  Quadrant first_quadrant = {0, 0, middle_height, middle_width, 0};
  Quadrant second_quadrant = {0, middle_width + 1, middle_height, MAX_WIDTH - 1, 0};
  Quadrant third_quadrant = {middle_height + 1, 0, MAX_HEIGHT - 1, middle_width, 0};
  Quadrant fourth_quadrant = {middle_height + 1, middle_width + 1, MAX_HEIGHT - 1, MAX_WIDTH - 1, 0};

  pthread_create(&thr1, NULL, f_thread, (void*)&first_quadrant);
  pthread_create(&thr2, NULL, f_thread, (void*)&second_quadrant);
  pthread_create(&thr3, NULL, f_thread, (void*)&third_quadrant);
  pthread_create(&thr4, NULL, f_thread, (void*)&fourth_quadrant);

  pthread_join(thr1, NULL);
  pthread_join(thr2, NULL);
  pthread_join(thr3, NULL);
  pthread_join(thr4, NULL);

  flags_and_spaces = first_quadrant.return_thread + second_quadrant.return_thread + third_quadrant.return_thread + fourth_quadrant.return_thread;
  if (flags_and_spaces == 10) {
    printf("\n YOU WIN :)\n\n");
    return 0;
  }
  return 1;
}

