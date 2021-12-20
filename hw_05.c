#include <locale.h>

#include "geek.h"

#define RAND_D 100

void qsm(int* arr, int first, int last)
{
    printf("qsm first: %d last: %d\n", first, last);
    if(last-first > 10-1)
    {
        int i = first;
        int j = last;
        int i_x = (first + last) / 2;

        printf("до: arr[first]: %d arr[i_x]: %d arr[last]: %d\n", arr[first], arr[i_x], arr[last]);
        if ((arr[first]<arr[i_x])&&(arr[i_x]>arr[last]))
        {
            if(arr[first]<=arr[last])
                swapInt(arr+i_x, arr+last);
            else
                swapInt(arr+first, arr+i_x);
        }
        else if ((arr[first]>arr[i_x])&&(arr[i_x]<arr[last]))
        {
            if(arr[first]<=arr[last])
                swapInt(arr+first, arr+i_x);
            else
                swapInt(arr+i_x, arr+last);
        }
        printf("median: arr[first]: %d arr[i_x]: %d arr[last]: %d\n\n", arr[first], arr[i_x], arr[last]);

        int x = arr[i_x];

        do
        {
            while (arr[i] < x)
                i++;
            while (arr[j] > x)
                j--;

            if (i <= j)
            {
                swapInt(&arr[i], &arr[j]);
                i++;
                j--;
            }
        } while (i <= j);

        if (i < last)
        {
            if(last-i > 10-1)
                qsm(arr, i, last);
            else
            {
                printf("sortIntInserts i: %d last: %d size: %d\n\n", i, last, last-i+1);
                sortIntInserts(arr+i, last-i+1);
            }
        }

        if (first < j)
        {
            if(j-first > 10-1)
                qsm(arr, first, j);
            else
            {
                printf("sortIntInserts first: %d j: %d size: %d\n\n", first, j, j-first+1);
                sortIntInserts(arr+first, j-first+1);
            }
        }
    }
    else
    {
        printf("sortIntInserts first: %d last: %d size: %d\n\n", first, last, last-first+1);
        sortIntInserts(arr+first, last-first+1);
    }
}

void bucketSortM(int* arr, int len) {
    const int max = len;
    const int b = 10;

    int buckets[b][max+1];
    for (int i = 0; i < b; ++i) {
        buckets[i][max] = 0;
    }

    for (int digit = 1; digit < 100000; digit*=10) {
        int indArrInd = 0;
        int indArr[len];
        printf("\ndigit: %d\n", digit);
        for (int i = 0; i < max; ++i) {
            int d = (arr[i] / digit) % b;
//            printf("d: %d  ", d);

//            int counter = buckets[d][max];
//            buckets[d][counter] = arr[i];
//            counter++;
//            buckets[d][max] = counter;

            if (!(arr[i]%2))
                buckets[d][buckets[d][max]++] = arr[i];
            else
                indArr[indArrInd++] = i;
        }
        int idx = 0;
        int indI = 0;
        for (int i = 0; i < b; ++i) {
            printf("\nb: %d\n", i);
            for (int j = 0; j < buckets[i][max]; ++j)
            {
                printf("%d ", buckets[i][j]);
                while(1)
                {
                    if ((indI<indArrInd)&&(idx == indArr[indI]))
                    {
//                        printf("\tindI: %d, indArr[indI]: %d\n", indI, indArr[indI]);
                        indI++;
                        idx++;
                    }
                    else
                    {
                        arr[idx++] = buckets[i][j];
                        break;
                    }
                }
            }
            buckets[i][max] = 0;
        }
        printf("\ncurr: ");
        for(int i = 0; i< len; i++)
            printf("%d ", arr[i]);
        printf("\n");
    }
}

int main()
{
    const int SIZE = 30;
    int array[SIZE];
    setlocale(LC_ALL, "");
    printf("1 Улучшенный алгоритм быстрой сортировки\n");
    printf("Исходный массив случайных чисел:\n");
    fillIntRandom(array, SIZE, RAND_D);
    printIntArray(array, SIZE, 3);
    printf("\nСортировка массива:\n");
    //sortIntInserts(array, SIZE);
    qsm(array, 0, SIZE-1);
    printf("\nОтсортированный массив:\n");
    printIntArray(array, SIZE, 3);

    printf("\n2 Алгоритм блочной сортировки\n");
    printf("Исходный массив случайных чисел:\n");
    fillIntRandom(array, SIZE, RAND_D);
    printIntArray(array, SIZE, 3);
    bucketSortM(array, SIZE);
    printf("\nОтсортированный массив:\n");
    printIntArray(array, SIZE, 3);
    return 0;
}
