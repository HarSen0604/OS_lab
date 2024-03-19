#include <stdio.h>

int main()
{
    int n = 2000;
    int a[n];
    for (int i = 0; i <= n; i++)
    {
        a[i] = i;
    }
    int item = 21;
    int j = 0;
    while (j < n && item != a[j])
    {
        j++;
    }

    if (item == a[j])
    {
        printf("%d is present at location %d", item, (j+1));
    }
    else
    {
        printf("%d is not present in the array", item);
    }
}