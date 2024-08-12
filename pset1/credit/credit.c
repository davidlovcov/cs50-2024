#include <cs50.h>
#include <stdio.h>

bool LuhnsAlgorithm(long card_number);
long GetFirstTwoDigits(long card_number);
int GetCardLength(long card_number);
void VerifyCard(long card_number);

int main(int argc, string argv[])
{
    long card_number = get_long("Give me your Card Number ;): ");

    VerifyCard(card_number);

    return 0;
}

void VerifyCard(long card_number)
{
    int first_digits = GetFirstTwoDigits(card_number);
    int card_length = GetCardLength(card_number);

    if ((first_digits == 34 || first_digits == 37) && card_length == 15 &&
        LuhnsAlgorithm(card_number))
    {
        printf("AMEX\n");
    }

    else if ((first_digits >= 51 && first_digits <= 55) && card_length == 16 &&
             LuhnsAlgorithm(card_number))
    {
        printf("MASTERCARD\n");
    }
    else if ((first_digits >= 40 && first_digits <= 49) &&
             (card_length == 13 || card_length == 16) && LuhnsAlgorithm(card_number))
    {
        printf("VISA\n");
    }

    else
    {
        printf("INVALID\n");
    }
}

long GetFirstTwoDigits(long card_number)
{
    long first_two_digits = card_number;

    while (first_two_digits > 100)
    {
        first_two_digits /= 10;
    }

    return first_two_digits;
}

int GetCardLength(long card_number)
{
    long temp_card = card_number;
    int length = 0;

    while (temp_card > 0)
    {
        temp_card /= 10;
        length++;
    }

    return length;
}

bool LuhnsAlgorithm(long card_number)
{
    int every_other_digit = 0;
    int sum_products = 0;
    long card_calc = card_number;

    while (card_calc > 0)
    {
        card_calc /= 10;
        every_other_digit = (card_calc % 10) * 2;

        while (every_other_digit > 9)
        {
            sum_products += every_other_digit % 10;
            every_other_digit /= 10;
        }

        sum_products += every_other_digit;

        card_calc /= 10;
    }

    card_calc = card_number;

    while (card_calc > 0)
    {
        sum_products += (card_calc % 10);
        card_calc /= 100;
    }

    if (sum_products % 10 == 0)
    {
        return true;
    }

    else
    {
        return false;
    }
}
