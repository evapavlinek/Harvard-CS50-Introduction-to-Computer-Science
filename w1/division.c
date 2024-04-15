#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x = get_int("x: ");
    int y = get_int("y: ");

    float z = (float) x / (float) y;
    // double is more precise (64 bits vs 32 from float)
    // floating-point imprecision
    printf("%.20f\n", z);
}
