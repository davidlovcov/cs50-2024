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

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Words counter
int words_in_dictionary = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash the word to get index for the hash table
    int hashed_word = hash(word);

    // Cursor that will point at linked-list elements
    node *cursor = table[hashed_word];

    // While the cursor is still in the linked-list
    while (cursor != NULL)
    {
        // If the given word is the same as the pointed word by the cursor
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }

        // else point the cursor at the next node
        cursor = cursor->next;
    }

    // If the word wasn't found in the dictionary
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
    FILE *dictionary_file = fopen(dictionary, "r"); // Create a variable that points to the dictionary and opens it in read mode

    // If the file can't be opened
    if (dictionary_file == NULL)
    {
        return false;
    }

    // If the file was openend successfully
    else
    {
        char *str = malloc(100 * sizeof(char)); // Create a variable that stores the words in the file

        // If memory couldn't be allocated
        if (str == NULL)
        {
            fclose(dictionary_file);
            return false;
        }

        // Iterate through the dictionary and store the words one by one in str
        while (fscanf(dictionary_file, "%s", str) != EOF)
        {
            node *word_node = malloc(sizeof(node)); // Create a new node for the word

            // If memory couldn't be allocated
            if (word_node == NULL)
            {
                fclose(dictionary_file);
                return false;
            }

            strcpy(word_node->word, str); // Set the word of the node to the word stored in str

            word_node->next = NULL; // Point the word to nothing

            int hashed_word = hash(word_node->word); // Hash the word to get index for the hash table

            // Point the word node to the table to make it the first element in the list
            word_node->next = table[hashed_word];

            // Afterwards set the table to be the word_node so it will be before the word node
            table[hashed_word] = word_node;

            words_in_dictionary++; // Increase the words counter
        }

        free(str);
    }

    fclose(dictionary_file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return words_in_dictionary;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate through the hash table array
    for (int i = 0; i < N; i++)
    {
        // Cursor will point at the linked-list's elements
        node *cursor = table[i];

        // While the cursor is in the linked-list
        while (cursor != NULL)
        {
            // Free the current element and point to the next element
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }

        // Point table index i to nothing after freeing the linked list
        table[i] = NULL;
    }

    // After we finished freeing the memory
    return true;
}
