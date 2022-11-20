//Description:
/*
 * This program takes a Sudoku puzzle solution as an input and then determines whether
 * the puzzle solution is valid. This validation is done using both single thread and 27 threads.
 * 27 threads are created as follows:
 * 9 for each 3x3 subsection, 9 for the 9 columns, and 9 for the 9 rows.
 * Each thread returns a integer value of 1 indicating that
 * the corresponding region in the puzzle they were responsible for is valid.
 * The program then waits for all threads to complete their execution and
 * checks if the return values of all the threads have been set to 1.
 * If yes, the solution is valid. If not, solution is invalid.
 *
 * This program also displays the total time taken for validation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 	
#include <iostream>
#include <chrono>

#define num_threads 27     

using namespace std;
using namespace std::chrono;

/**
 * Structure that holds the parameters passed to a thread.
 * This specifies where the thread should start verifying.
 */
typedef struct
{
    // The starting row.
    int row;
    // The starting column.
    int col;
    // The pointer to the sudoku puzzle.
    int (* board)[9];

} parameters;

/*
    Initialize the array which worker threads can update to 1 if the
    corresponding region of the sudoku puzzle they were responsible
    for is valid.
*/
int result[num_threads] = {0};

// Prototype for 3x3 square function.
void *check_grid(void *params);

// Prototype for the check_rows function.
void *check_rows(void *params);

// Prototype for the check_cols function.
void *check_cols(void *params);


/***************
 * ENTRY POINT *
 **************/
int main(void)
{
    //====== The Sudoku puzzle to be validated =======
    int sudoku[9][9];
     
     cout << "Enter the sudoko: \n" << endl;
     
     for(int i=0; i<9; i++)
     {
     	for(int j=0; j<9; j++)
     	{
     		cin >> sudoku[i][j];
     	}
     }
     
     

    // Starting ti62me for execution with 27 threads
    steady_clock::time_point start_time_threads = steady_clock::now();

    pthread_t threads[num_threads];

    int threadIndex = 0;

    // ====== Create the threads ======
    //Create one thread each for the 9 3x3 grid, one thread each for the 9 columns and one thread each for the 9 rows. There will be a total of 27 thread created
    //Function call parameters are Thread identifier, thread attributes, function the thread executes, parameters passed to function
    //Syntax for pthread_create function is pthread_create(pthread_t * thread, pthread_attr_t * attr, void * (*start_routine)(void *), void * arg);
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            // ==45==== Declaration of the parameter for the 3X3 grid check threads =======
            if (i%3 == 0 && j%3 == 0)
            {
                parameters *gridData = (parameters *) malloc(sizeof(parameters));
                gridData->row = i;
                gridData->col = j;
                gridData->board = sudoku;
                pthread_create(&threads[threadIndex++], NULL, check_grid, gridData);
            }

            // ====== Declaration of the parameter for the row check threads =======
            if (j == 0)
            {
                parameters *rowData = (parameters *) malloc(sizeof(parameters));
                rowData->row = i;
                rowData->col = j;
                rowData->board = sudoku;
                pthread_create(&threads[threadIndex++], NULL, check_rows, rowData);
            }

            // ====== Declaration of the parameter for the column check threads =======
            if (i == 0)
            {
                parameters *columnData = (parameters *) malloc(sizeof(parameters));
                columnData->row = i;
                columnData->col = j;
                columnData->board = sudoku;
                pthread_create(&threads[threadIndex++], NULL, check_cols, columnData);
            }
        }
    }

    // ======= Wait for all threads to finish their tasks =======
    //Parameters are Thread identifier and the return value of the function executed by the thread
    for (int i = 0; i < num_threads; i++)
        pthread_join(threads[i], NULL);


    // If any of the entries in the result array are 0, then the Sudoku solution is invalid
    for (int i = 0; i < num_threads; i++)
    {
        if (result[i] == 0)
        {
            cout << "Sudoku solution is invalid" << endl;

            // Compute and return the elapsed time in milliseconds.
            steady_clock::time_point end_time_threads = steady_clock::now();
            duration<double> elapsed_time_threads = duration_cast<duration<double>>(end_time_threads - start_time_threads);

            cout << endl << "Total time using 27 threads: " << elapsed_time_threads.count() << " seconds" << endl;
            return 1;
        }
    }
    cout << "Sudoku solution is valid" << endl;

    // Compute and return the elapsed time in milliseconds.
    steady_clock::time_point end_time_threads = steady_clock::now();
    duration<double> elapsed_time_threads = duration_cast<duration<double>>(end_time_threads - start_time_threads);

    cout << endl << "Total time using 27 threads: " << elapsed_time_threads.count() << " seconds" << endl;

}

