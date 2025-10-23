#include <stdio.h>
#include <cs50.h>
int main(void)
void print_column(int )

{   int n= get_int("how big do you want the square:");
   for(int row = 0; row < n; row++)
   {
    for(int col=0; col< n; col++)
    {
      printf("#");
    }
    printf("\n");
   }
}
