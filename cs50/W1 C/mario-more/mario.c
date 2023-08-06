#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do {
        n = get_int("Height: ");
    } while (n <= 0 || n > 8);

    for(int i = 1; i <= n; i++)
    {
        int spaces = n - i;
        for(int j = 1 ; j <= n; j++)
        {
            if(j <= spaces)
                printf(" ");
            else
                printf("#");
        }

        printf("  ");

        for(int k = 1; k <= i ; k++) {
            printf("#");
        }

        printf("\n");
    }

}