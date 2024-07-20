#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int LENGTH = 26;
char ALPHA[LENGTH] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                      'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
int INKEY[LENGTH] = {0}; // The index represents the alpha letters
                         // INKEY[1] = 1 means that 'B' is in the key provided

string cipher(char key[LENGTH], string plaintext);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != LENGTH)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Create an array of size LENGTH
    char key[LENGTH];

    // Add key chars to key[]
    for (int i = 0; i < LENGTH; i++)
    {
        if (isalpha(argv[1][i]))
        {
            char letter_char = toupper(argv[1][i]);
            int letter_index = letter_char - 65;

            if (INKEY[letter_index] == 0)
            {
                key[i] = letter_char;
                INKEY[letter_index] = 1;
            }
            else
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
        else
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }

    string plaintext = get_string("plaintext: ");
    string ciphertext = cipher(key, plaintext);

    printf("ciphertext: %s\n", ciphertext);

    return 0;
}

string cipher(char key[LENGTH], string text)
{
    string encrypted = text;
    for (int i = 0, lenght = strlen(encrypted), is_lower; i < lenght; i++)
    {
        if (isalpha(encrypted[i]))
        {
            is_lower = islower(encrypted[i]);

            char letter = toupper(encrypted[i]);
            int letter_index = letter - 65;

            if (is_lower)
            {
                encrypted[i] = tolower(key[letter_index]);
            }
            else
            {
                encrypted[i] = key[letter_index];
            }
            printf("%c\n", key[letter_index]);
        }
    }
    return encrypted;
}
