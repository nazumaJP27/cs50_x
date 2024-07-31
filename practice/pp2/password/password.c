// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    int uppercl = 0;
    int lowercl = 0;
    int number = 0;
    int symbol = 0;
    for (int i = 0, length = strlen(password); i < length; i++)
    {
        if (isupper(password[i]) > 0)
            uppercl++;
        else if (islower(password[i]) > 0)
            lowercl++;
        else if (isdigit(password[i]) > 0)
            number++;
        else if (ispunct(password[i]) > 0)
            symbol++;
    }
    if (uppercl > 0 && lowercl > 0 && number > 0 && symbol > 0)
        return true;
    else
        return false;
}
