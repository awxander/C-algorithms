#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define INF (0x100000000)
typedef long long int llint;

typedef struct Edge
{
    int firstV;
    int secondV;
} Edge;

int GetSecondV(llint *minEdgeFrom, int vertexN)
{
    llint minEdge = INF;
    int secondVertex = 0;
    for (int i = 0; i < vertexN; ++i)
    {
        if (minEdgeFrom[i] && minEdge > minEdgeFrom[i])
        {
            minEdge = minEdgeFrom[i];
            secondVertex = i;
        }
    }
    return secondVertex;
}

void BuildSpanningTree(Edge *minEdges, int *graph, int *firstV, llint *minEdgeFrom, int vertexN, int traversedVerticesN, int currentV)
{
    llint minEdge = INF;
    int secondVertex = 0;
    for (int i = 0; i < vertexN; i++)
    {
        llint edge = graph[vertexN * currentV + i];
        if (edge && minEdgeFrom[i] && (minEdgeFrom[i] > edge))
        {
            minEdgeFrom[i] = edge;
            firstV[i] = currentV;
            if (minEdge > edge)
            {
                minEdge = edge;
                secondVertex = i;
            }
        }
    }
    graph[vertexN * currentV + secondVertex] = 0;
    graph[vertexN * secondVertex + currentV] = 0;
    if (secondVertex)
    {
        minEdges[traversedVerticesN].firstV = firstV[secondVertex] + 1;
        minEdges[traversedVerticesN].secondV = secondVertex + 1;
        minEdgeFrom[secondVertex] = 0;
        traversedVerticesN++;
        BuildSpanningTree(minEdges, graph, firstV, minEdgeFrom, vertexN, traversedVerticesN, secondVertex);
    }
    if (traversedVerticesN != vertexN)
    {
        secondVertex = GetSecondV(minEdgeFrom, vertexN);
        if (secondVertex)
        {
            minEdges[traversedVerticesN].firstV = firstV[secondVertex] + 1;
            minEdges[traversedVerticesN].secondV = secondVertex + 1;
            minEdgeFrom[secondVertex] = 0;
            traversedVerticesN++;
            BuildSpanningTree(minEdges, graph, firstV, minEdgeFrom, vertexN, traversedVerticesN, secondVertex);
        }
    }
    return;
}

int main()
{
    int vertexN, edgesN;
    if (scanf("%i%i", &vertexN, &edgesN) != 2)
    {
        printf("bad number of lines");
        return 0;
    }
    if (vertexN == 0 && edgesN == 0)
    {
        printf("no spanning tree");
        return 0;
    }
    if (vertexN == 1 && edgesN == 0)
    {
        return 0;
    }
    if (vertexN < 0 || vertexN > 5000)
    {
        printf("bad number of vertices");
        return 0;
    }
    if (edgesN < 0 || edgesN > (((vertexN - 1) * vertexN) / 2))
    {
        printf("bad number of edges");
        return 0;
    }
    int *graph = calloc(vertexN * vertexN, sizeof(int));
    int firstVertex, secondVertex;
    int edgeLen;
    int *firstV = (int *)calloc(vertexN, sizeof(int));
    llint *minEdgeFrom = malloc(sizeof(llint) * vertexN);
    Edge *minEdges = calloc(vertexN - 1, sizeof(Edge));
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
        if (firstVertex < 1 || secondVertex < 1 || firstVertex > vertexN || secondVertex > vertexN)
        {
            printf("bad vertex");
            goto success_end;
        }
        graph[(firstVertex - 1) * vertexN + (secondVertex - 1)] = edgeLen;
        graph[(secondVertex - 1) * vertexN + (firstVertex - 1)] = edgeLen;
    }
    for (int i = 0; i < vertexN; i++)
    {
        minEdgeFrom[i] = INF;
    }
    minEdgeFrom[0] = 0;
    BuildSpanningTree(minEdges, graph, firstV, minEdgeFrom, vertexN, 0, 0);
    if (!minEdges[vertexN - 2].firstV)
    {
        printf("no spanning tree");
    }
    else
    {
        for (int i = 0; i < vertexN - 1; i++)
        {
            printf("%i %i\n", minEdges[i].firstV, minEdges[i].secondV);
        }
    }
success_end:
    free(minEdges);
    free(graph);
    free(minEdgeFrom);
    free(firstV);
    // system("pause");
    return 0;
}
