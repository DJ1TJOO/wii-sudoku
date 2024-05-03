#include "sudoku_generator.h"

static int mat[N][N];

static short unUsedInBox(int rowStart, int colStart, int num)
{
    for (int i = 0; i < SRN; i++)
        for (int j = 0; j < SRN; j++)
            if (mat[rowStart + i][colStart + j] == num)
                return 0;

    return 1;
}

static short randomGenerator(int num)
{
    return (int)(rand() % num) + 1;
}

static short unUsedInRow(int i, int num)
{
    for (int j = 0; j < N; j++)
        if (mat[i][j] == num)
            return 0;
    return 1;
}

// check in the row for existence
static short unUsedInCol(int j, int num)
{
    for (int i = 0; i < N; i++)
        if (mat[i][j] == num)
            return 0;
    return 1;
}

static short CheckIfSafe(int i, int j, int num)
{
    return (unUsedInRow(i, num) &&
            unUsedInCol(j, num) &&
            unUsedInBox(i - i % SRN, j - j % SRN, num));
}

static void fillBox(int row, int col)
{
    int num;
    for (int i = 0; i < SRN; i++)
    {
        for (int j = 0; j < SRN; j++)
        {
            do
            {
                num = randomGenerator(N);
            } while (!unUsedInBox(row, col, num));

            mat[row + i][col + j] = num;
        }
    }
}

static void fillDiagonal()
{
    for (int i = 0; i < N; i = i + SRN)
        fillBox(i, i);
}

static short fillRemaining(int i, int j)
{
    if (j >= N && i < N - 1)
    {
        i = i + 1;
        j = 0;
    }
    if (i >= N && j >= N)
        return 1;

    if (i < SRN)
    {
        if (j < SRN)
            j = SRN;
    }
    else if (i < N - SRN)
    {
        if (j == (int)(i / SRN) * SRN)
            j = j + SRN;
    }
    else
    {
        if (j == N - SRN)
        {
            i = i + 1;
            j = 0;
            if (i >= N)
                return 1;
        }
    }

    for (int num = 1; num <= N; num++)
    {
        if (CheckIfSafe(i, j, num))
        {
            mat[i][j] = num;
            if (fillRemaining(i, j + 1))
                return 1;

            mat[i][j] = 0;
        }
    }
    return 0;
}

static void removeKDigits()
{
    int count = K;
    while (count != 0)
    {
        int cellId = randomGenerator(N * N);

        int i = (cellId / N);
        int j = cellId % 9;
        // if (j != 0)
        //     j = j - 1;

        if (mat[i][j] != 0)
        {
            count--;
            mat[i][j] = 0;
        }
    }
}

static void fillValues()
{
    // Fill the diagonal of SRN x SRN matrices
    fillDiagonal();

    // Fill remaining blocks
    fillRemaining(0, SRN);

    // Remove Randomly K digits to make game
    removeKDigits();
}

int *generateSudoku()
{
    srand(time(NULL));
    fillValues();

    int *sudoku = malloc(sizeof(int) * N * N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            sudoku[i * N + j] = mat[i][j];

    return sudoku;
}