#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int sum(int n, ...)
{
    int result = 0;
    // получаем указатель на параметр n
    for (int *ptr = &n; n > 0; n--)
    {
        result += *(ptr++);
    }
    return result;
}
int main()
{
    printf("S.Holmes:\n");
    return 0;
}