#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int FAT_BLOCK = 512;

int isjpeg(uint8_t block[FAT_BLOCK]);

int main(int argc, char *argv[])
{
    // Check if the user provided one command-line argument
    if (argc != 2)
    {
        printf("Usage: %s \"forensic image\"\n", argv[0]);
    }
    // Open file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    int jpeg_count = 0;
    char jpeg_name[8];
    sprintf(jpeg_name, "%03i.jpg", jpeg_count);

    FILE *jpeg_file = fopen(jpeg_name, "w");

    uint8_t buffer[FAT_BLOCK];
    // Write to a JPEG file in 512B chuncks until a new JPEG is found
    while (fread(buffer, 1, FAT_BLOCK, file) > 0)
    {
        if (isjpeg(buffer))
        {
            if (jpeg_count == 0)
            {
                jpeg_count++;
            }
            else
            {
                fclose(jpeg_file);
                sprintf(jpeg_name, "%03i.jpg", jpeg_count);
                jpeg_file = fopen(jpeg_name, "w");
                jpeg_count++;
            }
        }
        if (jpeg_count > 0)
            fwrite(buffer, 1, sizeof(buffer), jpeg_file);
    }
    printf("%i\n", jpeg_count);
    fclose(jpeg_file);
    fclose(file);
    return 0;
}

// Function that checks the first four bytes in a block.
// Returns non-zero if it is a JPEG, or 0 otherwise.
int isjpeg(uint8_t block[FAT_BLOCK])
{
    uint8_t jpeg_sig[] = {0xff, 0xd8, 0xff, 0xe0};
    // Look for the first four bytes of a JPEG
    for (int i = 0; i < 4; i++)
    {
        if (i == 3 && (block[i] & 0xf0) != jpeg_sig[i])
            return 0;
        else if (block[i] != jpeg_sig[i])
            return 0;
    }
    // If pass, is JPEG signature
    return 1;
}
