#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

unsigned char hashLike8(unsigned char *ptucStr)
{
    unsigned char ucHash = 0;
    int iIndex = 0;
    while (ptucStr[iIndex])
    {
        printf("%x ", ptucStr[iIndex]);
        ucHash += ptucStr[iIndex++];
    }
    printf("\n");
    return ucHash;
}

unsigned short hashLike16(unsigned char *ptucStr)
{
    unsigned short usHash = 0;
    int iIndex = 0;
    while (ptucStr[iIndex])
    {
        printf("%x ", *(unsigned short *)(ptucStr+iIndex));
        usHash += *(unsigned short *)(ptucStr+iIndex);
        if (ptucStr[++iIndex])
            iIndex++;
        else
            break;
    }
    printf("\n");
    return usHash;
}

void greedyCash(iKopeckNum)
{
    if (iKopeckNum < 0)
    {
       printf("Некорректный параметр!");
       return;
    }
    int ptiCoinValue[] = {50, 10, 5, 2, 1};
    int ptiCoinCount[5] = {0};
    for (int i = 0; i < 5; i++)
    {
        ptiCoinCount[i] = iKopeckNum / ptiCoinValue[i];
        iKopeckNum -= ptiCoinCount[i] * ptiCoinValue[i];
        if (iKopeckNum <= 0)
            break;
    }
    for (int i = 0; i < 5; i++)
        printf("монет %2d коп.: %d\n", ptiCoinValue[i], ptiCoinCount[i]);
    return;
}

void main(void)
{
    setlocale(LC_ALL, "Russian");		//system("chcp 1251");

    printf("\n1 Элементарная хэш-функция\n\n");

    printf("Восьмиразрядный хэш\n");
    char ptcStr[255] = "";
    printf("Введите строку: ");
    gets(ptcStr);
    printf("Хэш: %x\n", hashLike8(ptcStr));

    printf("\nШестнадцатиразрядный хэш\n");
    printf("Введите строку: ");
    gets(ptcStr);
    printf("Хэш: %x\n", hashLike16(ptcStr));

    printf("\n2 Жадный алгоритм определения набора монет\n\n");
    printf("Введите сумму в копейках: ");
    int iKopeckNum = 0;
    scanf("%d", &iKopeckNum);
    greedyCash(iKopeckNum);
}
