#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //make sure key is valid
    int len = strlen(argv[1]);

    if(len != 26 || argc != 2)
    {
        printf("Usage: ./cipher key\n");
        return 1;
    }

    for(int i = 0; i < len; i++)
    {
        if(!isalpha(argv[1][i]))
        {
           printf("Usage: ./cipher key\n");
           return 1;
           break;
        }
    }

    bool seen[26] = {false};

    //burda yardım aldım :(
    for(int h = 0; h < len; h++)
    {
        char c = toupper(argv[1][h]);
        int x = c - 'A';

        if(seen[x])
        {
            printf("Your key has duplicate letters!\n");
            return 1;
        }

        seen[x] = true;
    }

    // get the plaintext
    string text = get_string("plaintext:  ");
    int len2 = strlen(text);

    //print the ciphertext
    printf("ciphertext:  ");

    for(int q = 0; q < len2; q++)
    {
        if(isalpha(text[q]))
        {
            if(isupper(text[q]))
            {
                char r = (text[q]);
                int m = r - 'A';
                printf("%c",toupper(argv[1][m]));
            }
            else
            {
                char r2 = (text[q]);
                int m2 = r2 - 'a';
                printf("%c",tolower(argv[1][m2]));
            }
        }
        else
        {
            printf("%c",(text[q]));
        }
    }
    printf("\n");
    return 0;
}
