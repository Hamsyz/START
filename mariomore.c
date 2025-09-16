#include <stdio.h>
#include <cs50.h>

int main(void)

{   int height;
    int row = 1;
    int space;

    do
     {height = get_int("Height:");}
     while (height<=0);

      space = height-1;

     for(int n = 0; n < height; n++)
     {
       for(int l = 0; l < space; l++)
       {
        printf(" ");

       }   space--;

        for(int h = 0; h < row; h++)
        {
          printf("#");

        }
         printf(" ");

         for(int k = 0; k < row; k++)
        {
          printf("#");

        }
         printf("\n");
          row++;
     }
     printf("\n");
}
