#include <cs50.h>
#include <stdio.h>
#include <string.h>

int TABLE_SIZE;

int get_row(string prompt, int row_size); // Returns a positive number <= column_size
int get_column(string prompt, int column_size); // Gets a char 'A/a' through 'Z/z' and returns it as an int (a == 1 & z == 26) <= coumn_size
void reset_table(char arr[TABLE_SIZE][TABLE_SIZE], int size); // Assign a single space to every index in the given array
void update_table(char arr[TABLE_SIZE][TABLE_SIZE], int size, int change_row, int change_column, char assign); // Prototype of the function that will update the display of the given array

int main(void)
{
    do
    {
        TABLE_SIZE = get_int("Table size (3-26): ");
    }
    while (TABLE_SIZE < 3 || TABLE_SIZE > 26);

    char array2d[TABLE_SIZE][TABLE_SIZE]; // Creates a 2D array with the chosen size
    reset_table(array2d, TABLE_SIZE);
    update_table(array2d, TABLE_SIZE, -1, -1, 'x');

    int squares = TABLE_SIZE * TABLE_SIZE;

    int strcasecmp(const char *s1, const char *s2); // Prototype
    bool wants_to_quit = false;
    string finish;

    do
    {
        char input = get_char("Assign \"char\" to table. Char: ");
        char mark_column = get_column("Column: ", TABLE_SIZE); // // Variable to index to a specific column in the table created
        int mark_row = get_row("Row: ", TABLE_SIZE); // Variable to index to a specific row in the table created

        update_table(array2d, TABLE_SIZE, mark_row - 1, mark_column - 1, input);
        squares--;

        finish = get_string("Continue: ");
        wants_to_quit = (strcasecmp(finish, "quit") == 0) ||
                 (strcasecmp(finish, "q") == 0) ||
                 (strcasecmp(finish, "n") == 0) ||
                 (strcasecmp(finish, "no") == 0) ||
                 (strcasecmp(finish, "e") == 0) ||
                 (strcasecmp(finish, "end") == 0) ||
                 (strcasecmp(finish, "0") == 0);
    }
    while (!wants_to_quit);
}

int get_row(string prompt, int column_size)
{ // Returns a positive number <= column_size
    int row;
    do
    {
        row = get_int("%s", prompt);
    }
    while (row <= 0 || row > column_size);

    return row;
}

int get_column(string prompt, int column_size)
{ // Gets a char 'A/a' through 'Z/z' and returns it as an int (a == 1 & z == 26) <= coumn_size
    int column;
    do
    {
        column = get_char("%s", prompt);
        // Converts using decimal ASCII chars:
        if (column >= 97 && column <= 122)
        { // If gets a char (a-z)
            column -= 96;
        }
        else if (column >= 65 && column <= 90)
        { // If gets a char (A-Z)
            column -= 64;
        }
    }
    while (column <= 0 || column > column_size);

    return column;
}

void reset_table(char arr[TABLE_SIZE][TABLE_SIZE], int size)
{
    for (int row = 0; row < size; row++)
    {
        for (int column = 0; column < size; column++)
        {
            arr[row][column] = ' ';
        }
    }
}

void update_table(char arr[TABLE_SIZE][TABLE_SIZE], int table_size, int change_row, int change_column, char assign)
{
    for (int i = 0; i < table_size; i++)
    { // Prints the column letter
        if (i == 0) { printf("    "); }
        printf("%c   ", i + 65);
    }
    printf("\n");
    for (int row = 0; row < table_size; row++)
        {
            printf("%i.", row + 1); // Prints the row number
            if (row < 9)
            { // Prints a space if the row number have one digit
                printf(" ");
            }
            for (int column = 0; column < table_size; column++)
            {
                if (change_row >= 0 && change_column >= 0 && row == change_row && column == change_column) // Change array value
                {
                    arr[row][column] = assign;
                }
                printf(" %c ", arr[row][column]);
                if (column < table_size - 1)
                {
                    printf("|");
                }
            }
            printf("\n");
            if (row < table_size - 1)
            {
                for (int i = 0; i < table_size; i++)
                {
                    if (i == 0) { printf("   "); }
                    printf("---");
                    if (i < table_size - 1)
                    {
                        printf("-");
                    }
                }
                printf("\n");
            }
        }
        printf("\n");
}
