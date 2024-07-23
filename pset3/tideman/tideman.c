#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
int pairs_margin(int index);
void lock_pairs(void);
bool is_path(int loser, int winner);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Find the index of the candidate who matches the name provided
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
            return true + (ranks[rank] = i);
    }
    // If name provided not in candidates
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Add a vote to rank i over j
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
            preferences[ranks[i]][ranks[j]]++;
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Check if i and j are tied
            if (preferences[i][j] != preferences[j][i])
            {
                // Check if i wins over j
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                }
                else
                {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;
                }
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int swaps = 0;
    do
    {
        swaps = 0;
        for (int i = 0; i < pair_count - 1; i++)
        {
            if (pairs_margin(i) < pairs_margin(i + 1))
            {
                printf("%i < %i. ", pairs_margin(i), pairs_margin(i + 1));
                pair temp = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = temp;
                swaps++;
            }
        }
    }
    while (swaps > 0);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Locks the first pair
    locked[pairs[0].winner][pairs[0].loser] = true;
    // Go through the pairs[] starting with the second pair
    for (int i = 1; i < pair_count; i++)
    {
        // Checks if the locked pair will not create a cycle
        if (!is_path(pairs[i].loser, pairs[i].winner))
            locked[pairs[i].winner][pairs[i].loser] = true;
    }
}

// Print the winner of the election
void print_winner(void)
{
    int source; // Index of the candidate with no incoming edges
    // Find the source of the graph by checking if the candidate have incoming edges
    for (int i = 0, incoming_edges = 0; i < candidate_count; incoming_edges = 0, i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                incoming_edges++;
                break;
            }
        }
        if (!incoming_edges)
            source = i;
    }

    printf("%s\n", candidates[source]);
}

// Return the winning margin of pairs[index]
int pairs_margin(int index)
{
    return preferences[pairs[index].winner][pairs[index].loser] -
           preferences[pairs[index].loser][pairs[index].winner];
}

// Return true or false for a path from a candidate to another
bool is_path(int loser, int winner)
{
    if (loser == winner)
        return true;
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if loser has an edge over i
        if (locked[loser][i])
            if (is_path(i, winner))
                return true;
    }
    return false;
}
