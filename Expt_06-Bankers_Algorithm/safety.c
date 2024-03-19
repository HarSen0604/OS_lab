#include <stdio.h>

int main() 
{
    int n;
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);

    int m;
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int available[m];
    printf("Enter the available resources: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    int maximum[n][m];
    printf("\nEnter the maximum demand of each process: ");
    for (int i = 0; i < n; i++) {
        printf("\nFor process %d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }

    int allocation[n][m];
    int need[n][m];
    int finish[n];
    printf("\nEnter the allocated resources for each process: ");
    for (int i = 0; i < n; i++) {
        printf("\nFor process %d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
        finish[i] = 0;
    }

    int work[m];
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    int count = 0, orderOfProcesses[n];
    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) 
        {
            if (!finish[i]) 
            {
                int j;
                for (j = 0; j < m; j++) 
                {
                    if (need[i][j] < work[j]) 
                    {
                        break;
                    }
                }
                if (j == m) 
                {
                    for (int k = 0; k < m; k++) 
                    {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = 1;
                    orderOfProcesses[count] = i;
                    found = 1;
                    count++;
                }
            }
        }
        if (!found) {
            break;
        }
    }

    if (count == n) 
    {
        printf("\nThe system is in a safe state.\n");
        for (int i = 0; i < n; i++){
            printf("T%d\t", orderOfProcesses[i]);
        }
    } 
    else 
    {
        printf("\nThe system is in an unsafe state.\n");
    }
    return 0;
}
