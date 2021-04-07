#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
/* Minesweeper board meanings
  0: Blank space = no bombs around
  1 ~ 8: Number of bombs around the space
  10: Bomb (B)
*/

#define MAX_HEIGHT 9
#define MAX_WIDTH 9
#define BOMBS 10

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

typedef struct CurrentCell {
  Cell*** board;
  int row;
  int column;
} CurrentCell;

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
  printf(" \e[1;35mWelcome to Minesweeer!\e[0m\n");
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
        if (board[row][column]->value == 10) {
          board[row][column]->is_open = 1;
          printf("\n \e[1;31mGAME OVER :(\e[0m\n\n");
          break;
        } 
        else if (board[row][column]->value == 0) 
        {
          openBoard(board, column, row);
        }
        else
        {
          board[row][column]->is_open = 1;
        }
      }
      else
      {
        printf("\e[1;31mInvalid command\e[0m\n");
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
        printf("\e[1;31mInvalid command\e[0m\n");
      }
    }
    else if (command == 'q')
    {
      break;
    }
    else
    {
      printf("\e[1;31mInvalid command\e[0m\n");
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
  int bombs = BOMBS;
  while (bombs != 0) 
  {
    int row = rand()%9;
    int column =  rand()%9;
    if (cell[row][column]->value != 10) {
      cell[row][column]->value = 10;
      bombs--;
    }
  }
};

// Create fixed board
void setValuesBoard(Cell ***cell)
{
  for (int i = 0; i < MAX_HEIGHT; i++)
  {
    for (int j = 0; j < MAX_WIDTH; j++)
    {
      if(cell[i][j]->value == 10) 
      {
        if (i - 1 < MAX_HEIGHT && i - 1 >= 0 && j - 1 < MAX_WIDTH && j - 1 >= 0)
          if (cell[i-1][j-1]->value != 10)
            cell[i-1][j-1]->value++;
        if (i < MAX_HEIGHT && i >= 0 && j - 1 < MAX_WIDTH && j - 1 >= 0)
          if (cell[i][j-1]->value != 10)
            cell[i][j-1]->value++;
        if (i + 1 < MAX_HEIGHT && i + 1 >= 0 && j - 1 < MAX_WIDTH && j - 1 >= 0)
          if (cell[i+1][j-1]->value != 10)
            cell[i+1][j-1]->value++;
        if (i - 1 < MAX_HEIGHT && i - 1 >= 0 && j < MAX_WIDTH && j >= 0)
          if (cell[i-1][j]->value != 10)
            cell[i-1][j]->value++;
        if (i + 1 < MAX_HEIGHT && i + 1 >= 0 && j < MAX_WIDTH && j >= 0)
          if (cell[i+1][j]->value != 10)
            cell[i+1][j]->value++;
        if (i - 1 < MAX_HEIGHT && i - 1 >= 0 && j + 1 < MAX_WIDTH && j + 1 >= 0)
          if (cell[i-1][j+1]->value != 10)
            cell[i-1][j+1]->value++;
        if (i < MAX_HEIGHT && i >= 0 && j + 1 < MAX_WIDTH && j + 1 >= 0)
          if (cell[i][j+1]->value != 10)
            cell[i][j+1]->value++;
        if (i + 1 < MAX_HEIGHT && i + 1 >= 0 && j + 1 < MAX_WIDTH && j + 1 >= 0)
          if (cell[i+1][j+1]->value != 10)
            cell[i+1][j+1]->value++;
      }
    }
  }
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
      printf(" \e[1;35m%d \e[0m", i + 1);
    for (int j = 0; j < MAX_HEIGHT; j++)
    {
      if (i == MAX_WIDTH)
        printf(" \e[1;35m%c \e[0m", j + 65);
      else if(cell[i][j]->is_open) {
        if (cell[i][j]->is_flagged)
          printf("\e[1;33m[F]\e[0m");
        else if (cell[i][j]->value == 10)
          printf("\e[1;31m[B]\e[0m");
        else if (cell[i][j]->value == 0)
          printf("\e[1;36m[%d]\e[0m", cell[i][j]->value);
        else if (cell[i][j]->value == 1)
          printf("\e[1;32m[%d]\e[0m", cell[i][j]->value);
        else
          printf("\e[1;33m[%d]\e[0m", cell[i][j]->value);
      } else if(cell[i][j]->is_open == 0)
        printf("[ ]");
    }
    printf("\n");
  }
};

void* p_thread_open(void *v) {
  CurrentCell *cell = (CurrentCell*)v;
  if(cell->board[cell->row][cell->column]->is_open == 0) 
  {
    cell->board[cell->row][cell->column]->is_open = 1;
    if (cell->board[cell->row][cell->column]->value == 0) 
    {
      if (cell->row - 1 < MAX_HEIGHT && cell->row - 1 >= 0 && cell->column - 1 < MAX_WIDTH && cell->column - 1 >= 0)
        openBoard(cell->board, cell->column - 1, cell->row - 1);
      if (cell->row < MAX_HEIGHT && cell->row >= 0 && cell->column - 1 < MAX_WIDTH && cell->column - 1 >= 0)
        openBoard(cell->board, cell->column - 1, cell->row);
      if (cell->row + 1 < MAX_HEIGHT && cell->row + 1 >= 0 && cell->column - 1 < MAX_WIDTH && cell->column - 1 >= 0)
        openBoard(cell->board, cell->column - 1, cell->row + 1);
      if (cell->row - 1 < MAX_HEIGHT && cell->row - 1 >= 0 && cell->column < MAX_WIDTH && cell->column >= 0)
        openBoard(cell->board, cell->column, cell->row - 1);
      if (cell->row + 1 < MAX_HEIGHT && cell->row + 1 >= 0 && cell->column < MAX_WIDTH && cell->column >= 0)
        openBoard(cell->board, cell->column, cell->row + 1);
      if (cell->row - 1 < MAX_HEIGHT && cell->row - 1 >= 0 && cell->column + 1 < MAX_WIDTH && cell->column + 1 >= 0)
        openBoard(cell->board, cell->column + 1, cell->row - 1);
      if (cell->row < MAX_HEIGHT && cell->row >= 0 && cell->column + 1 < MAX_WIDTH && cell->column + 1 >= 0)
        openBoard(cell->board, cell->column + 1, cell->row);
      if (cell->row + 1 < MAX_HEIGHT && cell->row + 1 >= 0 && cell->column + 1 < MAX_WIDTH && cell->column + 1 >= 0)
        openBoard(cell->board, cell->column + 1, cell->row + 1);
    }
  }

};

void openBoard(Cell ***board, int column, int row) {
  pthread_t thr1;
  CurrentCell current_cell = {board, row, column};

  pthread_create(&thr1, NULL, p_thread_open, (void*)&current_cell);
  pthread_join(thr1, NULL);
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
    printf("\n \e[1;35mYOU WIN :)\e[0m\n\n");
    return 0;
  }
  return 1;
}

