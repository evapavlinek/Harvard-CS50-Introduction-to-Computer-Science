#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long num;
    do
    {
        num = get_long("Number: ");
    }
    while (num < 1);

    int count = 0;
    int digitSum = 0;
    int nonMultipSum = 0;
    int firstTwoDig;
    int firstDig;

    // for (long i = num; i > 0; i = i / 10)
    for (; num > 0; num /= 10)
    {
        count++;
        int digit = num % 10;

        // sum of the digits not multiplied by 2
        if (count % 2 != 0)
        {
            nonMultipSum += digit;
        }
        else
        {
            // multiply every other digit by 2
            int product = digit * 2;

            // add the products' digits together
            digitSum += (product / 10 + product % 10);
        }

        if (num > 9 && num < 100)
        {
            firstTwoDig = num;
        }
        else if (num < 10)
        {
            firstDig = num;
        }
    }

    int final = digitSum + nonMultipSum;
    bool valid = final % 10 == 0;

    if (valid)
    {
        if (count == 15 && (firstTwoDig == 34 || firstTwoDig == 37))
        {
            printf("AMEX\n");
        }
        else if (count == 16 && (firstTwoDig == 51 || firstTwoDig == 52 || firstTwoDig == 53 ||
                                 firstTwoDig == 54 || firstTwoDig == 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((count == 13 || count == 16) && firstDig == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