/*
 * Checks if a square of size 3x3 contains all numbers from 1-9.
 * There is an array called validarray[10] initialized to 0.
 * For every value in the square, the corresponding index in validarray[] is checked for 0 and set to 1.
 * If the value in validarray[] is already 1, then it means that the value is repeating. So, the solution is invalid.
 *
 * @param   void *      The parameters (pointer).
 */
void *check_grid(void * params)
{
    parameters *data = (parameters *) params;
    int startRow = data->row;
    int startCol = data->col;
    int validarray[10] = {0};
    for (int i = startRow; i < startRow + 3; ++i)
    {
        for (int j = startCol; j < startCol + 3; ++j)
        {
            int val = data->board[i][j];
            if (validarray[val] != 0)
                pthread_exit(NULL);
            else
                validarray[val] = 1;
        }
    }

    // If the execution has reached this point, then the 3x3 sub-grid is valid.
    result[startRow + startCol/3] = 1; // Maps the 3X3 sub-grid to an index in the first 9 indices of the result array
    pthread_exit(NULL);
}

/**
 * Checks each row if it contains all digits 1-9.
 * There is an array called validarray[10] initialized to 0.
 * For every value in the row, the corresponding index in validarray[] is checked for 0 and set to 1.
 * If the value in validarray[] is already 1, then it means that the value is repeating. So, the solution is invalid.
 *
 * @param   void *      The parameters (pointer).
 */

void *check_rows(void *params)
{
    parameters *data = (parameters *) params;
    int row = data->row;

    int validarray[10] = {0};
    for (int j = 0; j < 9; j++)
    {
        int val = data->board[row][j];
        if (validarray[val] != 0)
            pthread_exit(NULL);
        else
            validarray[val] = 1;
    }

    // If the execution has reached this point, then the row is valid.
    result[9 + row] = 1; // Maps the row to an index in the second set of 9 indices of the result array
    pthread_exit(NULL);
}

/**
 * Checks each column if it contains all digits 1-9.
 * There is an array called validarray[10] initialized to 0.
 * For every value in the row, the corresponding index in validarray[] is checked for 0 and set to 1.
 * If the value in validarray[] is already 1, then it means that the value is repeating. So, the solution is invalid.
 *
 * @param   void *      The parameters (pointer).
 */
void *check_cols(void *params)
{
    parameters *data = (parameters *) params;
    //int startRow = data->row;
    int col = data->col;

    int validarray[10] = {0};
    for (int i = 0; i < 9; i++)
    {
        int val = data->board[i][col];
        if (validarray[val] != 0)
            pthread_exit(NULL);
        else
            validarray[val] = 1;
    }

    // If the execution has reached this point, then the column is valid.
    result[18 + col] = 1; // Maps the column to an index in the third set of 9 indices of the result array
    pthread_exit(NULL);
 }

/**
 * Checks each 3*3 grid if it contains all digits 1-9.
 * There is an array called validarray[10] initialized to 0.
 * For every value in the row/column, the corresponding index in validarray[] is checked for 0 and set to 1.
 * If the value in validarray[] is already 1, then it means that the value is repeating. So, the solution is invalid.
 *
 * @param   void *      The parameters (pointer).
 */
int check_grid(int sudoku[9][9])
{
    int temp_row, temp_col;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            temp_row = 3 * i;
            temp_col = 3 * j;
            int validarray[10] = {0};

            for(int p=temp_row; p < temp_row+3; p++)
            {
                for(int q=temp_col; q < temp_col+3; q++)
                {
                    int val = sudoku[p][q];
                    if (validarray[val] != 0)
                        return 1;
                    else
                        validarray[val] = 1;
                }
            }
        }
    }
    return 0;
}

