#ifndef __SUDOKU_GENERATOR_H__
#define __SUDOKU_GENERATOR_H__

#define N 9          // row and col
#define SRN 3        // square and row
#define DIFFICULTY 3 // missing digits

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>

int *generateSudoku();

#endif
