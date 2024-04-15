#include <cs50.h>
#include <stdio.h>

void printBlocks(int r);
void printRow(int row);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int row = 0; row < height; row++)
    {
        for (int spaces = 0; spaces < (height - row - 1); spaces++)
        {
            printf(" ");
        }
        printRow(row);
    }
}

void printBlocks(int r)
{
    for (int i = 0; i < (r + 1); i++)
    {
        printf("#");
    }
}

void printRow(int row)
{
    printBlocks(row);
    printf("  ");
    printBlocks(row);
    printf("\n");
}
