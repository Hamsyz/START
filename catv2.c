#include <stdio.h>
#include <cs50.h>


  void miyav(int n);
  int get_positive_int(void);

  int main(void)
{    int times = get_positive_int();
     miyav(times);
}

int get_positive_int(void)
{
    int n;
    do
    {
    n = get_int("how many times do you want:");

    }
    while( n < 0 );
    return n;
}




void miyav(int n)
{
    for(int l = 0; l<n; l++)
    {
        printf("miyavvvvvv\n");

    }
}
