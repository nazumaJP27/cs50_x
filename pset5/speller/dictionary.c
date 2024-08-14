// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Prototypes for dictionaty.c only
node *create_node(char *s);
void free_node(node *node);

// TODO: Choose number of buckets in hash table
const unsigned int N = 2027;

// Hash table
node *table[N];

int words_in_dict = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *cursor = table[hash(word)];
    if (!cursor)
        return false;

    // Compare word with same hash value while cursor != NULL
    do
    {
        if (strcasecmp(cursor->word, word) == 0)
            return true;
        else
            cursor = cursor->next;
    }
    while (cursor);

    // Return false if not find a match
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    unsigned int hash_word = 0;
    // Small prime number
    unsigned int prime = 71;

    for (int i = 0, len = strlen(word); i < len; i++)
    {
        if (word[i] == '\n')
            break;
        hash_word = hash_word * prime + tolower(word[i]);
    }
    return hash_word % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Opens dictionary file
    FILE *dict_file = fopen(dictionary, "r");
    if (dict_file == NULL)
    {
        printf("Error while loading dictionary file\n");
        return false;
    }

    // Read dict file line by line
    char word[LENGTH + 1];
    while (fgets(word, sizeof(word), dict_file) != NULL)
    {
        if (word[0] != '\n')
        {
            unsigned int hash_value = hash(word);
            // Create new node and copy word
            node *tmp = create_node(word);

            // tmp.next point to the current first node in the table
            tmp->next = table[hash_value];

            // Assign node to table hash index
            table[hash_value] = tmp;

            // Increment word counter
            words_in_dict++;
        }
    }
    fclose(dict_file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return words_in_dict;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        if (table[i])
            free_node(table[i]);
    }
    return true;
}

// Return a pointer to node and copy s to node.word
node *create_node(char *s)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        printf("Failed to allocate memory for node\n");
        return NULL;
    }

    int i = 0;
    // Copy string to node.word
    while ((s[i] != '\n') && (s[i] != '\0'))
    {
        n->word[i] = s[i];
        i++;
    }
    n->word[i] = '\0';
    n->next = NULL;
    return n;
}

// Free node
void free_node(node *n)
{
    while (n != NULL)
    {
        node *tmp = n;
        n = n->next;
        free(tmp);
    }
}
