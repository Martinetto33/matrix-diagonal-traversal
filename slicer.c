/**
 * This program performs a wavefront sweep of a matrix, i.e. prints its elements
 * considering the diagonals, starting from the top right element and going to
 * the bottom left one, printing them in right-down order.
 * For example, the following matrix:
 * 
 *  1   2   3
 *  4   5   6
 *  7   8   9
 * 
 * would be sliced into:
 * 
 * Slice 0: 3
 * Slice 1: 2 6
 * Slice 2: 1 5 9
 * Slice 3: 4 8
 * Slice 4: 7
 * 
 * The maximum number of slices is n + m - 1, where n is the number of rows and m is the
 * number of columns.
 * 
 * This program is also able to slice only the superior triangular matrix, but the output
 * only makes sense if the input matrix is a square matrix.
 * 
 * You can configure the number of rows and columns by changing the #define directives
 * you will find in the code. The program automatically generates a matrix with the
 * specified dimensions. In case you choose n = 0 and m = 0, the assertion in the
 * "slicer" function will fail, causing the abortion of the process.
 * 
 * To compile:
 * 
 *  gcc slicer.c -o slicer
 * 
 * Sources:
 * 
 * https://stackoverflow.com/questions/2112832/traverse-rectangular-matrix-in-diagonal-strips
 * 
 * https://www.geeksforgeeks.org/zigzag-or-diagonal-traversal-of-matrix/
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#define ROWS 2
#define COLUMNS 1

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

/**
 * The number of slices corresponds to the number of diagonals to be printed.
 * 
 * In the course of each iteration of the first for loop, the column and
 * row of the first element to be printed is determined. Then the variable
 * "count" is assigned the number of elements to be printed for one specific
 * diagonal.
 * 
 * Let's consider an example matrix:
 * 
 * 
 * 1    2   3   4   5
 * 6    7   8   9   10
 * 11   12  13  14  15
 * 
 * n = 3, m = 5
 * number of slices = n + m - 1 = 7 (supposing that the caller wants to slice the
 * whole matrix)
 * 
 * The following table reports the number of the slice and the column and row
 * indexes of the elements that should be printed:
 * 
 * SLICE NR.        ROW         COLUMN 
 * 0                0           4          -> take element in position matrix[0][4]
 * 1                0, 1        3, 4       -> take elements in position matrix[0][3] and matrix[1][4] 
 * 2                0, 1, 2     2, 3, 4    -> take matrix[0][2], matrix[1][3], matrix[2][4]
 * 3                0, 1, 2     1, 2, 3    -> ...
 * 4                0, 1, 2     0, 1, 2
 * 5                1, 2        0, 1
 * 6                2           0
 * 
 * So for each step, the starting column has index = max(0, m - 1 - slice)
 * and the starting row has index = max(0, slice - m + 1). This means that
 * when slice < max_column_index (which is m - 1), in order to get the column
 * of the first element we need to skip the first max_column_index - slice
 * columns. When slice becomes >= max_column_index, the first element to be
 * printed is always in the first column.
 * Similarly, while slice < max_column_index, the first element is always
 * in the first row, so no rows should be skipped. Instead, when slice
 * is >= max_column_index, the first element is found after skipping
 * slice - m + 1 columns.
 * 
 * Once determined the indexes of the first element, the number of elements
 * in the current diagonal is determined by calculating the minimum of
 * (slice, max_column_index - start_column, max_row_index - start_row) + 1.
 * In the considered example, a diagonal must always contain at least 1 element
 * and can never contain more than max_row_index - minimum_start_row + 1 elements = 
 * 2 - 0 + 1 = 3. This is because in this specific example the number of
 * rows is less than the number of columns, so the rows are the limiting factor.
 * 
 * Once determined the number of elements of the diagonal, the inner for loop
 * prints them one by one.
*/
void slicer(int** matrix, int n, int m, int slice_limit) {
    assert(slice_limit <= n + m - 1 && slice_limit >= 0);
    for (int slice = 0; slice < slice_limit; slice++) {
        printf("Slice %d: ", slice);
        int start_column = max(0, m - 1 - slice);
        int start_row = max(0, slice - m + 1);
        int count = min(min(slice, m - 1 - start_column), n - 1 - start_row) + 1;
        printf(" [count = %d] ", count);
        for (int j = 0; j < count; j++) {
            printf("%d ", matrix[max(j, slice - m + 1 + j)][max(j, m - 1 - slice + j)]);
        }
        puts("");
    }
}

void slice_whole_matrix(int** matrix, int n, int m) {
    slicer(matrix, n, m, n + m - 1);
}

/* This function only makes sense for square matrices, i.e. matrices
with the same number of rows and columns. */
void slice_superior_triangular_matrix(int** matrix, int n, int m, bool exclude_primary_diagonal) {
    if (exclude_primary_diagonal) {
        slicer(matrix, n, m, (n + m) / 2 - 1);
    } else {
        slicer(matrix, n, m, (n + m) / 2);
    }
}

int main() {
    /* Matrix creation. */
    int** matrix = (int **)malloc(sizeof(int*) * ROWS);
    for(int i = 0; i < ROWS; i++) {
        matrix[i] = (int *)malloc(COLUMNS * sizeof(int));
    }

    /* Prints the matrix. Useful to check correctness of the
    slices. */
    puts("Matrix:");
    for(int i = 0; i < ROWS; i++) {
        printf("Row %d: ", i);
        for(int j = 0; j < COLUMNS; j++) {
            matrix[i][j] = i * COLUMNS + j;
            printf("%d\t ", matrix[i][j]);
        }
        puts("");
    }

    int n = ROWS;
    int m = COLUMNS;
    slice_whole_matrix(matrix, n, m);
    puts("Now only the superior triangular matrix, with primary diagonal.");
    slice_superior_triangular_matrix(matrix, n, m, false);
    puts("And now the same but without the primary diagonal.");
    slice_superior_triangular_matrix(matrix, n, m, true);

    /* Deallocation of the matrix. */
    for(int i = 0; i < ROWS; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
