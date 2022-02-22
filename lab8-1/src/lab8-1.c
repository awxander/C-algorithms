#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define TRUE 1

typedef struct Edge
{
    short firstV;
    short secondV;
    int len;
} Edge;

int cmp(const void *a_, const void *b_)
{
    const Edge *a = a_;
    const Edge *b = b_;
    return a->len > b->len;
}

int FindParrent(int *parrent, int v)
{
    if (v != parrent[v - 1])
    {
        return FindParrent(parrent, parrent[v - 1]);
    }
    return v;
}
int MergeComponents(int *parrent, int a, int b)
{
    a = FindParrent(parrent, a);
    b = FindParrent(parrent, b);
    if (a != b)
    {
        parrent[a - 1] = b;
        return 0;
    }
    else
        return 1;
}
int PrintSpanningTree(Edge *edgesArr, int verticesN, int edgesN)
{
    qsort(edgesArr, edgesN, sizeof(Edge), cmp);
    int *parrent = malloc(verticesN * sizeof(int));
    for (int i = 0; i < verticesN; i++)
    {
        parrent[i] = i + 1;
    }
    int traversedEdges = 0;
    int i = 0;
    while (traversedEdges != verticesN - 1)
    {
        if(!MergeComponents(parrent, edgesArr[i].firstV, edgesArr[i].secondV))
        {
            printf("%i %i\n",edgesArr[i].firstV, edgesArr[i].secondV);
            traversedEdges++;
        }
        i++;
    }
    free(parrent);
    return 0;
}

int main()
{
    int verticesN, edgesN;
    if (scanf("%i%i", &verticesN, &edgesN) != 2)
    {
        printf("bad number of lines");
        return 0;
    }
    if (verticesN == 0 && edgesN == 0)
    {
        printf("no spanning tree");
        return 0;
    }
    if (verticesN == 1 && edgesN == 0)
    {
        return 0;
    }
    if (verticesN < 0 || verticesN > 5000)
    {
        printf("bad number of vertices");
        return 0;
    }
    if (edgesN < 0 || edgesN > (((verticesN - 1) * verticesN) / 2))
    {
        printf("bad number of edges");
        return 0;
    }
    Edge *edgesArr = calloc(edgesN, sizeof(Edge));
    int firstVertex, secondVertex;
    int edgeLen;
    int *incidentEdges = calloc(verticesN, sizeof(int));
    for (int i = 0; i < edgesN; i++)
    {
        if (scanf("%i%i%i", &firstVertex, &secondVertex, &edgeLen) != 3)
        {
            printf("bad number of lines");
            goto success_end;
        }
        if (edgeLen < 0)
        {
            printf("bad length");
            goto success_end;
        }
        if (firstVertex < 1 || secondVertex < 1 || firstVertex > verticesN || secondVertex > verticesN)
        {
            printf("bad vertex");
            goto success_end;
        }
        incidentEdges[firstVertex - 1]++;
        incidentEdges[secondVertex - 1]++;
        edgesArr[i].firstV = firstVertex;
        edgesArr[i].secondV = secondVertex;
        edgesArr[i].len = edgeLen;
    }
    for (int i = 0; i < verticesN; i++)
    {
        if (!incidentEdges[i])
        {
            printf("no spanning tree");
            goto success_end;
        }
    }
    PrintSpanningTree(edgesArr, verticesN, edgesN);
success_end:
    free(edgesArr);
    free(incidentEdges);
    // system("pause");
    return 0;
}
