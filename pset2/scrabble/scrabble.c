#include <cs50.h>
#include <stdio.h>
#include <string.h>

void CompareScores(string player_one_word, string player_two_word);
int CalculateScore(string word);

int main(int argc, string argv[])
{

    string player_one_word = get_string("Player 1: ");
    string player_two_word = get_string("Player 2: ");

    CompareScores(player_one_word, player_two_word);

    return 0;
}

void CompareScores(string player_one_word, string player_two_word)
{
    int player_one_score = CalculateScore(player_one_word);
    int player_two_score = CalculateScore(player_two_word);

    if (player_one_score > player_two_score)
    {
        printf("Player 1 wins!\n");
    }

    else if (player_two_score > player_one_score)
    {
        printf("Player 2 wins!\n");
    }

    else
    {
        printf("Tie!\n");
    }
}

int CalculateScore(string word)
{
    int scores[26] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                      1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    int score = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        if (word[i] >= 'A' && word[i] <= 'Z')
        {
            score += scores[word[i] - 'A'];
        }

        else if (word[i] >= 'a' && word[i] <= 'z')
        {
            score += scores[word[i] - 'a'];
        }
    }

    return score;
}
