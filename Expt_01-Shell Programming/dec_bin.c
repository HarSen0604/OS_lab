#include <stdio.h>

int main()
{
    int deci = 100;
    int l[20],i=0;
    while(deci>0)
    {
        l[i]=deci%2;
        deci=deci/2;
        i++;
    }
    printf("\nBinary equivalent is: ");
    for(i=i-1;i>=0;i--)
    {
        printf("%d",l[i]);
    }
    return 0;
}