/*
----------------------------------------------------NAME : DEVANSH KHOSLA----------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>// bool library is used for putting true or false statements

#define SIZE 9

//-----------------------------------------------------Function to print the Sudoku grid---------------------------------------------------------

void printMatrix(int matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

//--------------------------------------Function to check if it's valid to place num in the given row, column-----------------------------------

bool isValid(int matrix[SIZE][SIZE], int row, int col, int num) {
    // Check the row
    for (int j = 0; j < SIZE; j++) {
        if (matrix[row][j] == num) {
            return false;
        }
    }
    
//-----------------------------------------------------------Check the column----------------------------------------------------------------
   
    for (int i = 0; i < SIZE; i++) {
        if (matrix[i][col] == num) {
            return false;
        }
    }
 //------------------------------------------------------- Check the 3x3 subgrid---------------------------------------------------------------
   
    int startRow = row - row % 3;   // checking row in a 3x3 matrix if therw is any number that is repeating or not
    int startCol = col - col % 3;
    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            if (matrix[i][j] == num) {
                return false; // if same number is fount in the 3x3 matrix then returne false and its not safe to put the number at that spot
            }
        }
    }

    return true;
}

//==============================Function to find the next empty cell in the Sudoku grid (represented by 0)=========================================

bool findEmptyCell(int matrix[SIZE][SIZE], int *row, int *col) {
    for (*row = 0; *row < SIZE; (*row)++) {
        for (*col = 0; *col < SIZE; (*col)++) {
            if (matrix[*row][*col] == 0) {
                return true;  // Empty cell found where ther is no input
            }
        }
    }
    return false;  // No empty cells left
}

//==================================================Backtracking function to solve the Sudoku===================================================

bool solveSudoku(int matrix[SIZE][SIZE]) {
    int row, col;

//=========================================== If there are no empty cells, the puzzle is solved================================================
    if (!findEmptyCell(matrix, &row, &col)) {
        return true;
    }

//----------------------------------------------- Try numbers 1 to 9 in the empty cell---------------------------------------------------------
    for (int num = 1; num <= 9; num++) {
        if (isValid(matrix, row, col, num)) {
            matrix[row][col] = num;  // Place the number

            // Recursively solve the rest of the grid
            if (solveSudoku(matrix)) {
                return true;
            }

            // If the number doesn't work, backtrack and try the next number
            matrix[row][col] = 0;
        }
    }

    // If no number works, return false (backtrack)
    return false;
}

int main() {
    int matrix[SIZE][SIZE];

    printf("Enter the Sudoku puzzle (0 for empty cells):\n");

    // Getting user input for the Sudoku grid
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("Enter value for cell (%d,%d): ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
            if (matrix[i][j] < 0 || matrix[i][j] > 9) {
                printf("double digit or 0 is not allowed, Enter numbers between 0 and 9.\n");
                j--; // Retry this cell input
            }
        }
    }
    

    printf("Initial Sudoku puzzle:\n");
    printMatrix(matrix);

    if (solveSudoku(matrix)) {
        printf("\nSolved Sudoku puzzle:\n");
        printMatrix(matrix);
    } else {
        printf("\nNo solution exists!\n");
    }

    return 0;
}