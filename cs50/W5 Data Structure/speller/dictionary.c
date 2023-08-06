// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
// const unsigned int N = 676;
const unsigned int N = 10000;

// Hash table
node *table[N];

unsigned int wordcount = 0;
void free_node(node *n);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int hashcode = hash(word);

    node *n = table[hashcode];

    while(n != NULL) {

        if(strcasecmp(n->word,word) == 0) {
            return true;
        }

        n = n->next;

    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum = 1;
    int len = strlen(word);
    for(int i=0; i < len; i++) {
        sum *= word[i];
    }

    return sum % N;
    // int hashcode, w1, w0;
    // // printf("len:%lu\n",strlen(word));
    // w0 = toupper(word[0]) - 'A';
    // if(strlen(word) <= 1) {
    //     w1 = 0;
    // } else {
    //     w1 = toupper(word[1]) - 'A';
    // }
    // // printf("word:%s\n",word);
    // // printf("%d %d\n",w0,w1);
    // // printf("code:%d\n",(w0 * 26) + (w1));
    // return (w0 * 26) + (w1);

    // printf("\n");
    // TODO: Improve this hash function
    // return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //read file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL){
        return false;
    }

    //init hash table
    for(int k=0; k<N; k++) {
        table[k] = NULL;
    }

    node *n = malloc(sizeof(node));

    char c;
    int idx = 0;
    while (fread(&c, sizeof(char), 1, file)) {
        //words
        if(c != '\n') {
            n->word[idx] = c;
            idx++;
        //linebreak
        } else {
            n->word[idx] = '\0';
            unsigned int hashcode = hash(n->word);

            //set pointer next to front node
            if(table[hashcode] != NULL) {
                n->next = table[hashcode];
            } else {
                n->next = NULL;
            }
            //replace front node to current node
            table[hashcode] = n;

            //count words
            wordcount++;

            //reset words idx index
            idx = 0;

            // printf("word(%d):%s\n",hashcode,n->word);
            //create new
            n = malloc(sizeof(node));

        }
    }

    // Close text
    fclose(file);
    free(n);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordcount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for(int i=0; i < N; i++) {
        node *n = table[i];
        free_node(n);
    }
    return true;
}

void free_node(node *n) {
    // Handle base case
    if(n == NULL) {
        return;
    }

    // free next
    free_node(n->next);

}
