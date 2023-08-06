#include <cs50.h>
#include <stdio.h>

/*
We have a population of n llamas.
Each year, n / 3 new llamas are born, and n / 4 llamas pass away.
*/

int getReachYear(int base,int target) {
    int n = 0;
    while (base < target) {
        base += base / 3 - base / 4;
        n++;
    }
    return n;
}


int main(void)
{
    // TODO: Prompt for start size
    int start;
    do {
        start = get_int("Start size: ");
    } while (start < 9);
    // TODO: Prompt for end size
    int end;
    do {
        end = get_int("End size: ");
    } while (end < start);

    // TODO: Calculate number of years until we reach threshold
    int years = getReachYear(start,end);


    // TODO: Print number of years
    printf("Years: %d \n",years);

    return 0;
}
