#include <stdio.h>
#include <stdlib.h>
#define CYCLE_FOUND 1
#define FALSE 0
#define TRUE 1
int FillStack(char *graph, int *stack, char *checkVertex, char *checkStack, int *stackTop, int vertexN, int currentV)
{
    checkVertex[currentV - 1]++;
    if (checkVertex[currentV - 1] == 2)
    {
        return CYCLE_FOUND;
    }
    for (int i = 0; i < vertexN; i++)
    {
        if (graph[(currentV - 1) * vertexN + i] && !checkStack[i])
        {
            if (currentV - 1 == i)
                return CYCLE_FOUND;
            if (FillStack(graph, stack, checkVertex, checkStack, stackTop, vertexN, i + 1))
                return CYCLE_FOUND;
        }
    }
    stack[*stackTop] = currentV;
    checkStack[currentV - 1]++;
    *stackTop += 1;
    return 0;
}

int *TopoSort(char *graph, int vertexN)
{
    int *stack = calloc(vertexN, sizeof(int));
    char *checkVertex = calloc(vertexN, sizeof(char));
    char *checkStack = calloc(vertexN, sizeof(char));
    int stackTop = 0;
    for (int i = 0; i < vertexN; i++)
    {
        if (checkStack[i] == 0)
        {
            if (FillStack(graph, stack, checkVertex, checkStack, &stackTop, vertexN, i + 1))
            {
                free(stack);
                free(checkVertex);
                free(checkStack);
                return NULL;
            }
        }
    }
    if (stackTop != vertexN)
    {
        free(stack);
        free(checkVertex);
        free(checkStack);
        return NULL;
    }
    free(checkVertex);
    free(checkStack);
    return stack;
}

void Print(int *stack, int N)
{
    for (int i = N - 1; i >= 0; i--)
    {
        printf("%i\n", stack[i]);
    }
}

int main()
{
    int vertexN, edgesN;
    if (scanf("%i%i", &vertexN, &edgesN) != 2)
    {
        printf("bad number of lines");
        return 0;
    }
    if (vertexN < 0 || vertexN > 2000)
    {
        printf("bad number of vertices");
        return 0;
    }
    if (edgesN < 0 || edgesN > (((vertexN - 1) * vertexN) / 2))
    {
        printf("bad number of edges");
        return 0;
    }
    char *graph = calloc(vertexN * vertexN, sizeof(char));
    int firstVertex, secondVertex;
    for (int i = 0; i < edgesN; i++)
    {
        if (scanf("%i%i", &firstVertex, &secondVertex) != 2)
        {
            printf("bad number of lines");
            goto success_end;
        }
        if (firstVertex < 1 || secondVertex < 1 || firstVertex > vertexN || secondVertex > vertexN)
        {
            printf("bad vertex");
            goto success_end;
        }
        graph[(firstVertex - 1) * vertexN + (secondVertex - 1)]++;
    }
    int *stack = TopoSort(graph, vertexN);
    if (!stack)
    {
        printf("impossible to sort");
    }
    else
    {
        Print(stack, vertexN);
        free(stack);
    }
success_end:
    free(graph);
    // system("pause");
    return 0;
}
