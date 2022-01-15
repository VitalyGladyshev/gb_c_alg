#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

unsigned char * CaesarEncode(unsigned char *ptucStr, int iKey)
{
    for(int i = 0; (ptucStr[i] && (i <= 255)); i++)
        ptucStr[i] += iKey;
    return ptucStr;
}

unsigned char * CaesarDecode(unsigned char *ptucStr, int iKey)
{
    for(int i = 0; (ptucStr[i] && (i <= 255)); i++)
        ptucStr[i] -= iKey;
    return ptucStr;
}

unsigned char * PermutationEncode(unsigned char *ptucStr, int iKey, int iLen, unsigned char *ptucEncStr)
{
    int iIndex = 0;
    for(int i = 0; i < iLen; i++)
    {
        iIndex = (iIndex+iKey)%iLen;
        ptucEncStr[i] = ptucStr[iIndex];
    }
    ptucEncStr[iLen] = 0;
    return ptucEncStr;
}

unsigned char * PermutationDecode(unsigned char *ptucEncStr, int iKey, int iLen, unsigned char *ptucStr)
{
    int iIndex = 0;
    for(int i = 0; i < iLen; i++)
    {
        iIndex = (iIndex+iKey)%iLen;
        ptucStr[iIndex] = ptucEncStr[i];
    }
    ptucStr[iLen] = 0;
    return ptucStr;
}

int main(void)
{
    setlocale(LC_ALL, "Russian");		//system("chcp 1251");

    printf("\n1 Шифрование и расшифровка Цезаря\n\n");
    unsigned char ptcStr[255] = "";
    printf("Введите строку для кодирования: ");
    gets(ptcStr);
    printf("Введите ключ шифрования (сдвиг): ");
    int iKeyShift = 0;
    scanf("%d", &iKeyShift);
    printf("\nЗашифрованная строка: %s\n", CaesarEncode(ptcStr, iKeyShift));
    printf("Расшифрованная строка: %s\n", CaesarDecode(ptcStr, iKeyShift));

    printf("\n2 Шифрование и расшифровка перестановками\n\n");
    printf("Введите строку для кодирования: ");
    ptcStr[0] = 0;
    do gets(ptcStr);
    while(!ptcStr[0]);
    printf("Введите количество столбцов: ");
    scanf("%d", &iKeyShift);
    int iLen;
    for (iLen = 0; ptcStr[iLen]; iLen++);    //printf("\nДлина: %i\n", iLen);
    if (iLen <= iKeyShift)
    {
        printf("Количество столбцов больше длины сообщения\n");
        return -1;
    }
    unsigned char *ptucEncStr = (unsigned char *)malloc(sizeof(unsigned char) * iLen);
    unsigned char *ptucDecStr = (unsigned char *)malloc(sizeof(unsigned char) * iLen);
    printf("\nЗашифрованная строка: %s\n", PermutationEncode(ptcStr, iKeyShift, iLen, ptucEncStr));
    printf("Расшифрованная строка: %s\n", PermutationDecode(ptucEncStr, iKeyShift, iLen, ptucDecStr));
    free(ptucEncStr);
    free(ptucDecStr);
    return 0;
}
