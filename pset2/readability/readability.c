#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

double coleman_index(string text); // Returns the Coleman-Liau Index of string text
int ispxq(char c);                 // Returns non-zero if char c is equal '.', '!' or '?'

int main(void)
{
    string text = get_string("Text: ");
    int grade = round(coleman_index(text));

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

double coleman_index(string text)
{
    float letters = 0;
    float words = 0;
    float sentences = 0;

    // Loop to every char in the text
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        char c = text[i];
        // Increment number of letters on every char a-z
        if (isalpha(c))
        {
            letters++;
        }
        // Increment number of words on every white space char, *//+1 in the end of the loop
        else if (isspace(c))
        {
            words++;
        }
        // Increment number of sentences on every period, exclamation point, or question mark
        else if (ispxq(c) && isalpha(text[i - 1]))
        {
            sentences++;
        }
    }
    words++; //*

    float L = (letters / words) * 100.0;
    float S = (sentences / words) * 100.0;
    double index = (0.0588 * L) - (0.296 * S) - 15.8;

    return index;
}

int ispxq(char c)
{
    char pxq[3] = {'.', '!', '?'};
    for (int i = 0; i < 3; i++)
    {
        if (c == pxq[i])
        {
            return 1;
        }
    }
    return 0;
}
