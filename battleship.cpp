/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>

//#define FIELDSIZE   10
#include "battleship.h"
static FILE* fdmy;
static FILE* fdop;
static CellContent myContent[FIELDSIZE][FIELDSIZE];
static CellContent opContent[FIELDSIZE][FIELDSIZE];
static CellContent guesses[FIELDSIZE][FIELDSIZE];
void load_game()
{
     fdmy = fopen("battleship.my", "r");
     fdop = fopen("battleship.op", "r");

     fread(&myContent, sizeof(myContent), 1, fdmy);
     fread(&opContent, sizeof(opContent), 1, fdop);
     for (int i = 0; i < FIELDSIZE; i++)
     {
         for (int j = 0; j < FIELDSIZE; j++)
         {
             guesses[i][j] = Unknown;
         }
     }



}

/**
*** @param row The row where we get the shot.
*** @param col The col where we get the shot.
*** @return The value of cell indicated by row and column of the own field (filled
*** with the values of battleship.my). If row/col point outside the field the
*** value OutOfRange is returned.
*/
CellContent get_shot(int row, int col)
{
    if (row < 0 || row > FIELDSIZE-1 || col < 0 || col > FIELDSIZE-1)
    {
        return OutOfRange;
    }
    return myContent[row][col];


}

void surround_with_Water(int row, int col)
{
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if ((row-i >= 0 && row-i < FIELDSIZE) && (col-j >= 0 && col-j < FIELDSIZE))
            {
                guesses[row-i][col-j] = Water;
            }
        }
    }


}

bool IsNotOnBoard(int row, int col)
{
  return (row < 0 || row > FIELDSIZE-1 || col < 0 || col > FIELDSIZE-1);
}

/**
*** Sets the row and column of the my guesses table to the value held in the
*** opponents field. If this is a boat all surrounding cells are marked as water.
*** @param row The row where we place the shot
*** @param col The columnt where we place the shot.
*** @return True if target field is valid, i.e., inside the field, False otherwise.
*/
bool shoot(int row, int col)
{
  if (IsNotOnBoard(row, col))
  {
    return false;
  }
  if (opContent[row][col] == Boat)
  {
    surround_with_Water(row,col);
    guesses[row][col] = Boat;
    return true;
  }
  if (opContent[row][col] == Water)
  {
    guesses[row][col] = Water;
    return true;
  }
  return false;

}

/**
*** @param row The row where we want to get our own guess.
*** @param col The column where we want to get our own guess.
*** @return The value of the table with my guesses at row and column. If row/col
*** is outside the field OutOfRange is returned.
*/
CellContent get_my_guess(int row, int col)
{
  if (IsNotOnBoard(row,col))
  {
    return OutOfRange;
  }
  else
  {
    return guesses[row][col];
  }

}
