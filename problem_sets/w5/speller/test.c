// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

unsigned int hash(const char *word);

// TODO: Choose number of buckets in hash table
//const unsigned int N = 26;
//const unsigned int N = 52;
const unsigned int N = 5 * 26 + 1;
int arr[N];

int main()
{
    //printf("%i\n", hash("ac"));
    arr[hash("a's")] = 1;
    for (int i = 0; i < N; i++)
    {
        printf("%i\n", arr[i]);
    }
}


unsigned int hash(const char *word)
{
    // etaoinsrhldcumfpgwybvkxjqz
    if (word[0] == '\'' || word[1] == '\'')
    {
        return 130;
    }

    switch(toupper(word[0]))
    {
        case 'A':
            return toupper(word[1]) - 'A';
            break;
        case 'E':
            return 26 + (toupper(word[1]) - 'A') ;
            break;
        case 'I':
            return 2 * 26 + toupper(word[1]) - 'A';
            break;
        case 'O':
            return 3 * 26 + toupper(word[1]) - 'A';
            break;
        case 'U':
            return 4 * 26 + toupper(word[1]) - 'A';
            break;
    }

    return 0;
}
