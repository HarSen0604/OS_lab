#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOW 2
#define HIGH 9

int random_number()
{
    srand(time(NULL));
    return (rand() % (HIGH - LOW + 1) + LOW);
}

int John(int p, int n)
{
    if (!(p >= n))
    {
        p *= random_number();
        printf("John: %d\n", p);
        return p;
    }
    return -1;
}

int Michael(int p, int n)
{
    if (!(p >= n))
    {
        p *= random_number();
        printf("Michael: %d\n", p);
        return p;
    }
    return -1;
}

int main()
{
    int p = 1, n, chance = 0;
    scanf("%d", &n);
    
    while (!(p >= n))
    {
        if (chance % 2 != 0)
            p = Michael(p, n);
        else            
            p = John(p, n);
        chance++;
    }
    (chance % 2 == 0) ? printf("Michael won!\n") : printf("John won!\n");
    return 0;
}