// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

unsigned int word_count;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index;

    index = hash(word);
    node *p = table[index];
    while (p != NULL)
    {
        if (strcasecmp(p->word, word) == 0)
        {
            return true;
        }
        p = p->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // First letter
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char word[LENGTH + 1];
    int index;

    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return false;
    }

    word_count = 0;

    // Read strings from file
    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, word);

        // Get index
        index = hash(word);

        n->next = table[index];
        table[index] = n;

        word_count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *p = table[i];
        while (p != NULL)
        {
            node *tmp = p;
            p = p->next;
            free(tmp);
        }
        if (i == N - 1 && p == NULL)
        {
            return true;
        }
    }
    return false;
}