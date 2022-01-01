#include <stdio.h>
#include <stdlib.h>

#define true 1 == 1
#define false 1 != 1
typedef int boolean;

//1 Реализация обхода в глубину с использованием стека
typedef struct Data
{
    int iNodeIndex;
    int iLink;
} Data;

typedef struct Node
{
    Data *ptstData;
    struct Node *next;
} Node;

typedef struct
{
    Node *head;
    int size;
} Stack;

void init(Stack *stack)
{
    stack->head = NULL;
    stack->size = 0;
}

boolean push(Stack *stack, Data *ptData)
{
    Node *tmp = (Node *)malloc(sizeof(Node));
    if (tmp == NULL)
    {
        printf("Stack overflow \n");
        return false;
    }
    tmp->ptstData = ptData;
    tmp->next = stack->head;

    stack->head = tmp;
    stack->size++;
    return true;
}

Data* pop(Stack *stack)
{
    if(stack->size == 0)
        return 0;
    Node *tmp = stack->head;
    Data *ptData = stack->head->ptstData;
    stack->head = stack->head->next;
    free(tmp);
    stack->size--;
    return ptData;
}

void depthTrStCnt(int st, int *matrix, int n, int *ptLink)
{
    int visitedDepth[n];
    for (int i = 0; i < n; i++)
        visitedDepth[i] = 0;

    Stack *ptSt = (Stack *)malloc(sizeof(Stack));
    init(ptSt);
    int iLnk = 0;
    Data *ptData;

    visitedDepth[st] = 1;
    printf("\n%d ", st);
    do
    {
        for (iLnk; iLnk < n; iLnk++)
            if (*(matrix + n*st + iLnk) > 0)
            {
                (*(ptLink+st))++;
                if(!visitedDepth[iLnk])
                {
                    //printf("1 st %d iLnk %d\n", st, iLnk);
                    Data *ptData = (Data *)malloc(sizeof(Data));
                    ptData->iNodeIndex = st;
                    ptData->iLink = iLnk+1;
                    push(ptSt, ptData);
                    st = iLnk;
                    iLnk = -1;
                    visitedDepth[st] = 1;
                    printf("%d ", st);
                    continue;
                }
            }

        ptData = pop(ptSt);
        if (ptData)
        {
            st = ptData->iNodeIndex;
            iLnk = ptData->iLink;
            //printf("2 st %d iLnk %d\n", st, iLnk);
            free(ptData);
        }
        else
            break;
    }
    while(ptData);
    free(ptSt);
}

void depthTraversOnStack(int st, int *matrix, int n)
{
    int ptLink[n];
    for (int i = 0; i < n; i++)
        ptLink[i] = 0;

    depthTrStCnt(st, matrix, n, ptLink);
}

//2 Моделируем робот поисковой системы

void OrderedPrint(int *ptLink, int n)
{
    printf("\n");
    int iMaxInd;
    for (int j = 0; j < n;j++)
    {
        iMaxInd = 0;
        for (int i = 0; i < n; i++)
            if ((ptLink[i] > ptLink[iMaxInd])&&(ptLink[i] != -1))
                iMaxInd = i;
        printf("Node: %3d Link: %2d\n", iMaxInd, ptLink[iMaxInd]);
        ptLink[iMaxInd] = -1;
    }
    printf("\n");
}

void depthTraversOnStackLink(int st, int *matrix, int n)
{
    int ptLink[n];
    int ptLinkTmp[n];
    for (int i = 0; i < n; i++)
    {
        ptLink[i] = 0;
        ptLinkTmp[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        if (!ptLink[i])
            depthTrStCnt(i, matrix, n, ptLinkTmp);
        for (int j = 0; j < n; j++)
        {
            if (ptLink[j] < ptLinkTmp[j])
                ptLink[j] = ptLinkTmp[j];
            ptLinkTmp[j] = 0;
        }
    }

    OrderedPrint(ptLink, n);
}

void depthTraversRec(int st,  int *matrix, int n, int *visitedDepth, int *ptLink)
{
    int r;
    printf("%d ", st);

    *(visitedDepth+st) = 1;
    for (r = 0; r < n; ++r)
        if (*(matrix + n*st + r) == 1)
        {
            (*(ptLink+st))++;
            if(!*(visitedDepth+r))
                depthTraversRec(r, matrix, n, visitedDepth, ptLink);
        }
}

void depthTraversRecLink(int st, int *matrix, int n)
{
    int visitedDepth[n];
    int ptLink[n];
    for (int i = 0; i < n; i++)
    {
        visitedDepth[i] = 0;
        ptLink[i] = 0;
    }

    depthTraversRec(st, matrix, n, visitedDepth, ptLink);

    OrderedPrint(ptLink, n);
}

void main()
{
    setlocale(LC_ALL, "Russian");	//system("chcp 1251");

    printf("\n1 Реализация обхода в глубину с использованием стека\n\n");

    int n = 6;
    int matrix[6][6] =
    {
        {0, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1},
        {0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0}
    };
    depthTraversOnStack(0, matrix, n);
    depthTraversOnStack(2, matrix, n);
    depthTraversOnStack(1, matrix, n);

    n = 14;
    int adj[14][14] =
    {
        {0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}
    };
    depthTraversOnStack(0, adj, n);

    printf("\n\n2 Моделируем робот поисковой системы\n\n");

    printf("Рекурсивный обход\n");
    depthTraversRecLink(0, matrix, 6);
    depthTraversRecLink(0, adj, n);

    printf("Обход по матрице смежности\n");
    depthTraversOnStackLink(0, matrix, 6);
    depthTraversOnStackLink(0, adj, n);
}
