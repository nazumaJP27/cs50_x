#include <cs50.h>
#include <stdio.h>
#include <string.h>

int SCRABBLE[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
int word_score(string word);

int main(void)
{
    string p1_word = get_string("Player 1: ");
    string p2_word = get_string("Player 2: ");

    int p1_points = word_score(p1_word);
    int p2_points = word_score(p2_word);

    if (p1_points > p2_points)
    {
        printf("Player 1 wins!\n");
    }
    else if (p1_points < p2_points)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
    return 0;
}

int word_score(string word)
{
    int score = 0;
    for (int i = 0, length = strlen(word); i < length; i++)
    {
        int letter = word[i];
        if (letter >= 97 && letter <= 122)
        { // If letter is a char a-z
            letter -= 97;
        }
        else if (letter >= 65 && letter <= 90)
        { // If letter is a char A-Z
            letter -= 65;
        }
        score += SCRABBLE[letter];
    }
    return score;
}
