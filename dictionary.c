#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;
int count;
// Number of buckets in hash table
const unsigned int N = (LENGTH+1)*25;

// Hash table
node *table[N] = {NULL};

// Returns true if word is in dictionary, else false
bool check(const char *word)
{  
    //assign index
    int index = hash(word);
    //create a cursor
    node *temp = table[index];
    while (temp != NULL)
    {
        //compare
        if (strcasecmp(temp->word, word) == 0)
        {
    
            return true;
        }
        else
        {
            temp = temp->next;
        }
        
    }
    return false;
}

// Hashes word to a number
// unsigned int hash(const char *word)
// {
//     //first three words to lower
//     char a = tolower(*word);
//     char b = tolower(*(word + 1));
//     char c = tolower(*(word + 2));
//     //calculations 
//     int i1 = a - 'a';
//     i1 *= 26 * 26;
//     int i2 = 0;
//     if (strlen(word) > 1)
//     {
//         i2 = b - 'a';
//         i2 *= 26;
//     }
//     int i3 = 0;
//     if (strlen(word) > 2)
//     {
//         i3 = c - 'a';
//     }    
//     //final index
//     int index = i1 + i2 + i3;
//     return index;
    
// }
unsigned int hash(const char *word)
{
    int sum=0;
    for(int i=0; i < strlen(word); i++)
    {
        sum+=tolower(word[i])-'a';
    }
    return (sum % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //total words
    count = 0;
    //open dictionary
    FILE *dict = fopen(dictionary, "r");
    //check for memory
    if (dict == NULL)
    {
        return false;
    }
    //to store word from dict
    char word1[LENGTH + 1];
    while (fscanf(dict, "%s", word1) != EOF)
    {
        //memory for new node
        node *temp = malloc(sizeof(node));
        //check for leak
        if (temp == NULL)
        {
            return false;
        }
        strcpy(temp->word, word1);
        //total words
        count++;
        //assign to hash table
        int index = hash(word1);
        temp->next = table[index];
        table[index] = temp;
    }
    //file close
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    //total words
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //free memory
    node *cursor = NULL;
    node *temp = NULL;
    //check
    if (cursor != NULL && temp != NULL)
    {
        return false;
    }
    //loop for each hash table
    for (int i = 0; i < N; i++)
    {
        temp = table[i];
        cursor = table[i];
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(temp);
            temp = cursor;
        }
        
    }
    return true;
}