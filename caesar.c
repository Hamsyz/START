#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{

    //print error message if needed
    if(argc != 2)
    {
        printf("You need to enter a proper key!\n");
        return 1;
    }

    //get the lenght of the number
    int len = strlen(argv[1]);

    for(int i = 0; i < len; i++)
    {
        int x = (isdigit(argv[1][i]));
        if(x == 0)
        {
            printf("You need to enter a proper key!\n");
            return 1;
            break;
        }
    }
     //convert string type key to int type key
    int key = atoi(argv[1]);
    key = key%26;

    //get the plaintext and its lenght
    string text1 = get_string("plaintext:  ");
    int len2 = strlen(text1);

    //loop
    for(int h = 0; h < len2; h++)
    {
        if(isalpha(text1[h]))
        {
           if(islower(text1[h]))
            {
                text1[h] = (text1[h] + key);
                if(text1[h] > 122)
                {
                    text1[h] = (text1[h])%123 + 97;
                }
            }
            else
            {
                text1[h] = (text1[h] + key);
                if(text1[h] > 90)
                {
                    text1[h] = (text1[h])%91 + 65;
                }
                //𝑐𝑖=(𝑝𝑖+𝑘) % 26 easier method
            }
        }
    }
    printf("%s\n",text1);
}
