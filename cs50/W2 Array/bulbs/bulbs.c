#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    string text = get_string("Message: ");

    for(int i = 0 , N = strlen(text); i < N; i++){
        char c = text[i];
        int bytes[BITS_IN_BYTE];
        for(int j = BITS_IN_BYTE - 1; j >= 0; j--){
            bytes[j] = c % 2;
            c = c / 2;
        }

        for(int k = 0; k < BITS_IN_BYTE; k++){
            print_bulb(bytes[k]);
        }

        printf("\n");
    }
}



void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
