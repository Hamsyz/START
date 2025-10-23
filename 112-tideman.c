#include <cs50.h>
#include <stdio.h>
#include <string.h>


// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// strenght of the pairs
int strenght[MAX*(MAX-1)/2];

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
void lock_pairs(void);
void print_winner(void);
bool search(int start,int current);

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
    // TODO
    for(int i = 0; i < candidate_count; i++)
    {
        if(!strcmp(name,candidates[i]))
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for(int h = 0; h < candidate_count; h++)
    {
        for(int i = candidate_count-1; i >= 0; i--)
        {
            if(h == i)
            {
                break;
            }
            else
            {
                preferences[ranks[h]][ranks[i]]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    int can = candidate_count;
    for(int i = 0; i < can; i++)
    {
        for(int k = can-1; k > -1; k--)
        {
            if(k == i)
            {
                break;
            }
            else
            {
                if(preferences[i][k] > preferences[k][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = k;
                    strenght[pair_count] = preferences[i][k] - preferences[k][i];
                    pair_count++;
                }
                else if(preferences[i][k] < preferences[k][i])
                {
                    pairs[pair_count].winner = k;
                    pairs[pair_count].loser = i;
                    strenght[pair_count] = preferences[k][i] - preferences[i][k];
                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    for(int i = 0; i < pair_count; i++)
    {
        for(int k = 0; k < pair_count-1-i; k++)
        {
            if(strenght[k] < strenght[k+1])
            {
                int tempwinner = pairs[k+1].winner;
                int temploser = pairs[k+1].loser;
                pairs[k+1].winner = pairs[k].winner;
                pairs[k+1].loser = pairs[k].loser;
                pairs[k].winner =  tempwinner;
                pairs[k].loser = temploser;
                int tempstrenght = strenght[k+1];
                strenght[k+1] = strenght[k];
                strenght[k] = tempstrenght;
           }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for(int i = 0; i < pair_count; i++)
    {
         locked[pairs[i].winner][pairs[i].loser] = true;
         if(search(pairs[i].winner,pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    bool found;
    for(int f = 0; f < candidate_count; f++)
    {
        for(int k = 0; k < candidate_count; k++)
        {
            if(locked[k][f])
            {
                found = false;
                break;
            }
            else
            {
                found = true;
            }
        }
        if(found)
        {
            printf("%s\n",candidates[f]);
        }
    }
    return;
}

// Check if there is a way back to the winner (cycle)
bool search(int start,int current)
{
    for(int f = 0; f < candidate_count; f++)
    {
        if(locked[current][pairs[f].loser] == true)
        {
            if(pairs[f].loser == start)
            {
                return true;
            }
            if(search(start,pairs[f].loser))
            {
                return true;
            }
        }
    }
    return false;
}
