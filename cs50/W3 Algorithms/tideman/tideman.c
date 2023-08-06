#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <search.h>

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
}
pair;

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

void swap(pair *a, pair *b);
bool check_loop(int origin,int target);

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
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(candidates[i],name) == 0) {
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
    for (int i = 0; i < candidate_count - 1; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            // printf("i:%d j:%d\n",ranks[i],ranks[j]);
            int win_cndt = ranks[i];
            int lose_cndt = ranks[j];
            preferences[win_cndt][lose_cndt] += 1;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count - 1; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            // printf("i:%d j:%d\n",ranks[i],ranks[j]);
            pair p;
            if(preferences[i][j] > preferences[j][i]) {
                p.winner = i;
                p.loser = j;
                pairs[pair_count] = p;
                pair_count++;
            } else if(preferences[i][j] < preferences[j][i]) {
                p.winner = j;
                p.loser = i;
                pairs[pair_count] = p;
                pair_count++;
            }
        }
    }

    return;
}

void swap(pair *a, pair *b) {
  pair temp = *a;
  *a = *b;
  *b = temp;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // for(int i = 0; i < pair_count; i++) {
    //     printf("winner:%d loser:%d ; votes:%d \n",pairs[i].winner,pairs[i].loser,preferences[pairs[i].winner][pairs[i].loser]);
    // }
    for (int i = 0; i < pair_count - 1; i++) {
        int max_idx = i;
        int max_win_num = preferences[pairs[i].winner][pairs[i].loser];
        for (int j = i + 1; j < pair_count; j++) {
            int win_num = preferences[pairs[j].winner][pairs[j].loser];
            if (win_num > max_win_num){
                max_idx = j;
            }
        }
        swap(&pairs[i],&pairs[max_idx]);
    }

    // printf("---\n");
    // for(int i = 0; i < pair_count; i++) {
    //     printf("winner:%d loser:%d ; votes:%d \n",pairs[i].winner,pairs[i].loser,preferences[pairs[i].winner][pairs[i].loser]);
    // }

    return;
}

bool check_loop(int origin,int target) {
    //base case
    if(origin == target)
        return true;

    //recursive case
    for (int next_target = 0; next_target < candidate_count;next_target++) {
        if(locked[target][next_target]) {
            bool isLoop = check_loop(origin,next_target);
            if(isLoop)
                return true;
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for(int i = 0; i < pair_count; i++) {

        if(!check_loop(pairs[i].winner,pairs[i].loser)) {
            locked[pairs[i].winner][pairs[i].loser] = true;
            // printf("* (%d,%d) locked * \n",pairs[i].winner,pairs[i].loser);
        }

    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int j = 0; j < candidate_count; j++) {
        bool beenLocked = false;
        for (int i = 0; i < candidate_count; i++) {
            if(locked[i][j]){
                beenLocked = true;
                break;
            }
        }

        if(!beenLocked) {
            printf("%s\n",candidates[j]);
            return;
        }
    }

    return;
}