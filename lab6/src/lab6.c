#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    struct Node *L;
    struct Node *R;
    char height;
    int key;
} Node;

char GetHeight(Node *tree)
{
    if (tree)
        return tree->height;
    else
        return 0;
}

void FixHeight(Node *tree)
{
    char heightL = GetHeight(tree->L);
    char heightR = GetHeight(tree->R);
    tree->height = (heightL > heightR ? heightL : heightR) + 1;
}

Node *RightRotation(Node *tree)
{
    Node *newNode = tree->L;
    tree->L = newNode->R;
    newNode->R = tree;
    FixHeight(tree);
    FixHeight(newNode);
    return newNode;
}

Node *LeftRotation(Node *tree)
{
    Node *newNode = tree->R;
    tree->R = newNode->L;
    newNode->L = tree;
    FixHeight(tree);
    FixHeight(newNode);
    return newNode;
}

char Disbalance(Node *tree)
{
    return GetHeight(tree->R) - GetHeight(tree->L);
}

Node *BalanceTree(Node *tree)
{
    FixHeight(tree);
    switch (Disbalance(tree))
    {
    case (2):
    {
        if (Disbalance(tree->R) < 0)
        {
            tree->R = RightRotation(tree->R);
        }
        return LeftRotation(tree);
    }
    case (-2):
    {
        if (Disbalance(tree->L) > 0)
        {
            tree->L = LeftRotation(tree->L);
        }
        return RightRotation(tree);
    }
    default:
        return tree;
    }
}

Node *AddNode(Node *tree, Node *newNode)
{
    if (!tree)
    {
        tree = newNode;
        return tree;
    }
    else
    {
        if (newNode->key < tree->key)
        {
            tree->L = AddNode(tree->L, newNode);
        }
        else
        {
            tree->R = AddNode(tree->R, newNode);
        }
        return BalanceTree(tree);
    }
}

void PrintTree(Node *tree, int n)
{
    if (tree)
    {
        PrintTree(tree->R, n + 5);
        for (int i = 0; i < n; i++)
            printf(" ");
        printf("%d\n", tree->key);
        PrintTree(tree->L, n + 5);
    }
}

Node *BuildTree(Node *treeNodes, Node *treeTop, int N, FILE *input)
{
    int key;
    if (fscanf(input, "%i", &key) == EOF)
        return 0;
    treeTop->L = NULL;
    treeTop->R = NULL;
    treeTop->key = key;
    treeTop->height = 1;
    for (int i = 1; i < N ; i++)
    {
        if (fscanf(input, "%i", &key) == EOF)
            return 0;
        treeNodes[i].L = NULL;
        treeNodes[i].R = NULL;
        treeNodes[i].key = key;
        treeNodes[i].height = 1;
        treeTop = AddNode(treeTop, &treeNodes[i]);
    }
    return treeTop;
}


int main()
{
    int N;
    FILE *input;
    input = fopen("in.txt", "r");
    if (fscanf(input, "%i", &N) == EOF)
    {
        fclose(input);
        return 1;
    }
    if (N > 0)
    {
        Node *treeNodes = malloc(sizeof(Node) * N);
        Node *treeTop = treeNodes;
        if (!(treeTop = BuildTree(treeNodes, treeTop, N, input)))
        {
            fclose(input);
            free(treeNodes);
            return 1;
        }
        printf("%i", treeTop->height);
        free(treeNodes);
    }
    else
    {
        printf("0");
    }
    // system("pause");
    fclose(input);
    return 0;
}
