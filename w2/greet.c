#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    // the location of the program is always in argv[0]
    //printf("The location of the program is: %s\n", argv[0]);

    if (argc == 2)
    {
        printf("hello, %s\n", argv[1]);
    }
    else
    {
        printf("hello, wolrd\n");
    }

}
