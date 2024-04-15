#include <cs50.h>
#include <stdio.h>

int collatz(int n);

int main()
{
    int n = get_int("Enter n: ");
    printf("It took %i steps to get from %i to 1.\n", collatz(n), n);
}

int collatz(int n)
{
    if (n == 1)
        return 0;
    if (n % 2 == 0)
        return 1 + collatz(n / 2);
    else
        return 1 + collatz(3 * n + 1);
}
