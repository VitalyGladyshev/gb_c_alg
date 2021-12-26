#include <stdio.h>
#include <locale.h>

#define T char
#define true 1 == 1
#define false 1 != 1
typedef int boolean;

//1 Определение правильности порядка скобок
typedef struct Node
{
    T dat;
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

boolean push(Stack *stack, T value)
{
    Node *tmp = (Node *)malloc(sizeof(Node));
    if (tmp == NULL)
    {
        printf("Stack overflow \n");
        return false;
    }
    tmp->dat = value;
    tmp->next = stack->head;

    stack->head = tmp;
    stack->size++;
    return true;
}

T pop(Stack *stack)
{
    if(stack->size == 0)
    {
        printf("Stack is empty \n");
        return -1;
    }
    Node *tmp = stack->head;
    T data = stack->head->dat;
    stack->head = stack->head->next;
    free(tmp);
    stack->size--;
    return data;
}

boolean BracketsTest(char *ptcStr)
{
    Stack *st = (Stack*)malloc(sizeof(Stack));
    init(st);
    boolean bErr = false;

    for(int i = 0; ptcStr[i] != 0; i++)
    {
        if ((ptcStr[i] == '(')||(ptcStr[i] == '[')||(ptcStr[i] == '{'))
            push(st, ptcStr[i]);
        char cBr;
        if ((ptcStr[i] == ')')||(ptcStr[i] == ']')||(ptcStr[i] == '}'))
        {
            if (!st->size)
            {
                printf("Закрывающая скобка без открывающей в позиции %d\n", i+1);
                bErr = true;
                break;
            }
            cBr = pop(st);
            if ((ptcStr[i] == ')')&&(cBr != '('))
            {
                printf("Некорректно поставлена скобка: ) в позиции %d. Не соответствует скобке: %c\n", i+1, cBr);
                bErr = true;
                break;
            }
            if ((ptcStr[i] == ']')&&(cBr != '['))
            {
                printf("Некорректно поставлена скобка: ] в позиции %d. Не соответствует скобке: %c\n", i+1, cBr);
                bErr = true;
                break;
            }
            if ((ptcStr[i] == '}')&&(cBr != '{'))
            {
                printf("Некорректно поставлена скобка: } в позиции %d. Не соответствует скобке: %c\n", i+1, cBr);
                bErr = true;
                break;
            }
        }
    }
    if (st->size)
    {
        if (!bErr)
        {
            printf("Остались незакрытые скобки\n");
            bErr = true;
        }
        while(st->size)
            pop(st);
    }
    free(st);
    if (bErr)
        return false;
    else
        return true;
}

//2 копирование односвязного списка
typedef struct OneLinkNode
{
    int dat;
    struct OneLinkNode *next;
} OneLinkNode;

typedef struct
{
    OneLinkNode *head;
    int size;
} OneLinkList;

void initOneLinkList(OneLinkList *oList)
{
    oList->head = NULL;
    oList->size = 0;
}

void insert(OneLinkList *lst, int data)
{
    OneLinkNode *new = (OneLinkNode*) malloc(sizeof(OneLinkNode));
    new->dat = data;
    new->next = NULL;

    OneLinkNode *current = lst->head;
    if (current == NULL)
    {
        lst->head = new;
        lst->size++;
    }
    else
    {
        while (current->next != NULL)
            current = current->next;
        current->next = new;
        lst->size++;
    }
}

OneLinkNode* rm(OneLinkList *lst, int data)
{
    OneLinkNode *current = lst->head;
    OneLinkNode *parent = NULL;
    if (current == NULL)
        return NULL;

    while (current->next != NULL && current->dat != data)
    {
        parent = current;
        current = current->next;
    }
    if (current->dat != data)
        return NULL;
    if (current == lst->head)
    {
        lst->head = current->next;
        lst->size--;
        return current;
    }
    parent->next = current->next;
    lst->size--;
    return current;
}

void printOneLinkIntNode(OneLinkNode *n)
{
    if (n == NULL)
    {
        printf("[]");
        return;
    }
    printf("[%d]", n->dat);
}

void printOneLinkIntList(OneLinkList *oList)
{
    OneLinkNode *current = oList->head;
    if (current == NULL)
        printOneLinkIntNode(current);
    else
    {
        do
        {
            printOneLinkIntNode(current);
            current = current->next;
        } while(current != NULL);
    }
    printf(" Size: %d \n", oList->size);
}

boolean copyOneLinkIntList(OneLinkList *oList_s, OneLinkList *oList_d)
{
    if (oList_s->head != NULL)
    {
        OneLinkNode *current = oList_s->head;
        do
        {
            insert(oList_d, current->dat);
            current = current->next;
        }
        while (current != NULL);
    }
    return true;
}

void ridOneLinkIntList(OneLinkList *oList)
{
    OneLinkNode *current;
    while(oList->size)
    {
        current = rm(oList, oList->head->dat);
        free(current);
    }
    //printOneLinkIntList(oList);
    free(oList);
    return;
}

//3 Проверка наличия сортировки в связанном списке
boolean testSortOneLinkIntList(OneLinkList *oList)
{
    if (oList->size == 0)
    {
        printf("Список пуст\n");
        return false;
    }
    else if (oList->size == 1)
    {
        printf("Список единичной длины всегда отсортирован\n");
        return true;
    }
    else
    {
        int iDlt = 0, tmp;
        OneLinkNode *current = oList->head;
        do
        {
            tmp = 0;
            //printf("current->dat: %d current->next->dat: %d\n", current->dat, current->next->dat);
            if (current->dat < current->next->dat)
                tmp = 1;
            if (current->dat > current->next->dat)
                tmp = -1;
            if (tmp)
            {
                if ((iDlt)&&(iDlt != tmp))
                    return false;
                iDlt = tmp;
            }
            current = current->next;
        }
        while(current->next != NULL);
        if (iDlt > 0)
            printf("Список отсортирован по возрастанию\n");
        else if (iDlt < 0)
            printf("Список отсортирован по убыванию\n");
        else
            printf("Элементы списка равны друг-другу\n");
        return true;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");	//system("chcp 1251");

    printf("1 Определение правильности порядка скобок\n\n");
    char ptcStr[255] = "";
    printf("Введите строку со скобками: ");
    gets(ptcStr);
    if (BracketsTest(ptcStr))
        printf("Нет ошибок расстановки скобок\n\n");
    else
        printf("Нарушена логика расстановки скобок\n\n");

    printf("2 Функция копирования односвязного списка\n\n");
    OneLinkList *lst = (OneLinkList*) malloc(sizeof(OneLinkList));
    initOneLinkList(lst);
    for (int i = 3; i <= 30; i+=3)
        insert(lst, i);
    printf("Исходный односвязный список\nlst:");
    printOneLinkIntList(lst);

    OneLinkList *lst_cp = (OneLinkList*) malloc(sizeof(OneLinkList));
    initOneLinkList(lst_cp);
    if (copyOneLinkIntList(lst, lst_cp))
    {
        printf("Копирование выполнено\nlst_cp:");
        printOneLinkIntList(lst_cp);
    }
    else
        printf("Ошибка копирования\n");
    ridOneLinkIntList(lst_cp);

    printf("\n3 Проверка наличия сортировки в связанном списке\n\n");
    printf("Список\n");
    printOneLinkIntList(lst);
    if (testSortOneLinkIntList(lst))
        printf("Список отсортирован\n");
    else
        printf("Список не отсортирован\n");

    OneLinkList *lst_dw = (OneLinkList*) malloc(sizeof(OneLinkList));
    initOneLinkList(lst_dw);
    for (int i = 30; i >= 3; i-=3)
        insert(lst_dw, i);
    printf("\nСписок\n");
    printOneLinkIntList(lst_dw);
    if (testSortOneLinkIntList(lst_dw))
        printf("Список отсортирован\n");
    else
        printf("Список не отсортирован\n");

    OneLinkList *lst_rn = (OneLinkList*) malloc(sizeof(OneLinkList));
    initOneLinkList(lst_rn);
    insert(lst_rn, 5);
    insert(lst_rn, 5);
    insert(lst_rn, 5);
    insert(lst_rn, 7);
    insert(lst_rn, 3);
    insert(lst_rn, 3);
    insert(lst_rn, 3);
    insert(lst_rn, 6);
    insert(lst_rn, 10);
    insert(lst_rn, 1);
    printf("\nСписок\n");
    printOneLinkIntList(lst_rn);
    if (testSortOneLinkIntList(lst_rn))
        printf("Список отсортирован\n");
    else
        printf("Список не отсортирован\n");

    ridOneLinkIntList(lst);
    ridOneLinkIntList(lst_dw);
    ridOneLinkIntList(lst_rn);
    return 0;
}

// Использовалось для отладки

//    push(st, 'a');
//    push(st, 'b');
//    push(st, 'c');
//    push(st, 'd');
//    push(st, 'e');
//    printOneLinkCharStack(st);
//    printf("%c \n", pop(st));
//    printOneLinkCharStack(st);

//    insert(lst, 10);
//    printOneLinkIntList(lst);
//    printOneLinkIntNode(rm(lst, 1)); printf("<- removed node\n");
//    printOneLinkIntList(lst);
//    printOneLinkIntNode(rm(lst, 2)); printf("<- removed node\n");
//    printOneLinkIntList(lst);

void printOneLinkCharNode(Node *n)
{
    if (n == NULL)
    {
        printf("[]");
        return;
    }
    printf("[%c]", n->dat);
}

void printOneLinkCharStack(Stack *stack)
{
    Node *current = stack->head;
    if (current == NULL)
        printOneLinkCharNode(current);
    else
    {
        do
        {
            printOneLinkCharNode(current);
            current = current->next;
        } while(current != NULL);
    }
    printf(" Size: %d \n", stack->size);
}
