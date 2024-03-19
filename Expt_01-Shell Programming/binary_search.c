#include <stdio.h>

int main()
{
    int n = 2000;
    int a[n];
    for (int i=n; i >= 0; i--)
    {
        a[i]=i;
    }
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n-1; j++)
        {
            if (a[j] > a[j+1])
            {
                int t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }
        }
    }

    int s = 16, mid;
    int l = 0, c = 0, u = n-1;

    while (l <= u)
    {
        mid = (l+u)/2;
        if (s == a[mid])
        {
            c=1;
            break;
        }
        else if (s < a[mid]){
            u = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    if (c == 1)
    {
        printf("\nElement %d found art position %d", s, mid+1);
    }
    else{
        printf("\nElement not found");
    }
    return 0;
}