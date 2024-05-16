#include <cs50.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // check whether the program was correctly called
    if (argc != 2)
    {
        printf("Usage: recover.c card.raw\n");
        return 1;
    }

    // open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("The card cannot be opened for reading!\n");
        return 1;
    }

    // while there is still data to read from the memory card
    // iterate over a memory card by reading 512 bytes at the time
    uint8_t *buffer = malloc(512 * sizeof(uint8_t));
    if (buffer == NULL)
    {
        return 1;
    }
    
    int jpgCounter = 0;
    bool newImgStart = false;

    FILE *img = NULL;

    while (fread(buffer, 512, 1, card) != 0)
    {
        // look at the first 4 bytes and search for the JPEG's signature
        newImgStart = buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
                      // bitwise arithmetic - look at the first 4 bits of this 8-bit
                      // byte and set the remaining 4 bits to 0
                      (buffer[3] & 0xf0) == 0xe0;

        if (newImgStart)
        {
            if (img != NULL)
                fclose(img);
            char filename[8];
            // print to the string filename
            sprintf(filename, "%03i.jpg", jpgCounter);

            // open the new image file and copy the first 512 bytes
            img = fopen(filename, "w");
            fwrite(buffer, 512, 1, img);
            jpgCounter++;
        }
        else
        {
            if (jpgCounter > 0)
            {
                fwrite(buffer, 512, 1, img);
            }
        }
    }

    fclose(img);
    free(buffer);
    fclose(card);
}
