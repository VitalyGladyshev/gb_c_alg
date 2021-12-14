#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

char c_arr_Bin[256];

NumToBinStr(int number)
{
    static int len, level = 0, binary = 1;

    if (level)
        binary <<= 1;
    else
        binary = 1;

    if (binary <= number)
    {
        level++;
        number = NumToBinStr(number);
        level--;
        binary >>= 1;
    }
    else
    {
        c_arr_Bin[level] = 0;
        len = level-1;
        return number;
    }
    if (binary <= number)
    {
        number = number - binary;
        c_arr_Bin[len - level] = '1';
    }
    else
        c_arr_Bin[len - level] = '0';
    return number;
}

NumToBinStrByShift(int number)
{
    static int len, level = 0;

    if (number > 0)
    {
        level++;
        int diff = NumToBinStrByShift(number >> 1);
        level--;
        if (number - diff)
            c_arr_Bin[len - level] = '1';
        else
            c_arr_Bin[len - level] = '0';
        return number << 1;
    }
    else
    {
        c_arr_Bin[level] = 0;
        len = level-1;
        return 0;
    }
}

double PowRec(double num, int ex)
{
    double res = 1;
    if (ex > 0)
    {
        if (ex - 1 > 0)
            res = PowRec(num, ex - 1);
        res *= num;
    }
    return res;
}

double PowRecAlt(double num, int ex)
{
    static double res = 1;

    if (ex > 0)
    {
        if (ex % 2)
        {
            if (ex-1)
                res = PowRecAlt(num, ex-1);
            res *= num;
        }
        else
        {
            if (ex>>1)
                res = PowRecAlt(num, ex>>1);
            if (res == 1)
                res = num;
            res *= res;
        }
    }
    return res;
}

int bricks_map[][2] = {{1, 1}, {3, 3}};
int bricks_num = 2;

int routes(int x, int y)
{
    int fr_y = 0, fr_x = 0;
    if (x == 0 && y == 0)
        return 0;
    else if (x == 0 ^ y == 0)
        return 1;
    else
    {
        for (int i = 0; i < bricks_num; i++)
        {
            if ((bricks_map[i][0] == x)&&(bricks_map[i][1] == y - 1))
                fr_y = 1;
            if ((bricks_map[i][0] == x - 1)&&(bricks_map[i][1] == y))
                fr_x = 1;
        }
        if (!fr_y)
            fr_y = routes(x, y - 1);
        if (!fr_x)
            fr_x = routes(x - 1, y);
        return fr_x + fr_y;
    }
}

int main()
{
    int number;
    setlocale(LC_ALL, "");
    printf("Преобразование десятичного числа в двоичное функцией NumToBinStr()\n");
    printf("Введите, пожалуйста, целое положительное число: ");
    scanf("%d", &number);

    if (number > 0)
    {
        NumToBinStr(number);
        printf("Число %d в двоичной системе: %s\n", number, c_arr_Bin);
    }
    else
        printf("Некорректный ввод!");

    printf("\nПреобразование десятичного числа в двоичное функцией NumToBinStrByShift()\n");
    printf("Введите, пожалуйста, целое положительное число: ");
    scanf("%d", &number);

    if (number > 0)
    {
        NumToBinStrByShift(number);
        printf("Число %d в двоичной системе: %s\n", number, c_arr_Bin);
    }
    else
        printf("Некорректный ввод!");

    double num;
    int ex;
    printf("\nВозведение в степень функцией PowRec()\n");
    printf("Введите, пожалуйста, основание: ");
    scanf("%lf", &num);
    printf("Введите, пожалуйста, показатель (целое положительное число): ");
    scanf("%d", &ex);
    if (ex >= 0)
        printf("Результат возведения числа %.4f в степень %d: %.4f\n", num, ex, PowRec(num, ex));
    else
        printf("Некорректный ввод!");

    printf("\nВозведение в степень функцией PowRecAlt()\n");
    printf("Введите, пожалуйста, основание: ");
    scanf("%lf", &num);
    printf("Введите, пожалуйста, показатель (целое положительное число): ");
    scanf("%d", &ex);
    if (ex >= 0)
        printf("Результат возведения числа %.4f в степень %d: %.4f\n", num, ex, PowRecAlt(num, ex));
    else
        printf("Некорректный ввод!");

    printf("\nНахождение количества маршрутов шахматного короля с препятствиями\n");

    const int sizeX = 5;
    const int sizeY = 5;
    for (int y = 0; y < sizeY; ++y)
    {
        for (int x = 0; x < sizeX; ++x)
        {
            int br = 0;
            for (int i = 0; i < bricks_num; i++)
                if ((bricks_map[i][0] == x)&&(bricks_map[i][1] == y))
                {
                    printf("%5c", 'X');
                    br = 1;
                }
            if (!br)
                printf("%5d", routes(x, y));
        }
        printf("\n");
    }

    return 0;
}
