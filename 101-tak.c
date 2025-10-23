#include <stdio.h>
#include <cs50.h>

int main(void)
{
    char c = get_char("onaylıyorsanız e'ye basın onaylamıyorsanız h'ye basın:");
   if (c == 'e' || c =='E')
   {
      printf("onaylandı\n");
   }
   else if (c == 'h' || c =='H')
   {
      printf("onaylanmadı\n");
   }
}
