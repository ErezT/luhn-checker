#include <cs50.h>
#include <stdio.h>
#include <math.h>

int numbreaker (int n);
bool check_validity(long long number);
string card_check(long long cc);
//American Express uses 15-digit numbers, MasterCard uses 16-digit numbers, and Visa uses 13- and 16-digit numbers.
//American Express numbers all start with 34 or 37; MasterCard numbers all start with 51, 52, 53, 54, or 55; and Visa numbers all start with 4

int main(void)
{
    printf("Number: ");
    long long credit_card = get_long_long();
    string result = card_check(credit_card);
    printf("%s\n", result);
    return 0;
}

int numbreaker (int n)
{
    return n % 10;
}

bool check_validity(long long number)
{
    const long long max = 100000000000000000;
    int added_product = 0;
    int added_others = 0;
    int mega_final = 0;
    
    for ( long long i = 10, j = 0; i < max; j++) //loops over card number to target each number
    {
        long long res = fmod(j, 2); // checks for every other number
        long long doub = fmod(number, i); //
        long long wanted = floor(doub / (i / 10));
        if (res != 0)
        {
            int sum = wanted * 2;
            if (sum > 9)
            {
                sum = numbreaker(sum) + 1;
            }
            added_product = added_product + sum;
        }
        else
        {
            added_others = added_others + wanted;
        }
        
        i = i * 10;
    }

    mega_final = added_product + added_others;
    
    if(mega_final % 10 == 0)
    {
        printf("%d\n", mega_final);
        return true;
    }
    else
    {
        printf("%d\n", mega_final);
        return false;
    }
}

string card_check(long long cc)
{
    string card = "INVALID";
    
    if (check_validity(cc))
    {
        //check length is 16
        if (cc < 10000000000000000 && cc > 1000000000000000)
        {
            //check for visa beginning
            if ( floor(cc / 1000000000000000) == 4 )
            {
                card = "VISA";
            }
            //check for mastercard beggining
            else if (floor(cc / 1000000000000000) == 51 || floor(cc / 1000000000000000) == 52 || floor(cc / 1000000000000000) == 53 || floor(cc / 1000000000000000) == 54 || floor(cc / 1000000000000000) == 55)
            {
                printf("%f\n", floor(cc / 1000000000000000));
                card = "MASTERCARD";
            }
        }
        //check length is 15
        //check for american express beginning and length
        else if ( (cc < 1000000000000000 && cc > 99999999999999) && (  floor(cc / 100000000000000) == 34 || floor(cc / 100000000000000) == 37) )
        {
            card = "AMEX";
        }
        //check length is 13
        else if ( (cc < 10000000000000 && cc > 100000000000) && floor(cc / 1000000000000000) == 4)
        {
            card = "VISA";
        }
    }
    else
    {
        card = "INVALID2";
    }
    return card;
}