# OpenMP_matrix_multiplication

Author          : Yingqiao Zheng
Created         : October 24, 2018
Last Modified   : October 30, 2018

Affiliation     : Georgia Institute of Technology


Description
-------------

This file contains two openMP matrix multiplication programs, one of it uses static mapping method to calculate (pre-assigned tasks to every thread), the other uses dynamic mapping method (the assignment of tasks to threads is unknown until execution).

The size of the matrix is set to be N * N, which is square.

**Static mapping**: the rows of the matrix are assigned in round robin fashion to the different threads, and the assignment is in advance to execution.

**Dynamic mapping**: in this method, every thread access a global variable to decide next row to be calculated. The specific rows of the matrix assigned to a certain thread is not known until during the execution of the computation itself.


Notes
------------

The original matrices and the result matrix could be printed simply by uncomment print_matrix function in the main function.


Installation
------------

To install static mapping program, simply run

    gcc omp_matrix_static.c -std=c99 -o static

To install dynamic mapping program, simply run

	gcc omp_matrix_dynamic.c -std=c99 -o dynamic

Note: The -std=c99 flag is required on some C compilers
to allow variable declarations at arbitrary locations in
a function.


Execution
-----------

Both program use the same execution format, run them using

    ./<executable_name> <matrix_size> <number_of_threads>

For exaple, 5\*5 dynamic mapping with 3 theads

	./dynamic 5 3



