#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <limits.h>

#define true 1 == 1
#define false 1 != 1
typedef int boolean;

typedef struct Node
{
    struct Node *ptLeft;
    struct Node *ptRight;
    int iData;
}Node;

//1 Функция проверяющая является ли переданное в неё бинарное дерево сбалансированным
Node* build_random_tree(int iSize)
{
    Node *NewNode = NULL;
    if (iSize)
    {
        NewNode = (Node *)malloc(sizeof(Node));
        int iP = iSize/2;
        //printf("data: %d, middle: %d, size: %d\n", *(iArr + iP), iP, iSize);
        NewNode->iData = rand()%50;
        if (iP)
            NewNode->ptLeft = build_random_tree(iP);
        else
            NewNode->ptLeft = NULL;
        if (iSize-iP-1)
            NewNode->ptRight = build_random_tree(iSize-iP-1);
        else
            NewNode->ptRight = NULL;
    }
    return NewNode;
}

int printTreeNodeCount(Node *root, int iCount)
{
    if(root)
    {
        iCount++;
        if(root->ptLeft || root->ptRight)
        {
            if (root->ptLeft)
                iCount = printTreeNodeCount(root->ptLeft, iCount);
            if (root->ptRight)
                iCount = printTreeNodeCount(root->ptRight, iCount);
        }
    }
    return iCount;
}

typedef struct LevelMinMax
{
    int iMaxLevel;
    int iMinLevel;
}LevelMinMax;

boolean treeTestBalance(Node *root)
{
    if (root == NULL)
        return false;

    int iLevelCounter = 1;
    LevelMinMax strLevelMinMax;
    strLevelMinMax.iMaxLevel = 0;
    strLevelMinMax.iMinLevel = INT_MAX;

    if(root)
    {
        if(root->ptLeft || root->ptRight)
        {
            if (root->ptLeft)
                testBalance(root, &strLevelMinMax, iLevelCounter);
            if (root->ptRight)
                testBalance(root, &strLevelMinMax, iLevelCounter);
        }
        else
        {
            printf("Разница уровней: 0\n");
            return true;
        }
    }

    printf("iMaxLevel: %d iMinLevel: %d Разница уровней: %d\n", strLevelMinMax.iMaxLevel, strLevelMinMax.iMinLevel, strLevelMinMax.iMaxLevel - strLevelMinMax.iMinLevel);
    if (strLevelMinMax.iMaxLevel - strLevelMinMax.iMinLevel <= 1)
        return true;
    else
        return false;
}

testBalance(Node *root, LevelMinMax *ptLevelMinMax, int iLevelCounter)
{
    iLevelCounter++;
    if((root->ptLeft == NULL) && (root->ptRight == NULL))
    {
        if(ptLevelMinMax->iMaxLevel < iLevelCounter)
            ptLevelMinMax->iMaxLevel = iLevelCounter;
        if(ptLevelMinMax->iMinLevel > iLevelCounter)
            ptLevelMinMax->iMinLevel = iLevelCounter;
    }
    if (root->ptLeft)
        testBalance(root->ptLeft, ptLevelMinMax, iLevelCounter);
    if (root->ptRight)
        testBalance(root->ptRight, ptLevelMinMax, iLevelCounter);
}

Node* getSuccessor(Node *node)
{
    Node *current = node->ptRight;
    Node *parent = node;
    Node *s = node;

    while(current != NULL)
    {
        parent = s;
        s = current;
        current = current->ptLeft;
    }
    if (s != node->ptRight)
    {
        parent->ptLeft = s->ptRight;
        s->ptRight = node->ptRight;
    }
    return s;
}

boolean deleteTreeNode(Node *root, int key)
{
    Node *current = root;
    Node *parent = root;
    boolean isLeftChild = true;

    while(current->iData != key)
    {
        parent = current;
        if(key < current->iData)
        {
            current = current->ptLeft;
            isLeftChild = true;
        }
        else
        {
            current = current->ptRight;
            isLeftChild = false;
        }
        if(current == NULL)
            return false;
    }

    if(current->ptLeft == NULL && current->ptRight == NULL)
    {
        if(current == root)
            root = NULL;
        else if(isLeftChild)
            parent->ptLeft = NULL;
        else
            parent->ptRight = NULL;
    }
    else if(current->ptRight == NULL)
    {
        if(isLeftChild)
            parent->ptLeft = current->ptLeft;
        else
            parent->ptRight = current->ptLeft;
    }
    else if(current->ptLeft == NULL)
    {
        if(isLeftChild)
            parent->ptLeft = current->ptRight;
        else
            parent->ptRight = current->ptRight;
    }
    else
    {
        Node *successor = getSuccessor(current);
        if(current == root)
            root = successor;
        else if(isLeftChild)
            parent->ptLeft = successor;
        else
            parent->ptRight = successor;
        successor->ptLeft = current->ptLeft;
    }
    return true;
}

