#include <locale.h>

#include "geek.h"

#define SZ 10

typedef struct {
    int pr;
    int dat;
} Node;

Node* arr[SZ];
int head;
int tail;
int items;

void initQueue() {
    for (int i = 0; i < SZ; ++i) {
        arr[i] = NULL;
    }
    head = 0;
    tail = 0;
    items = 0;
}

void ins_pin(int pr, int dat)
{
    Node *node = (Node*) malloc(sizeof(Node));
    node->dat = dat;
    node->pr = pr;

    if (items == SZ)
    {
        printf("%s \n", "Queue is full");
        return;
    }
    else
    {
        arr[tail++ % SZ] = node;
        items++;
    }
//    printf("1 head: %d items: %d tail: %d arr[(tail-1)  SZ]: %d\n", head, items, tail, arr[(tail-1) % SZ]->dat);
}

Node* rem_pin()
{
    if (items == 0)
        return NULL;
    else
    {
        int flag = head;
        int idx;
        Node *res = arr[head % SZ];

        for (int i = head; i < tail; ++i)
        {
            idx = i % SZ;
            if (arr[idx]->pr > res->pr)
            {
                res = arr[idx];
                flag = i;
            }
        }

        while (flag > head)
        {
//            printf("2 head: %d flag: %d tail: %d arr[flag]: %d arr[(flag-1)  SZ]: %d \n", head, flag, tail, arr[flag % SZ]->dat, arr[(flag-1) % SZ]->dat);
            arr[flag % SZ] = arr[(flag-1) % SZ];
            flag--;
//            printf("3 head: %d flag: %d tail: %d arr[(flag+1) SZ]: %d\n", head, flag, tail, arr[(flag+1) % SZ]->dat);
        }

        arr[head % SZ] = NULL;
        head++;
        items--;
//        printf("4 head: %d flag: %d tail: %d\n", head, flag, tail);
        return res;
    }
}

void printQueue() {
    printf("[ ");
    for (int i = 0; i < SZ; ++i) {
        if (arr[i] == NULL)
            printf("[*, *] ");
        else
            printf("[%d, %d] ", arr[i]->pr, arr[i]->dat);
    }
    printf(" ]\n");
}

#define T char
#define SIZE 1000
#define true 1 == 1
#define false 1 != 1

typedef int boolean;
int cursor = -1;
T Stack[SIZE];

boolean pushStack(T data) {
    if (cursor < SIZE) {
        Stack[++cursor] = data;
        return true;
    } else {
        printf("%s \n", "Stack overflow");
        return false;
    }
}

T popStack() {
    if (cursor != -1) {
        return Stack[cursor--];
    } else {
        printf("%s \n", "Stack is empty");
        return -1;
    }
}

void PrintBin(void *vptData, unsigned long int iDataSize)
{
    for(int i = 0; i < iDataSize; i++)
        for(unsigned char ucMask = 1; ucMask != 0; ucMask <<= 1)
            if (ucMask & *((unsigned char *)vptData + i))
                pushStack('1');
            else
                pushStack('0');

    int iCnt = 0;
    while (cursor != -1)
    {
        printf("%c", popStack());
        if (++iCnt >= 32)
        {
            printf("\n");
            iCnt = 0;
        }
        else if (!(iCnt % 8))
            printf(" ");
    }
    printf("\n");
}

int main()
{
    setlocale(LC_ALL, "");

    printf("1 Очередь с приоритетным исключением\n\n");
    initQueue();
    ins_pin(1, 11);
    ins_pin(3, 22);
    ins_pin(4, 33);
    ins_pin(2, 44);
    ins_pin(3, 55);
    ins_pin(4, 66);
    ins_pin(5, 77);
    ins_pin(1, 88);
    ins_pin(2, 99);
    ins_pin(6, 100);
    printQueue();

    for (int i = 0; i < 7; ++i)
    {
        Node* n = rem_pin();
        printf("pr=%d, dat=%d \n", n->pr, n->dat);
    }
    printQueue();

    ins_pin(1, 110);
    ins_pin(3, 120);
    ins_pin(6, 130);
    printQueue();

    for (int i = 0; i < 5; ++i)
    {
        Node* n = rem_pin();
        printf("pr=%d, dat=%d \n", n->pr, n->dat);

    }
    printQueue();

    printf("\n\n2 Перевод из десятичной в двоичную систему счисления с использованием стека\n\n");
    for(int i = -3; i < 4; i++)
    {
        printf("int i = %d\n", i);
        PrintBin((void *)&i, sizeof(i));
    }

    int iarrA[7] = {-255, -1, 1, 2, 3, 255, 65535};
    printf("int iarrA[7] = {-255, -1, 1, 2, 3, 255, 65535}\n");
    PrintBin((void *)iarrA, sizeof(iarrA));


    for(float f = -2; f < 2.1; f += 0.5)
    {
        printf("float i = %4.1f\n", f);
        PrintBin((void *)&f, sizeof(f));
    }

    short shV = 11111;
    printf("short shV = 11111\n");
    PrintBin((void *)&shV, sizeof(shV));

    double dbV = 16;
    printf("\ndouble dbV = 16\n");
    PrintBin((void *)&dbV, sizeof(dbV));

    char strS[] = "abcABC123абвАБВ";
    printf("char strS[] abcABC123абвАБВ\n");
    PrintBin((void *)&strS, sizeof(strS));

    return 0;
}
