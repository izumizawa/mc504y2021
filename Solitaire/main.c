#include <stdio.h>
#include <stdbool.h>

typedef struct Card
{
  int value;   // 2 < value < 10 || 1 = A || 13 = K || 12 = Q || 11 = J
  char *suit;  // Spades || Hearts || Diamonds || Clubs
  bool isOpen; // 0 = false || 1 = true
} Card;

Card Deck[52] = {
    {1, "Diamonds", 0},
    {2, "Diamonds", 0},
    {3, "Diamonds", 0},
    {4, "Diamonds", 0},
    {5, "Diamonds", 0},
    {6, "Diamonds", 0},
    {7, "Diamonds", 0},
    {8, "Diamonds", 0},
    {9, "Diamonds", 0},
    {10, "Diamonds", 0},
    {11, "Diamonds", 0},
    {12, "Diamonds", 0},
    {13, "Diamonds", 0},
    {1, "Spades", 0},
    {2, "Spades", 0},
    {3, "Spades", 0},
    {4, "Spades", 0},
    {5, "Spades", 0},
    {6, "Spades", 0},
    {7, "Spades", 0},
    {8, "Spades", 0},
    {9, "Spades", 0},
    {10, "Spades", 0},
    {11, "Spades", 0},
    {12, "Spades", 0},
    {13, "Spades", 0},
    {1, "Hearts", 0},
    {2, "Hearts", 0},
    {3, "Hearts", 0},
    {4, "Hearts", 0},
    {5, "Hearts", 0},
    {6, "Hearts", 0},
    {7, "Hearts", 0},
    {8, "Hearts", 0},
    {9, "Hearts", 0},
    {10, "Hearts", 0},
    {11, "Hearts", 0},
    {12, "Hearts", 0},
    {13, "Hearts", 0},
    {1, "Clubs", 0},
    {2, "Clubs", 0},
    {3, "Clubs", 0},
    {4, "Clubs", 0},
    {5, "Clubs", 0},
    {6, "Clubs", 0},
    {7, "Clubs", 0},
    {8, "Clubs", 0},
    {9, "Clubs", 0},
    {10, "Clubs", 0},
    {11, "Clubs", 0},
    {12, "Clubs", 0},
    {13, "Clubs", 0}};

int main()
{
  printf("Welcome to Solitaire!\n");

  return 0;
}
