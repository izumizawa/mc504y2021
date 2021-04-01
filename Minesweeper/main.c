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

void setAnswersBoard();
void setUserBoard();
void printBoard();
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
      scanf(" %s", &cell);
      cell[0] = toupper(cell[0]);
      row = (int)cell[1] - 49;
      column = (int)cell[0] - 65;
      if (row < MAX_HEIGHT && row >= 0 && column < MAX_WIDTH && column >= 0)
      {
        UserBoard[row][column] = AnswersBoard[row][column];
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
      scanf(" %s", &cell);
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

    printBoard();

  } while (isBoardCompleted());

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

int isBoardCompleted()
{
  // use Pthread
  return 0;
}