#include <stdio.h>
#include <stdlib.h>

void invert(double **matrix, int n);
void input(double **matrix, int *n);
void output(double **matrix, int n);

int main()
{
    int n;
    double **matrix;

    input(&matrix, &n);

    invert(matrix, n);

    output(matrix, n);

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}

void invert(double **matrix, int n)
{
    double **augmented = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        augmented[i] = (double *)malloc(2 * n * sizeof(double));
    }

    // Создаем расширенную матрицу, где правая часть - единичная матрица
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmented[i][j] = matrix[i][j];
            augmented[i][j + n] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Приводим расширенную матрицу к диагональному виду
    for (int i = 0; i < n; i++) {
        if (augmented[i][i] == 0.0) {
            // Если ведущий элемент равен 0, ищем ненулевой элемент в той же колонке
            int nonZeroRow = -1;
            for (int j = i + 1; j < n; j++) {
                if (augmented[j][i] != 0.0) {
                    nonZeroRow = j;
                    break;
                }
            }
            // Если такой элемент найден, меняем строки местами
            if (nonZeroRow != -1) {
                double *temp = augmented[i];
                augmented[i] = augmented[nonZeroRow];
                augmented[nonZeroRow] = temp;
            } else {
                // Если ненулевой элемент не найден, обратная матрица не существует
                printf("n/a\n");
                return;
            }
        }

        double divisor = augmented[i][i];
        for (int j = 0; j < 2 * n; j++) {
            augmented[i][j] /= divisor;
        }

        for (int j = 0; j < n; j++) {
            if (j != i) {
                double factor = augmented[j][i];
                for (int k = 0; k < 2 * n; k++) {
                    augmented[j][k] -= factor * augmented[i][k];
                }
            }
        }
    }

    // Извлекаем обратную матрицу из расширенной матрицы
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = augmented[i][j + n];
        }
    }

    for (int i = 0; i < n; i++) {
        free(augmented[i]);
    }
    free(augmented);
}

void input(double ***matrix, int *n)
{
    scanf("%d", n);

    *matrix = (double **)malloc(*n * sizeof(double *));
    for (int i = 0; i < *n; i++) {
        (*matrix)[i] = (double *)malloc(*n * sizeof(double));
        for (int j = 0; j < *n; j++) {
            scanf("%lf", &((*matrix)[i][j]));
        }
    }
}

void output(double **matrix, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.6f", matrix[i][j]);
            if (j != n - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}
