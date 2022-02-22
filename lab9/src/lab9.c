#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#define INF UINT_MAX
#define TRUE 1
typedef unsigned int uint;


uint *GetInitialDistances(int *parent, int initialV, int verticesN)
{
    uint *distance = malloc(sizeof(int) * verticesN);
    for (int i = 0; i < verticesN; i++)
    {
        parent[i] = -1;
        distance[i] = INF;
    }
    distance[initialV - 1] = 0;
    return distance;
}

int DistanceCmp(uint *distance, uint *overflow, uint node1, uint node2, uint nodeAddition)
{
    if (overflow[node1] < overflow[node2])
        return -1;
    else if (overflow[node1] > overflow[node2])
        return 1;

    if (distance[node1] + nodeAddition < distance[node2])
        return -1;
    else if (distance[node1] + nodeAddition > distance[node2])
        return 1;

    return 0; // равны
}

void PrintMinDistances(uint *distances, uint *overflow, int verticesN)
{

    for (int i = 0; i < verticesN; ++i)
    {
        if (distances[i] == INF)
            printf("oo ");
        else if (overflow[i])
            printf("INT_MAX+ ");
        else
            printf("%u ", distances[i]);
    }
    printf("\n");
}

void GetMinDistances(uint *graph, uint *distance, int *parent, uint *overflow, int verticesN)
{
    char *used = calloc(verticesN, sizeof(char));
    for (int i = 0; i < verticesN; ++i)
    {
        int v = -1;
        for (int j = 0; j < verticesN; ++j)
            if (!used[j] && (v == -1 || distance[j] < distance[v]))
                v = j;

        if (distance[v] == INF)
            break;

        used[v] = TRUE;
        for (int j = 0; j < verticesN; ++j)
        {
            if (graph[v * verticesN + j] == INF)
                continue; // нет ребра

            int to = j;
            int len = graph[v * verticesN + to];

            if (DistanceCmp(distance, overflow, v, to, len) == -1)
            {
                distance[to] = distance[v] + len;
                overflow[to] = overflow[v];

                while (distance[to] > INT_MAX)
                {
                    overflow[to]++;
                    distance[to] -= INT_MAX;
                }

                parent[to] = v;
            }
        }
    }
    free(used);
}

void PrintMinPath(int *parent, uint *overflow, char overflowCount, int initialV, int finalV)
{
    if (initialV == finalV)
    {
        printf("%d\n", initialV);
    }
    else if (parent[finalV - 1] == -1)
    {
        printf("no path\n");
    }
    else if (overflow[finalV - 1] && overflowCount >= 2)
    {
        printf("overflow\n");
    }
    else
    {
        for (int pathNode = finalV - 1; pathNode != initialV - 1; pathNode = parent[pathNode])
            printf("%d ", pathNode + 1);
        printf("%d\n", initialV);
    }
}

void PrintMinDistancesAndMinPath(uint *graph, int initialV, int finalV, int verticesN)
{
    uint *overflow = calloc(verticesN, sizeof(uint));
    int *parent = calloc(verticesN, sizeof(int));
    uint *distance;
    distance = GetInitialDistances(parent, initialV, verticesN);

    GetMinDistances(graph, distance, parent, overflow, verticesN);

    PrintMinDistances(distance, overflow, verticesN);
    char overflowCount = 0;
    if (overflow[finalV - 1])
    {
        for (int i = 0; i < verticesN; ++i)
        {
            if (graph[(finalV - 1) * verticesN + i] != INF && distance[i] + graph[(finalV - 1) * verticesN + i] > INT_MAX)
                overflowCount++;

            if (overflowCount >= 2)
                break;
        }
    }
    PrintMinPath(parent, overflow, overflowCount, initialV, finalV);
    free(distance);
    free(parent);
    free(overflow);
}

int main()
{
    int verticesN, edgesN, initialV, finalV;
    if (scanf("%i%i%i%i", &verticesN, &initialV, &finalV, &edgesN) != 4)
    {
        printf("bad number of lines");
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
    if (initialV < 1 || initialV > 5000 || finalV < 1 || finalV > 5000)
    {
        printf("bad vertex");
        return 0;
    }
    int firstVertex, secondVertex, edgeLen;
    uint *graph = calloc(verticesN * verticesN, sizeof(uint));
    for (int i = 0; i < verticesN; i++)
        for (int j = 0; j < verticesN; j++)
        {
            graph[i * verticesN + j] = INF;
        }

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

        graph[(firstVertex - 1) * verticesN + (secondVertex - 1)] = edgeLen;
        graph[(secondVertex - 1) * verticesN + (firstVertex - 1)] = edgeLen;
    }
    PrintMinDistancesAndMinPath(graph, initialV, finalV, verticesN);
success_end:
    free(graph);
    // system("pause");
    return 0;
}
