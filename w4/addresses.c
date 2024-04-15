#include <stdio.h>

int main(void)
{
    int n = 50;

    // declaring the pointer (a variable that will hold the address)
    int *p = &n;

    // print the address
    printf("%p\n", p);
    // print what is on that address
    printf("%i\n", *p);
}
