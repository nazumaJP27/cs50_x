#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get a number greater than 0 and less than 9
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int line = 0; line < height; line++)
    {
        for (int space = 0; space < height - line - 1; space++)
        {
            printf(" ");
        }
        for (int lHash = 0; lHash <= line; lHash++)
        {
            printf("#");
        }
        printf("  ");
        for (int rHash = 0; rHash <= line; rHash++)
        {
            printf("#");
        }
        printf("\n");
    }
}
