#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

# define RAND_D 100

int** initArray(int** array, const int row, const int col) {
    array = (int**) calloc(sizeof(int*), row);
    for (int i = 0; i < row; ++i) {
        *(array + i) = (int*) calloc(sizeof(int), col);
    }
    return array;
}

void printArray(int** array, const int row, const int col) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            printf("%4d", *((*(array + i)) + j));
        }
        printf("\n");
    }
}

void initArrayByRandom(int** array, const int row, const int col, const int rand_d)
{
    srand(time(0));
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            *(*(array + i) + j) = rand() % rand_d;
}

void freeTwoDimIntArray(int** array, const int row)
{
    for (int i = 0; i < row; ++i)
        free(*(array + i));
    free(array);
}

void bubleTwoDimSort(int** array, const int row, const int col)
{
    int i_prv, j_prv, i, j, tmp;
    for (int len = row*col; len > 1; len--)
    {
        i = 0;
        j = 1;
        i_prv = 0;
        j_prv = 0;
        while(i*col+j < len)
        {
            if (*(*(array + i) + j) < *(*(array + i_prv) + j_prv))
            {
                tmp = *(*(array + i_prv) + j_prv);
                *(*(array + i_prv) + j_prv) = *(*(array + i) + j);
                *(*(array + i) + j) = tmp;
            }//printf("n: %d prv: %d\n", *(*(array + i) + j), *(*(array + i_prv) + j_prv));
            i_prv = i;
            j_prv = j;
            if (++j >= col)
            {
                j = 0;
                i++;
            }
        }
    }
}

int main()
{
    int **ptptiArr;
    int iArrR = 4;
    int iArrC = 5;
    setlocale(LC_ALL, "");
    printf("Сортировка двумерного массива функцией bubleTwoDimSort()\n");
    ptptiArr = initArray(ptptiArr, iArrR, iArrC);
    initArrayByRandom(ptptiArr, iArrR, iArrC, RAND_D);
    printf("Массив до сортировки:\n");
    printArray(ptptiArr, iArrR, iArrC);
    bubleTwoDimSort(ptptiArr, iArrR, iArrC);
    printf("\nМассив после сортировки:\n");
    printArray(ptptiArr, iArrR, iArrC);
    freeTwoDimIntArray(ptptiArr, iArrR);

    printf("\nАлгоритм Трабба-Прадо-Кнута\n");
    printf("Введите, пожалуйста, длину массива (целое положительное число): ");
    int len = 0;
    scanf("%d", &len);
    if (len <= 0)
    {
       printf("Некорректный ввод!");
       return 0;
    }
    double *ptdbArr = (double *)malloc(len*sizeof(double));
    for(int i = 0; i < len; i++)
    {
        printf("Введите %d элемент массива (произвольное число): ", i+1);
        scanf("%lf", ptdbArr+i);
    }
    printf("\nМассив до инвертирования:\n");
    for (int i = 0; i < len; ++i)
        printf("%.2f ", *(ptdbArr+i));
    printf("\n");
    double tmp;
    for(int i = 0; len-(i*2+1) > 1; i++)
    {
        tmp = *(ptdbArr+i);
        *(ptdbArr+i) = *(ptdbArr+len-1-i);
        *(ptdbArr+len-1-i) = tmp;
    }
    printf("\nМассив после инвертирования:\n");
    for (int i = 0; i < len; ++i)
        printf("%.2f ", *(ptdbArr+i));
    printf("\n");
    for(int i = 0; i < len; i++)
    {
        tmp = sqrt(fabs(*(ptdbArr+i))) + 5 * pow(*(ptdbArr+i), 3);
        if (tmp > 400)
            printf("Результат для элемента %d больше 400: %.4f\n", i+1, tmp);
    }
    free(ptdbArr);

    return 0;
}
