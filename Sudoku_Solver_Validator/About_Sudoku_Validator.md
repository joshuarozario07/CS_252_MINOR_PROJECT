# PROJECT 1 : Sudoku_Solution_Validator

The specifications for the project are as follows:

A Sudoku puzzple uses a 9x9 grid in which each column and row as well and each of the 3 x 3 subrigrids, must contain all the rigits from 1 to 9.

This projwct consists of designing a multithreaded application that determines whether the solution to the sudoku puzzple is valid or not

The stratergy implement in our project is as follows:

STEP 1: Before inputting the sudoku
Define the number of threads: 27 threads
Define a structure called parameters, with starting row, starting column and pointer to the sukodu puzzle
Create a result array in which worker threads update to 1 if the operation they performed results in valid output.
Name functions to check grids, rows and columns before starting main function

STEP 2: Main Function
User needs to input the sudoku which needs to be validated
Threads are numbered in chronological order in which they run ( 0 , 1, 2,3...26)
Threads are then created (9 threads for grids, 9 for rows and 9 for columns)
Functions to check if grid, row and column are valid are then defined

Rows, grids and columns are checked if valid with the help of a validarray [10] (initialized to 0), for every value in the square, the corresponding index in validarray[] is checked for 0 and set to 1. If validarray[] is already 1, the it means that the value is repeating, so the solution is invalid

If valid the thread updates the result array to 1, else 0.

Finally if any entries in the result array are 0, the the sudoku solution is invalid, else the solution is valid

Hence in this way we can check is the sudoku solution is valid or not.
