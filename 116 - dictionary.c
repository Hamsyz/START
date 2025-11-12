// Implements a dictionary's functionality
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dictionary.h"
#include <string.h>

//variable to keep track of how many words are loaded
int loaded = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

//prototype
void freenode(node *nodeptr);

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    bool found = false;

    //which bucket
    int bucket = toupper(word[0]) - 'A';

    //create a cursor to compare
    node *cursor = table[bucket];

    //create memory for the word that we are going to search on dictionary
    int len = strlen(word);
    char *upperword = malloc(len +1);

    //copy the word and uppercase it
    for(int i = 0; i < len; i++)
    {
         upperword[i] = toupper(word[i]);
    }

    // add \0 at the end of the string
    upperword[len] = '\0';

    while(found == false)
    {
        char *dicword = NULL;

        //check if we are on the last ring on the chain
        if(cursor != NULL)
        {
            //create memory for the current dicword
            int lendic = strlen(cursor -> word);
            dicword = malloc(lendic + 1);

            //copy the word and uppercase it
            for(int i = 0; i < lendic + 1; i++)
            {
                 dicword[i] = toupper(cursor -> word[i]);
            }

            if(strcmp(upperword , dicword) == 0)
            {
                free(dicword);
                free(upperword);
                return true;
            }
        }
        else
        {
            free(upperword);
            free(dicword);
            return false;
        }

        //move the cursor to the next one
        free(dicword);
        cursor = cursor -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    //open dictionary file
    FILE *dicptr = fopen(dictionary , "r");
    if(dicptr == NULL)
    {
        fclose(dicptr);
        return false;
    }

    char newword[LENGTH + 1];

    //create a loop
    while(fscanf(dicptr, "%s", newword) != EOF)
    {
         //get the index of the new word
         int index = hash(newword);
         node *newnode = malloc(sizeof(node));
         if(newnode == NULL)
         {
            return false;
         }

         //check if it is the first word on that bucket
         if(table[index] == NULL)
         {
            strcpy(newnode -> word , newword);
            table[index] = newnode;
            newnode -> next = NULL;
         }
         else
         {
            strcpy(newnode -> word , newword);
            newnode -> next = table[index];
            table[index] = newnode;
         }

         //keep track of the loaded words count
         loaded++;
    }

    //close the file
    fclose(dicptr);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return loaded;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for(int i = 0; i < N; i++)
    {
        //check if it already empty or not
        if(table[i] != NULL)
        {
            freenode(table[i]);
        }
    }

    return true;
}

//helper function for unload (recursion)
void freenode(node *nodeptr )
{
    //base case
    if(nodeptr -> next == NULL)
    {
        free(nodeptr);
    }
    else
    {
        freenode(nodeptr -> next);
        free(nodeptr);
    }
}


