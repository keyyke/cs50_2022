#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number;
    long tmp_number;
    int sum_of_even = 0;
    int sum_of_odd = 0;
    int digit = 0;
    int i;
    int buz;
    int tmp;
    int sum;
    int judge = 0;

    // input card number
    do
    {
        number = get_long("number: ");
    }
    while (number < 0 || number > 9999999999999999);

    // get digit
    tmp_number = number;
    while (tmp_number != 0)
    {
        tmp_number = tmp_number / 10;
        ++digit;
    }

    // check card type
    tmp_number = number;
    for (i = 0; i < digit - 2; i++)
    {
        tmp_number = tmp_number / 10;
    }
    if (digit == 15 && (tmp_number == 34 || tmp_number == 37))
    {
        judge = 1;
    }
    else if (digit == 16 && (tmp_number == 51 || tmp_number == 52 || tmp_number == 53 || tmp_number == 54 || tmp_number == 55))
    {
        judge = 2;
    }
    else
    {
        tmp_number = tmp_number / 10;
        if ((digit == 13 || digit == 16) && tmp_number == 4)
        {
            judge = 3;
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }

    //Luhn
    i = 1;
    while (number != 0)
    {
        tmp_number = number;
        number /= 10;
        number *= 10;
        buz = tmp_number - number;
        number /= 10;

        if (i % 2 == 0)
        {
            buz *= 2;
            if (buz >= 10)
            {
                tmp = buz;
                buz /= 10;
                buz += tmp % 10;
            }
            sum_of_even += buz;
        }
        else
        {
            sum_of_odd += buz;
        }
        i++;
    }
    sum = sum_of_even + sum_of_odd;
    if (sum % 10 != 0)
    {
        judge = 0;
    }
    if (judge == 1)
    {
        printf("AMEX\n");
        return 0;
    }
    else if (judge == 2)
    {
        printf("MASTERCARD\n");
        return 0;
    }
    else if (judge == 3)
    {
        printf("VISA\n");
        return 0;
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }
}