#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

/*
key itself should be case-insensitive
ERROR
    executed without any command-line arguments or with more than one command-line argument: return 1
    If the key is invalid
        not containing 26 characters
        containing any character that is not an alphabetic character
        not containing each letter exactly once
preserve case
*/
void cipher_text(string text,string key);
int verify_key(string inputKey);

int main(int argc, string argv[])
{
    if(argc == 2){
        int status = verify_key(argv[1]);
        if(status > 0)
            return 1;
    } else {
        printf("without or more than 1 argument\n");
        return 1;
    }

    string text = get_string("plaintext: ");
    cipher_text(text,argv[1]);

    return 0;
}

void cipher_text(string text,string key){
    int N = strlen(text);
    char cipher[N+1];
    for(int i = 0; i < N; i++){
        char c = text[i];
        int idx;
        if(islower(c)){
            idx = c - 97;
            cipher[i] = tolower(key[idx]);
        } else if(isupper(c)){
            idx = c - 65;
            cipher[i] = toupper(key[idx]);
        } else {
            cipher[i] = c;
        }
    }
    cipher[N] = '\0';
    printf("ciphertext: %s\n",cipher);
}

int verify_key(string key){
        int N = strlen(key);
        if(N != 26){
            printf("not containing 26 characters\n");
            return 1;
        }

        int keyChk[26];
        for(int i = 0; i < N; i++){
            char c = toupper(key[i]);
            if(isupper(c)){
                int idx = c - 65;
                if(keyChk[idx] == 0)
                    keyChk[idx] = 1;
                else {
                    printf("not containing each letter exactly once\n");
                    return 1;
                }
            } else {
                printf("not alphabetic character\n");
                return 1;
            }
        }
        return 0;
}