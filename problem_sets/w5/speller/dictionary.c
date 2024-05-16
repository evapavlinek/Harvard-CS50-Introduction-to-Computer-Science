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

// A number of buckets in hash table
const unsigned int N = 26 * LENGTH;

// Hash table
node *table[N];

// Dictionary word counter
unsigned int wordCounter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // hash word to obtain a hash value
    int hashIndex = hash(word);

    // access linked list at that index in the hash table
    node *currentNode = table[hashIndex];

    // traverse linked list, looking for the word
    while (currentNode != NULL)
    {
        if (strcasecmp(word, currentNode->word) == 0)
        {
            return true;
        }
        else
        {
            currentNode = currentNode->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // a hash table based on the first letter and the length of the word
    return 26 * (toupper(word[0]) - 'A') + strlen(word);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open dictionary file
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
    {
        return false;
    }

    // read strings from file one at a time
    char *word = malloc(sizeof(char) * (LENGTH + 1));
    while (fscanf(f, "%s", word) != EOF)
    {
        wordCounter++;

        // create a new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, word);
        n->next = NULL;

        // hash word to obtain a hash value
        int hashIndex = hash(word);

        // insert node into hash table at that location
        if (table[hashIndex] == NULL)
        {
            table[hashIndex] = n;
        }
        else
        {
            n->next = table[hashIndex];
            table[hashIndex] = n;
        }
    }

    free(word);
    fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordCounter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // iterate over the hash table and free all nodes
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            node *currentNode = table[i];
            node *tmp;
            while (currentNode != NULL)
            {
                tmp = currentNode;
                currentNode = currentNode->next;
                free(tmp);
            }
        }
    }

    return true;
}

// Some other hash functions that I've tried:

// The original one - based on the first letter of the word

// const unsigned int N = 26;
// unsigned int hash(const char *word)
//{
//    return toupper(word[0]) - 'A';
//}

// Based on the first letter and whether the second letter is between
// A and M or M and Z

// const unsigned int N = 52;
// unsigned int hash(const char *word)
// {
//
//    if (toupper(word[1]) - 'A' > 13)
//    {
//        return 2 * (toupper(word[0]) - 'A') + 1;
//    }
//
//    return 2 * (toupper(word[0]) - 'A');
// }

// Based on the first letter of the word + whether the second one is one
// of the vowels or something else

// const unsigned int N = 26 * 6;
// unsigned int hash(const char *word)
//{
//     switch(toupper(word[1]))
//     {
//         case 'A':
//             return (6 * toupper(word[0]) - 'A') + 0;
//             break;
//         case 'E':
//             return (6 * toupper(word[0]) - 'A') + 1;
//             break;
//         case 'I':
//             return (6 * toupper(word[0]) - 'A') + 2;
//             break;
//         case 'O':
//             return (6 * toupper(word[0]) - 'A') + 3;
//             break;
//         case 'U':
//             return (6 * toupper(word[0]) - 'A') + 4;
//             break;
//         default:
//             return (6 * toupper(word[0]) - 'A') + 5;
//             break;
//     }
//
//     return 0;
// }
