#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node *L, *R;
    int amount;
    char symb;
} Node;

typedef struct Table
{
    int len;
    int code;
} Table;

typedef unsigned char uchar;
int cmp(const void *a_, const void *b_)
{
    const Node *a = a_;
    const Node *b = b_;
    return a->amount > b->amount;
}

Node *BuildTree(Node *newStart, int N) // N - количество рэлементов в массиве
{
    while (N > 1)
    {
        newStart[N].amount = newStart[0].amount + newStart[1].amount;
        newStart[N].L = &newStart[0];
        newStart[N].R = &newStart[1];
        newStart = newStart + 2;
        N--;
        qsort(newStart, N, sizeof(Node), cmp);
    }
    return newStart;
}

void print(int deep, Node *p)
{
    if (p)
    {
        print(deep + 1, p->L);
        for (int i = 0; i < deep; i++)
            printf("   ");
        printf(">%c", p->symb);
        printf("\n");
        print(deep + 1, p->R);
    }
}

void FillCodingTable(Table *codingTable, Node *hafTree, int code, int codeLen)
{
    if (!hafTree->R && !hafTree->L)
    {
        codingTable[(uchar)hafTree->symb].len = codeLen;
        codingTable[(uchar)hafTree->symb].code = code;
        return;
    }
    if (hafTree->L)
    {
        FillCodingTable(codingTable, hafTree->L, (code << 1), codeLen + 1);
    }
    if (hafTree->R)
    {
        FillCodingTable(codingTable, hafTree->R, (code << 1) + 1, codeLen + 1);
    }
    return;
}
Node *GetCodingTable(FILE *input)
{
    Node *countSymbs = calloc(512, sizeof(Node));
    int curr_symb = 0;
    while ((curr_symb = getc(input)) != EOF)
    {
        countSymbs[curr_symb].amount++;
        countSymbs[curr_symb].symb = curr_symb;
    }
    qsort(countSymbs, 256, sizeof(Node), cmp);
    int i = 0;
    while (!countSymbs[i].amount)
        i++;
    if (i == 256)
        return NULL;
    Node *newStart = countSymbs + i;
    Node *hafTree;
    hafTree = BuildTree(newStart, 256 - i);
    print(0, hafTree);
    Table *codingTable = calloc(256, sizeof(Table));
    FillCodingTable(codingTable, hafTree, 0, 0);
    return NULL;
}
int main()
{
    FILE *input;
    input = fopen("C:\\Users\\Alexander\\template\\lab5\\src\\input.txt", "r");
    GetCodingTable(input);
    system("pause");
    fclose(input);
    return 0;
}