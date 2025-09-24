#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int sentence = 0;
//words = spaces + 1
int words = 1;
int letters = 0;

int main(void)
{
    //get the text
    string text =get_string("text:");

    //count the len
    int len = strlen(text);


     for(int i = 0; i < len; i++)
    {
     //count the sentences
        if(text[i] == '!' || text[i] =='?' || text[i] == '.' )
        {
            sentence ++;
        }

     //count the words
        if(isblank(text[i]))
        {
            words ++;
        }

    //count the letters
        if(isalpha(text[i]))
        {
            letters++;
        }
      }

    //compute L and S and index
    float L = ((double) letters * 100) / (double)words;
    float S = ((double) sentence * 100) / (double)words;
    float index = (0.0588 * L - 0.296 * S - 15.8);

    int grade = (int) round(index);

    // print the index
    if (grade<1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade>16)
    {
        printf("Grade 16+\n");
    }

    else
    {
        printf("Grade %i\n",grade);
    }
}
