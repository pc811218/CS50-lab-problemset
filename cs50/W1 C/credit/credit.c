#include <cs50.h>
#include <stdio.h>
#include <math.h>

bool checkSum(long n);

int main(void)
{

    long cardNo;
    //get card number
    do {
        cardNo = get_long("Number: ");
    } while (cardNo < 0);

    //AMEX
    long dAMEX = cardNo / (long) pow(10,15-2);
    if(dAMEX == 34 || dAMEX == 37) {
        if(checkSum(cardNo)){
            printf("AMEX\n");
            return 0;
        }
    }

    //MASTERCARD
    long dMASTERCARD = cardNo / (long) pow(10,16-2);
    if(dMASTERCARD >= 51 && dMASTERCARD <= 55) {
       if(checkSum(cardNo)){
            printf("MASTERCARD\n");
            return 0;
        }
    }

    //VISA
    long dVISA;
    if(cardNo < (long) pow(10,16-1))
        dVISA = cardNo / (long) pow(10,13-1);
    else
        dVISA = cardNo / (long) pow(10,16-1);

    if(dVISA == 4) {
        if(checkSum(cardNo)){
            printf("VISA\n");
            return 0;
        }
    }

    printf("INVALID\n");
    return 0;
}

bool checkSum(long n) {
    int sum = 0;
    bool isValid = false;
    bool isMultiply = false;

    while(n > 0){
        int digit = n % 10;

        if(isMultiply){
            digit *= 2;
            sum += digit / 10 + digit % 10;
        } else {
            sum += digit;
        }

        n = n / 10;
        isMultiply = !isMultiply;
    }

    //valid when sum ends with 0
    if (sum % 10 == 0)
        isValid = true;

    return isValid;
}