#include <cs50.h>
#include <stdio.h>

int check_luhn(long);
int count_digits(long);
void is_valid(long);

int main(void)
{
    long card;
     // Prompts the user for a number (long)
    do
    {
        card = get_long("Number: ");
    }
    while (card < 1 || card > 9999999999999999);
    
    int result = check_luhn(card);
    is_valid(result);
}

int check_luhn(long card)
{
    // visa example
    // card = 4003600000000014;
    // mastercard example
    // card = 5555555555554444;
    // amex example
    // card = 378282246310005;
    // invalid example
    // card = 88003600000000014;
    int nDigits = count_digits(card);
    if (nDigits < 13)
    {
        return 0;
    }
    int lDigit = 0;
    int result = 0;
    int s1 = 0;
    int s2 = 0;

    for (int digitPos = 1; digitPos <= nDigits; digitPos++)
    {
        // Actual last digit
        lDigit = card % 10;
        // Check even or odd number
        if (digitPos % 2 == 0)
        {
            // Even (par)
            int produto = lDigit * 2;
            int resultado = produto > 9 ? produto - 9 : produto;
            s2 = s2 + resultado;
        }
        else
        {
            // Odd (impar)
            s1 += lDigit;
        }
        // Take it the first two digits
        // Or just the first one if a potential VISA
        if (digitPos + 1 == nDigits)
        {
            result = card / 10 == 4 ? card / 10 : card;
        }
        // Remove the actual last digit
        card = card / 10;
    }
    if ((s1 + s2) % 10 != 0)
    {
        result = 0;
    }
    return result;
}

int count_digits(long start)
{
    int counter = 0;
    do
    {
        start = start / 10;
        counter++;
    }
    while (start > 0);
    return counter;
}

void is_valid(long card)
{
    switch (card)
    {
        case 34:
        case 37:
            printf("AMEX\n");
            break;
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
            printf("MASTERCARD\n");
            break;
        case 4:
            printf("VISA\n");
            break;
        default:
            printf("INVALID\n");
    }
}
