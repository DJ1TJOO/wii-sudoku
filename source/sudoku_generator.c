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

static short hasEmptyCell()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (mat[i][j] == 0)
                return 1;
    return 0;
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

static short solveSudoku(int *numberOfSolution)
{
    int row, col;

    for (int cellId = 0; cellId < N * N; cellId++)
    {
        row = (cellId / N);
        col = cellId % 9;

        if (mat[row][col] == 0)
        {
            for (int num = 1; num <= N; num++)
            {
                if (CheckIfSafe(row, col, num))
                {
                    mat[row][col] = num;

                    if (!hasEmptyCell())
                    {
                        (*numberOfSolution)++;
                        break;
                    }

                    if (solveSudoku(numberOfSolution))
                        return 1;
                }
            }

            break;
        }
    }

    mat[row][col] = 0;

    return 0;
}

static void fillValues()
{
    srand(time(NULL));

    // Fill the diagonal of SRN x SRN matrices
    fillDiagonal();

    // Fill remaining blocks
    fillRemaining(0, SRN);

    // Remove digits
    srand(time(NULL));

    int attempt = DIFFICULTY;
    while (attempt > 0)
    {
        int row = randomGenerator(N);
        int col = randomGenerator(N);

        while (mat[row][col] == 0)
        {
            row = randomGenerator(N);
            col = randomGenerator(N);
        }

        int backupValue = mat[row][col];
        mat[row][col] = 0;

        int numberOfSolution = 0;
        solveSudoku(&numberOfSolution);

        if (numberOfSolution != 1)
        {
            mat[row][col] = backupValue;
            attempt--;
        }
    }
}

int *generateSudoku()
{
    fillValues();

    int *sudoku = (int *)malloc(sizeof(int) * N * N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            sudoku[i * N + j] = mat[i][j];

    return sudoku;
}