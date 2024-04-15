#include <cs50.h>
#include <stdio.h>

int fact(int n);

int main()
{
    int n = get_int("Get the factorial of number: ");
    printf("%i\n", fact(n));
}

int fact(int n)
{
    if (n == 1)
        return 1;
    else
        return n * fact(n - 1);
}
