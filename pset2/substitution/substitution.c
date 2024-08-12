#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool ValidateKey(string key);
string ToLowerString(string text);
string ConvertPlaintextToCiphertext(string plaintext, string key);

int main(int argc, string argv[])
{
    string key = argv[1];

    if (argc != 2)
    {
        return 1;
    }

    else if (ValidateKey(key))
    {
        string plaintext = get_string("plaintext: ");

        string ciphertext = ConvertPlaintextToCiphertext(plaintext, key);

        printf("ciphertext: %s\n", ciphertext);
        return 0;
    }

    else
    {
        return 1;
    }
}

bool ValidateKey(string key)
{
    string tmp_key = ToLowerString(key);

    if (strlen(tmp_key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    for (int i = 0; i < strlen(tmp_key); i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return false;
        }

        for (int j = i + 1; j < strlen(tmp_key); j++)
        {
            if (key[i] == key[j])
            {
                printf("Key must not contain repeated characters.\n");
                return false;
            }
        }
    }
    return true;
}

string ToLowerString(string text)
{
    for (int i = 0; i < strlen(text); i++)
    {
        text[i] = tolower(text[i]);
    }
    return text;
}

string ConvertPlaintextToCiphertext(string plaintext, string key)
{
    string ciphertext = plaintext;

    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isupper(plaintext[i]) && isalpha(plaintext[i]))
        {
            ciphertext[i] = toupper(key[plaintext[i] - 'A']);
        }

        else if (islower(plaintext[i]) && isalpha(plaintext[i]))
        {
            ciphertext[i] = tolower(key[plaintext[i] - 'a']);
        }
    }

    return ciphertext;
}