//2 Рекурсивная функция бинарного поиска в дереве хранящемся в узлах, а не в массиве
int qsort_compare(int *iA, int *iB)
{
    return *iA-*iB;
}

Node* build_tree(int *iArr, int iSize)
{
    Node *NewNode = NULL;
    if (iSize)
    {
        NewNode = (Node *)malloc(sizeof(Node));
        int iP = iSize/2;
        //printf("data: %d, middle: %d, size: %d\n", *(iArr + iP), iP, iSize);
        NewNode->iData = *(iArr + iP);
        if (iP)
            NewNode->ptLeft = build_tree(iArr, iP);
        else
            NewNode->ptLeft = NULL;
        if (iSize-iP-1)
            NewNode->ptRight = build_tree(iArr + iP + 1, iSize-iP-1);
        else
            NewNode->ptRight = NULL;
    }
    return NewNode;
}

void printTree(Node *root)
{
    if(root)
    {
        printf("%d", root->iData);
        if(root->ptLeft || root->ptRight)
        {
            printf("(");
            if (root->ptLeft)
                printTree(root->ptLeft);
            else
                printf("NULL");
            printf(", ");
            if (root->ptRight)
                printTree(root->ptRight);
            else
                printf("NULL");
            printf(")");
        }
    }
}

boolean tree_search(Node *ptRoot, int iNumber)
{
    if (ptRoot == NULL)
        return false;

    Node *ptCurrent = ptRoot;
    while(ptCurrent != NULL)
    {
        if (ptCurrent->iData == iNumber)
            return true;
        else if (iNumber < ptCurrent->iData)
            ptCurrent = ptCurrent->ptLeft;
        else
            ptCurrent = ptCurrent->ptRight;
    }
    return false;
}

free_tree_memory(Node *ptNode)
{
    if (ptNode != NULL)
    {
        free_tree_memory(ptNode->ptRight);
        free_tree_memory(ptNode->ptLeft);
        //printf("Удаляем узел: %d\n", ptNode->iData);
        free(ptNode);
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");	//system("chcp 1251");

    printf("1 Функция проверяющая является ли переданное в неё бинарное дерево сбалансированным\n\n");
    Node *RandomTree;
    for(int i = 0; i < 50; i++)
    {
        RandomTree = build_random_tree(10000);
        for(int j = 0; j < 50; j++)
            deleteTreeNode(RandomTree, rand()%50);
        printf("Дерево %d. Количество узлов: %d\n", i+1, printTreeNodeCount(RandomTree, 0));
        if (treeTestBalance(RandomTree))
            printf("Дерево сбалансированное\n\n");
        else
            printf("Дерево несбалансированное\n\n");
        free_tree_memory(RandomTree);
    }

    printf("\n2 Рекурсивная функция бинарного поиска в дереве хранящемся в узлах, а не в массиве\n\n");
    printf("Введите размер дерева: ");
    int iSize;
    scanf("%d", &iSize);
    if (iSize <= 0)
    {
        printf("Некорректный размер\n");
        return 0;
    }
    srand(time(NULL));
    int iTmp[iSize];
    for(int i = 0; i < iSize; i++)
    {
        iTmp[i] = rand()%(150-50)+50;
        printf("%d ", iTmp[i]);
    }
    qsort(iTmp, iSize, sizeof(int), qsort_compare);
    printf("\n\n");
    for(int i = 0; i < iSize; i++)
        printf("%d ", iTmp[i]);
    printf("\n\n");
    Node *RootNode;
    RootNode = build_tree(iTmp, iSize);
    printTree(RootNode);
    printf("\nВведите число для поиска: ");
    int iNumber;
    scanf("%d", &iNumber);
    if (tree_search(RootNode, iNumber))
        printf("Число найдено :)\n");
    else
        printf("Число не найдено :(\n");
    free_tree_memory(RootNode);
    return 0;
}
