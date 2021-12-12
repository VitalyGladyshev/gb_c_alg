#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#define SIZE 10000

int get_new_prime(int *arr, int *ind);

int main()
{
    int *arr = (int *)malloc(SIZE * sizeof(int));
    arr[0] = 2;
    int ind = 0;

    int a;
    setlocale(LC_ALL, "");
    printf("Введите число не более %d: ", SIZE);
    scanf("%d", &a);

    if (a > SIZE)
    {
        printf("Слишком большое число!");
        return -1;
    }

    int is_prime = 0;
    while(1)
        if (get_new_prime(arr, &ind) != a)
        {
            if ((a % arr[ind-1] == 0)||(a < 2))
                break;
        }
        else
        {
            is_prime = 1;
            break;
        }

    if (is_prime)
        printf("Число %d простое\n", a);
    else
        printf("Число %d не является простым\n", a);

    free(arr);
	return 0;
}

int get_new_prime(int *arr, int *ind)
{
    if (*ind)
    {
        int isPrime;
        int i = arr[*ind - 1] + 1;
        while(1)
        {
            isPrime = 1;
            for (int j = 0; j < *ind; ++j)
                if (i % arr[j] == 0)
                {
                    isPrime = 0;
                    break;
                }
            if (isPrime)
            {
                arr[*ind] = i;
                *ind = *ind + 1;
                break;
            }
            i++;
        }
        return arr[*ind-1];
    }
    else
    {
        int tmp = arr[*ind];
        *ind = *ind + 1;
        return tmp;
    }
}
