#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <x86intrin.h>
#define N_MIN 256
#define N_MAX (32*1024*256)
#define K 10
void DirectFill(int *arr, int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        arr[i] = i + 1;
    }
    arr[n - 1] = 0;
}
void ReverseFill(int *arr, int n)
{
    for(int i = n; i > 1; i--)
    {
        arr[i] = i - 1;
    }
    arr[0] = n - 1;
}

void RandFill(int *arr, int n)
{
    for(int i = 0; i < n; i++)
    {
        int j = rand()%(i+1);
        arr[j] = arr[i];
        arr[i] = j;
    }
}

void PrintDetourTime(int *arr, int n)
{
    long long total_time[K];
    long long start;
    long long end;
    for(int i = 0; i < K; i++)
    {
        int index = 0;
        start = _rdtsc();
        for(int j = 0; j < n; j++)
        {
            index = arr[index];
        }
        end = _rdtsc();
        total_time[i] = end - start;
    }
    
}


int main()
{
    for(int i = N_MIN; i < N_MAX; i*=2)
    {
        int *arr = (int*)malloc(sizeof(int) * i);

    }

}
