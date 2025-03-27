#include <iostream>
#include "clui.h"
#include <cstring>
#include <conio.h>
#include <ctime>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;
//----------------------------------------------------------------
int rows;
int columns;
bool alreadyGotRowCol = false;
//----------------------------------------------------------------
struct User
{
    char name[50];
    int score;
    int rightMoves;
    int wrongMoves;
    int remainingTime;
};
User users[100];
int userCount = 0;
//----------------------------------------------------------------
const int MAX_USERS = 100;
const int MAX_USERNAME_LENGTH = 50;
char usernames[MAX_USERS][MAX_USERNAME_LENGTH];
bool alreadyGotHint = false;
int members = 0;
string userName;
int score = 0;
int wrongMoves = 0;
int rightMoves = 0;
//----------------------------------------------------------------
const int GRID_SIZE = 9;
int gridSuduko[GRID_SIZE][GRID_SIZE] = { // Player Sudoku grid
    {5, 3, 4, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 9, 0, 6, 0, 0, 2, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 8, 0, 0, 8, 0, 0, 7, 9}};
//----------------------------------------------------------------
int Pregrid[GRID_SIZE][GRID_SIZE] = { // Pre-set Sudoku grid
    {5, 3, 4, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 9, 0, 6, 0, 0, 2, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 8, 0, 0, 8, 0, 0, 7, 9}};
//----------------------------------------------------------------
int completedSuduko[GRID_SIZE][GRID_SIZE] = { // Completed Sudoku grid
    {5, 3, 4, 6, 7, 8, 9, 1, 2},
    {6, 7, 2, 1, 9, 5, 3, 4, 8},
    {1, 9, 8, 3, 4, 2, 5, 6, 7},
    {8, 5, 9, 7, 6, 1, 4, 2, 3},
    {4, 2, 6, 8, 5, 3, 7, 9, 1},
    {7, 1, 3, 9, 2, 4, 8, 5, 6},
    {9, 6, 1, 5, 3, 7, 2, 8, 4},
    {2, 8, 7, 4, 1, 9, 6, 3, 5},
    {3, 4, 5, 2, 8, 6, 1, 7, 9}};