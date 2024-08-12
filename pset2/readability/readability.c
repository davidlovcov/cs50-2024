#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int CountLetters(string text);
int CountWords(string text);
int CountSentences(string text);

int main(int argc, string argv[])
{
    string user_text = get_string("Type your Text: ");
    int amount_letters = CountLetters(user_text);
    int amount_words = CountWords(user_text);
    int amount_sentences = CountSentences(user_text);


    double L = ((double) amount_letters / (double) amount_words) * 100;

    double S = ((double) amount_sentences / (double) amount_words) * 100;

    double index = 0.0588 * L - 0.296 * S - 15.8;
    int rounded_index = round(index);

    if (rounded_index < 1)
    {
        printf("Before Grade 1\n");
    }

    else if (rounded_index > 16)
    {
        printf("Grade 16+\n");
    }

    else
    {
        printf("Grade %i\n", rounded_index);
    }

}

int CountLetters(string text)
{
    int letters_counter = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letters_counter++;
        }
    }

    return letters_counter;
}

int CountWords(string text)
{
    int words_counter = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (!isalpha(text[i]) && isalpha(text[i - 1]) && text[i] != '-')
        {
            words_counter++;
        }
    }

    return words_counter;
}

int CountSentences(string text)
{
    int sentences_counter = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if ((text[i] == '.' || text[i] == '!' || text[i] == '?') && isalpha(text[i - 1]))
        {
            sentences_counter++;
        }
    }

    return sentences_counter++;
}
