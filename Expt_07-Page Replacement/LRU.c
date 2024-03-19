#include <stdio.h>
#include <stdbool.h>

int main()
{
    int numFrames = 0;
    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);
    int page[numFrames];

    //initializing
    for (int i = 0; i < numFrames; i++)
        page[i] = -1;

    int numReferences = 0;
    printf("Enter the number of references: ");
    scanf("%d", &numReferences);

    //reference string
    int referenceString[numReferences];
    printf("Enter the reference string: ");
    for (int i = 0; i < numReferences; i++)
        scanf("%d", &referenceString[i]);
    
    int numPageFault = 0;
    for (int i = 0; i < numReferences; i++)
    {
        bool check = true;
        for (int j = 0; j < numFrames; j++)
        {
            if (page[j] == referenceString[i])
            {
                check = false;
                printf("Exists\n");
                break;
            }
        }
        if (check)
        {
            numPageFault++;
            int j;
            for (j = 0; j < numFrames; j++)
            {
                if (page[j] == -1)
                {
                    page[j] = referenceString[i];
                    break;
                }
            }
            if (j == numFrames)
            {
                int maxDistance = -1, index = -1;
                for (int k = 0; k < numFrames; k++)
                {
                    int distance = 0; 
                    for (int l = i - 1; l >= 0; l--)
                    {
                        distance++;
                        if (page[k] == referenceString[l])
                        {
                            break;
                        }
                    }
                    if (distance > maxDistance)
                    {
                        maxDistance = distance;
                        index = k;
                    }
                }
                page[index] = referenceString[i];
            }
            for (int k = 0; k < numFrames; k++)
            {
                printf("%d ", page[k]);
            }
            printf("\n");
        }
    }
    printf("\nNumber of page faults: %d", numPageFault);
    return 0;
}
//7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1