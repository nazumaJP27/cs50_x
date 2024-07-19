#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./program_name \"count from n\"\n");
        printf("Provide one argument.\n");
        return 1;
    }
    int number = atoi(argv[1]);
    int array[number + 1];

    for (int i = 0; i <= number; i++)
    {
        array[i] = i;
    }

    int engine_start = 1;

    while (number >= 0)
    {
        if (number == 11)
        {
            printf("T-");
        }
        else if ((number >= 8) || (number <= 4 && number >= 1))
        {
            printf("%i, ", array[number]);
        }
        else if ((number <= 7 && number >= 5) && engine_start > 0)
        {
            printf("we have a GO for main engine start. We have main engine start, ");
            engine_start--;
        }
        else if (number == 0)
        {
            printf("GO. Blast of engine!\n");
            return 0;
        }
        number--;
    }
}
