#include <cs50.h>
#include <stdio.h>

int number_lenght(long number);
int luhns_alg(long cardNumber);
int get_first_n_numbers(long number, int n_numbers);

int main(void)
{
    long card = get_long("Number: ");
    int number_of_digits = number_lenght(card);
    int first = get_first_n_numbers(card, 1);
    string card_flag = "INVALID";

    if (number_of_digits >= 13 && number_of_digits <= 16)
    {
        int verify = luhns_alg(card);
        if ((verify % 10) != 0)
        {
            card_flag = "INVALID";
        }
        else if ((number_of_digits == 13 || number_of_digits == 16) &&
                 get_first_n_numbers(card, 1) == 4)
        {
            card_flag = "VISA";
        }
        else if ((number_of_digits == 16) &&
                 (get_first_n_numbers(card, 2) >= 51 && get_first_n_numbers(card, 2) <= 55))
        {
            card_flag = "MASTERCARD";
        }
        else if ((number_of_digits == 15) &&
                 (get_first_n_numbers(card, 2) == 34 || get_first_n_numbers(card, 2) == 37))
        {
            card_flag = "AMEX";
        }
    }

    printf("%s\n", card_flag);
}

int luhns_alg(long cardNumber)
{
    int sum_second_to_last = 0;
    int every_other = 0;
    int sum_of_others = 0;

    while (cardNumber > 0)
    {
        int last_digit = cardNumber % 10;
        if (every_other == 1)
        {
            int product = last_digit *= 2;
            if ((product / 10) > 0) // if the product have two digits
            {
                int first = product % 10;
                int last = product / 10;
                sum_second_to_last += first + last;
            }
            else
            {
                sum_second_to_last += product;
            }
            every_other = 0;
        }
        else
        {
            sum_of_others += last_digit;
            every_other = 1;
        }
        cardNumber /= 10;
    }
    return (sum_second_to_last + sum_of_others);
}

int number_lenght(long number)
{
    int number_of_digits = 0;

    while (number > 0)
    {
        number_of_digits++;
        number /= 10;
    }

    return number_of_digits;
}

int get_first_n_numbers(long number, int n_numbers)
{
    int x;
    if (n_numbers == 2)
    {
        x = 100;
    }
    else if (n_numbers == 1)
    {
        x = 10;
    }
    else
    {
        return 0;
    }

    while (number >= x)
    {
        number /= 10;
    }
    return number;
}
