# Matrix diagonal traversal
A wavefront sweep of a matrix of any dimension, starting from the top-right element and going to the bottom-left one.

This program performs a wavefront sweep of a matrix, i.e. prints its elements
considering the diagonals, starting from the top right element and going to
the bottom left one, printing them in right-down order.
For example, the following matrix:
```math
\begin{bmatrix} 1 & 2 & 3 \\\ 4 & 5 & 6 \\\ 7 & 8 & 9 \end{bmatrix}
```
  1   2   3
  4   5   6
  7   8   9
  
would be sliced into:
 
Slice 0: 3
Slice 1: 2 6
Slice 2: 1 5 9
Slice 3: 4 8
Slice 4: 7
 
The maximum number of slices is n + m - 1, where n is the number of rows and m is the
number of columns.
 
This program is also able to slice only the superior triangular matrix, but the output
only makes sense if the input matrix is a square matrix.
 
You can configure the number of rows and columns by changing the #define directives
you will find in the code. The program automatically generates a matrix with the
specified dimensions. In case you choose n = 0 and m = 0, the assertion in the
"slicer" function will fail, causing the abortion of the process.
 
To compile:
``` 
gcc slicer.c -o slicer
```
 
Sources:
 
https://stackoverflow.com/questions/2112832/traverse-rectangular-matrix-in-diagonal-strips
 
https://www.geeksforgeeks.org/zigzag-or-diagonal-traversal-of-matrix/
 

