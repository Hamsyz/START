#include <cs50.h>
#include <stdio.h>

int main (void)
{
int x = get_int("ilk sayıyı giriniz=>");
int y = get_int("ikinci sayıyı giriniz=>");
if (x < y)
printf("ikinci sayı birinciden büyük\n");
else if (x > y)
printf("birinci sayı ikinciden büyük\n");
else
printf("bu iki sayı eşit\n");

}
