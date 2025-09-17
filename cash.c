#include <stdio.h>
#include <cs50.h>


int main (void)
{ int change;
    do
    {change = get_int("Change owed:");}
    while(change < 0);

    int quarter = change/25;
    change = change%25;

    int ten = change/10;
    change = change%10;

    int five = change/5;
    change = change%5;

    int penny = change;

    int number = quarter + ten + five + penny;
    printf("%i\n",number);
}
