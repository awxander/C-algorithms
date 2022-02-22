#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define INF 2147483648

typedef struct Node
{
    struct Node *L;
    struct Node *R;
    int height;
    char key1;
    char key2;
} Node;

int PrintSpanningTree(int *graph, int vertexN)
{
    char *checkVertex = calloc(vertexN, sizeof(char));      //были ли мы в вершине [i]
    int *traversedVerticies = calloc(vertexN, sizeof(int)); //пройденные вершины по очереди прохождения
    checkVertex[0]++;
    traversedVerticies[0] = 1;
    int i = 0;
    while (i < vertexN)
    {
        int minEdge = INT_MAX;
        int firstVertex = -1;
        int secondVertex = -1;
        for (int j = 0; j < i + 1; j++) //ищем минимальную длину ребра, из всех ребер выходящих из пройденых вершин
        {
            for (int k = 0; k < vertexN; k++)
            {
                if (graph[vertexN * (traversedVerticies[j] - 1) + k] != 0 && graph[vertexN * (traversedVerticies[j] - 1) + k] <= minEdge && !checkVertex[k])
                {
                    minEdge = graph[vertexN * (traversedVerticies[j] - 1) + k];
                    firstVertex = traversedVerticies[j];
                    secondVertex = k + 1;
                }
            }
        }
        if (secondVertex == -1)
        {
            break;
        }
        checkVertex[secondVertex - 1]++;
        i++;
        traversedVerticies[i] = secondVertex;
        printf("%i %i\n", firstVertex, secondVertex);
    }
    return 0;
}

int main()
{

    int a = INF - 1;
    printf("%i", a);
    system("pause");

    return 0;
}