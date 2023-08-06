#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define ALPHABET 26
#define DECIMAL 10

int to_int(string str);
void cipher_text(string text,int num);

int main(int argc, string argv[])
{
    int num;
    if(argc == 2){
        num = to_int(argv[1]);
        if(num == -1)
            return 1;
    } else {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string text = get_string("plaintext: ");

    cipher_text(text,num);
}

int to_int(string str) {
    int result = 0;
    int m = 1;
    for(int i = strlen(str) -1; i >= 0; i--) {
        if(isdigit(str[i])) {
            int d = str[i] - '0';
            result += d * m;
            m *= DECIMAL;
        } else {
            return -1;
        }
    }
    return result;
}

void cipher_text(string text,int num) {
    int k = num % ALPHABET;
    int N = strlen(text);
    char cipher[N+1];

    for(int i = 0; i < N; i++){
        char c = text[i];

        if(islower(c)) {
            int idx = c - 'a';
            int idx_new = (idx + k) % ALPHABET;
            cipher[i] = 'a' + idx_new;
        }
        else if(isupper(c)) {
            int idx = c - 'A';
            int idx_new = (idx + k) % ALPHABET;
            cipher[i] = 'A' + idx_new;
        } else {
            cipher[i] = c;
        }
    }

    cipher[N] = '\0';
    printf("ciphertext: %s\n",cipher);
}