#include <cs50.h>
#include <stdio.h>
#include <stdlib.h> // for strtof()

bool valid_triangle(float a, float b, float c);

int main(int argc, string argv[])
{
    if (argc != 4)
    {
        printf("Usage: ./valid-triangle side1 side2 side3\n");
        printf("Enter three real numbers as arguments.\n");
        return 1;
    }

    float tri_sides[3];
    for (int i = 0; i < argc - 1; i++)
    {
        char *endptr;
        tri_sides[i] = strtof(argv[i + 1], &endptr);

        // Check for conversion errors:
        if (*endptr != '\0')
        { // Non-numeric characters encountered
            printf("Invalid input: \"%s\" is not a real number.\n", argv[i + 1]);
            return 1;
        }
    }

    string is_valid;
    if (valid_triangle(tri_sides[0], tri_sides[1], tri_sides[2]))
    {
        is_valid = "VALID";
    }
    else
    {
        is_valid = "INVALID";
    }
    printf("The triangle is %s\n", is_valid);
}

bool valid_triangle(float a, float b, float c)
{
    if (a <= 0 || b <= 0 || c <= 0)
    {
        return false;
    }
    else if ((a + b <= c) || (a + c <= b) || (c + b <= a))
    {
        return false;
    }
    return true;
}
