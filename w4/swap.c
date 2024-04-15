#include <stdio.h>

void swap(int *a, int *b);

int main(void)
{
    int x = 1;
    int y = 2;

    printf("x is %i, y is %i\n", x, y);
    swap(&x, &y);
    printf("x is %i, y is %i\n", x, y);
}

void swap(int *a, int *b)
{
    // passing by reference
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

//void swap(int a, int b)
//{
//    // passing by value - this wil only swap the values inside of
//    // the scope of swap function (x and y from the main won't swap)
//    int tmp = a;
//    a = b;
//    b = tmp;
//}
