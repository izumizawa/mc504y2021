#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
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

typedef struct Cell {
  int value;
  int is_open;
  int is_flagged;
} Cell;

typedef struct Quadrant {
  Cell*** board;
  int start_row;
  int start_column;
  int end_row;
  int end_column;
  int return_thread;
} Quadrant;

Cell*** createBoard();
void initBoard();
void setAnswersBoard();
void setUserBoard();
void printBoard();
void openBoard(Cell ***board, int column, int row);
int isBoardCompleted();

int main()
{
  char command;
  char cell[3];
  int row, column;
  Cell ***board = createBoard();
  printf(" Welcome to Minesweeer!\n");
  initBoard(board);
  do
  {
    printBoard(board);
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
        board[row][column]->is_open = 1;
        if (board[row][column]->value == 10) {
          printf("\n GAME OVER :(\n\n");
          break;
        } 
        else if (board[row][column]->value == 0) 
        {
          openBoard(board, column, row);
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
        board[row][column]->is_open = 1;
        board[row][column]->is_flagged = 1;
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

  } while (isBoardCompleted(board));
  printBoard(board);
  printf("\n");
  return 0;
}

Cell*** createBoard()
{
  Cell ***cell = malloc(MAX_HEIGHT * sizeof(Cell**));
  if (cell != NULL) {
    for(int i = 0; i < MAX_HEIGHT; i++) 
    {
      cell[i] = malloc(MAX_WIDTH * sizeof(Cell*));
      if(cell[i] != NULL)
      for(int j = 0; j < MAX_WIDTH; j++) 
      {
        cell[i][j] = malloc(sizeof(Cell));
      }
    }
  }
  return cell;
};

void setBombs(Cell ***cell)
{
  cell[0][7]->value = 10;
  cell[1][0]->value = 10;
  cell[1][6]->value = 10;
  cell[2][8]->value = 10;
  cell[3][7]->value = 10;
  cell[4][1]->value = 10;
  cell[4][4]->value = 10;
  cell[5][3]->value = 10;
  cell[7][8]->value = 10;
  cell[8][2]->value = 10;
};

// Create fixed board
void setValuesBoard(Cell ***cell)
{
  cell[0][0]->value = 1;
  cell[0][1]->value = 1;
  cell[0][5]->value = 1;
  cell[0][6]->value = 2;
  cell[0][8]->value = 1;
  cell[1][1]->value = 1;
  cell[1][5]->value = 1;
  cell[1][7]->value = 3;
  cell[1][8]->value = 2;
  cell[2][0]->value = 1;
  cell[2][1]->value = 1;
  cell[2][5]->value = 1;
  cell[2][6]->value = 2;
  cell[2][7]->value = 3;
  for (int i = 0; i < 7; i++)
    cell[3][i]->value = 1;
  cell[3][8]->value = 2;
  cell[4][0]->value = 1;
  cell[4][2]->value = 2;
  cell[4][3]->value = 2;
  cell[4][5]->value = 1;
  cell[4][6]->value = 1;
  cell[4][7]->value = 1;
  cell[4][8]->value = 1;
  cell[5][0]->value = 1;
  cell[5][1]->value = 1;
  cell[5][2]->value = 2;
  cell[5][4]->value = 2;
  cell[5][5]->value = 1;
  cell[6][2]->value = 1;
  cell[6][3]->value = 1;
  cell[6][4]->value = 1;
  cell[6][7]->value = 1;
  cell[6][8]->value = 1;
  cell[7][1]->value = 1;
  cell[7][2]->value = 1;
  cell[7][3]->value = 1;
  cell[7][7]->value = 1;
  cell[8][1]->value = 1;
  cell[8][3]->value = 1;
  cell[8][7]->value = 1;
  cell[8][8]->value = 1;
};

void initBoard(Cell ***cell) 
{
  for (int i = 0; i < MAX_HEIGHT; i++) 
  {
    for (int j = 0; j < MAX_WIDTH; j++) 
    {
      cell[i][j]->value = 0;
      cell[i][j]->is_open = 0;
      cell[i][j]->is_flagged = 0;
    }  
  }
  setBombs(cell);
  setValuesBoard(cell);
};

void printBoard(Cell ***cell)
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
      else if(cell[i][j]->is_open) {
        if (cell[i][j]->is_flagged)
          printf("[F]");
        else if (cell[i][j]->value == 10)
          printf("[B]");
        else
          printf("[%d]", cell[i][j]->value);
      } else if(cell[i][j]->is_open == 0)
        printf("[ ]");
    }
    printf("\n");
  }
};

void* p_thread_open(void *v) {

};

void openBoard(Cell ***board, int column, int row) {
  pthread_t thr1, thr2, thr3, thr4, thr5, thr6, thr7, thr8;

};

void* f_thread(void *v) {
  Quadrant *id = (Quadrant*)v;
  for (int i = id->start_row; i <= id->end_row; i++) {
    for (int j = id->start_column; j <= id->end_column; j++)
    {
      if(id->board[i][j]->is_open == 0 || id->board[i][j]->is_flagged) {
        id->return_thread++; 
      } 
    }
  }
  return NULL; 
} 

int isBoardCompleted(Cell ***cell)
{
  int flags_and_spaces;
  int middle_width = (int)MAX_WIDTH/2;
  int middle_height = (int)MAX_HEIGHT/2;
  pthread_t thr1, thr2, thr3, thr4;
  Quadrant first_quadrant = {cell, 0, 0, middle_height, middle_width, 0};
  Quadrant second_quadrant = {cell, 0, middle_width + 1, middle_height, MAX_WIDTH - 1, 0};
  Quadrant third_quadrant = {cell, middle_height + 1, 0, MAX_HEIGHT - 1, middle_width, 0};
  Quadrant fourth_quadrant = {cell, middle_height + 1, middle_width + 1, MAX_HEIGHT - 1, MAX_WIDTH - 1, 0};

  printf("i: 0 j: 7 open: %d flag: %d \n", cell[0][7]->is_open, cell[0][7]->is_flagged);

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

