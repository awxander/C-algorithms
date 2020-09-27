#include <stdio.h>
#include <iostream>
#define bad_in {printf("bad input"); exit(1);}
void float_in_char(long long int f_sum10, int ss2, long long int den)
{
     int x,i = 0;
    char y;
    while (f_sum10%den > 0.0000000000001)
    {
        x = (f_sum10 * ss2)/den;
        f_sum10 =( f_sum10 * ss2)%den;
        if (x >= 10)
            y = x + 87;
        else
            y = x + 48;
        printf("%c", y);
        i++;
    }
}
void int_in_char(long long int sum10, int ss2)
{
    if (sum10 / ss2 != 0)
        int_in_char(sum10 / ss2, ss2);
    char y;
    int x;
    x = sum10 % ss2;
    if (x >= 10)
        y = x + 87;
    else
        y = x + 48;
    printf("%c", y);
}
const char* conv(const char *s, int b, long long int& nom, long long int& denom)
{
    denom = 1;
    int i,term = 0;
    for (i = 0; s[i] != '.' && s[i] != '\0'; i++)
    {
        
        if (s[i] >= '0' && s[i] <= '9')// 48="0" 
            term = s[i] - 48;
        else 
            if (s[i] >= 'a' && s[i] <= 'f') // 97="a" 
                term = s[i] - 87;
            else 
                if (s[i] >= 'A' && s[i] <= 'F')
                    term = s[i] - 'A' + 10;
                else  bad_in
        nom = nom * b + term;
        denom = denom * b;
    }
    return(&s[i]);
}
int main()
{
    int b1, b2;
    scanf("%i%i", &b1, &b2);
    if (b1 > 16 || b1 < 2 || b2>16 || b2 < 2)
        bad_in
    char str[14];
    if (1 != (scanf("%s", str)))
        return(1);
    int i,num_of_points=0;
    for (i = 0; str[i] != '\0'; i++)
        if (str[i] == '.')
            num_of_points++;
    if(str[0]=='.' || str[i-1]=='.' || num_of_points>1)
        bad_in
    const char* p;
    long long int whole=0, den=0,Float = 0;
       p= conv(str, b1, whole, den);
       int_in_char(whole, b2);
       if (p[0] != '\0')
       {
           p = conv(p + 1, b1, Float, den);
           if(Float>0)
           printf(".");
           float_in_char(Float, b2, den);
       }
}