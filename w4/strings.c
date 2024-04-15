#include <stdio.h>

int main(void)
{
    // strings are actually pointers (string s = char *s)
    // typedef char *string;
    // string s = "HI!";
    char *s = "HI!";
    // Pointer Arithmetic
    printf("%c", *s);
    printf("%c", *(s + 1));
    printf("%c\n", *(s + 2));
}
