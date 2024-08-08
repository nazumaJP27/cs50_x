#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO
    // If the string has only one number, returns it converted to an int by subtracting the ASCII value of '0'
    if (strlen(input) == 1)
        return input[0] - 48;

    // The last number is converted to an int by subtracting the ASCII value of '0' char
    int number = input[strlen(input) - 1] - 48;
    // Move null terminator one position to the left
    input[strlen(input) - 1] = 0;
    // Return converted number + 10 times the integer value of the shortened string.
    return number + (convert(input) * 10);
}
