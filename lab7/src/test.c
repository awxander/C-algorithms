#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node *L;
    struct Node *R;
    int height;
    char key1;
    char key2;
} Node;

int main()
{
    printf("%i\n",sizeof(Node));
    system("pause");
    return 0;
}