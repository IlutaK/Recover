#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define BLOCK_SIZE 512
typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }
    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open card.raw.\n");
        return 1;
    }
    // create a buffer for a block of data
    BYTE buffer[BLOCK_SIZE];
    // pointer to opened JPEG file
    FILE *img = NULL;
    // array to store filename
    char filename[8];
    // counter for the JPEG files found
    int file_count = 0;

    // While there's still data left to read from the memory card
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        // Create JPEGs from the data
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (img != NULL)
            {

                fclose(img);
            }
            // write blocks to a new file
            sprintf(filename, "%03i.jpg", file_count);
            file_count++;
            img = fopen(filename, "w");
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
            if (img == NULL)
            {

                fclose(card);
                return 2;
            }
        }
        else if (img != NULL)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
        }
    }
    // close remaining files
    if (img != NULL)
    {
        fclose(img);
    }
    fclose(card);
    return 0;
}
