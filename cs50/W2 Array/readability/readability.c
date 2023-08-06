#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int get_index(string text);
int calc_index(int letters,int words,int sentences);

int main(void)
{
    string text = get_string("Text: ");
    int index = get_index(text);

    if(index < 1)
        printf("Before Grade 1");
    else if(index >= 16)
        printf("Grade 16+");
    else
        printf("Grade %d",index);

    printf("\n");

    return 0;
}

int get_index(string text){
    int letters = 0, words = 1, sentences = 0;

    for(int i = 0 , N = strlen(text); i < N; i++){
        char c = toupper(text[i]);
        if(isupper(c)){
            letters++;
        } else if(c == ' ') {
            words++;
        } else if(c == '.' || c == '!' || c == '?'){
            sentences++;
        }
    }

    int index = calc_index(letters,words,sentences);

    return index;
}

int calc_index(int letters,int words,int sentences){
    float L = letters / (float) words * 100;
    float S = sentences / (float) words * 100;

    int index = round(0.0588 * L - 0.296 * S - 15.8);

    return index;
}