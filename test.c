#include <stdio.h>
#include <stdlib.h>

void ft(int **a)
{
    int b;

    b = 5;

    // *a = malloc(sizeof(int) * 2);

    *a = &b;
    // printf("%p  a\n", &b);
}

void    ft_ft(int *a)
{
    printf("%d\n", *a);
}

// void ft_a(int *b)
// {
//     b = malloc(1);
//     *b = 4;
// }

int main()
{
    int *a;

    // printf("%p  a\n", a);

    ft(&a);

    printf("%d\n", *a);

    ft_ft(a);

    // printf("%p  a\n", a);


    // int a;

    // printf("%d\n", a);

    // ft_a(&a);

    // printf("%d\n", a);

}