#include <cs50.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./pdf filename.ext\n");
        return 1;
    }

    string filename = argv[1];
    FILE *f = fopen(filename, "r");
    // 1 byte long int
    uint8_t buffer[4];

    // fread returns the number of read blocks
    fread(buffer, 1, 4, f);

    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", buffer[i]);
    }
    fclose(f);
}
