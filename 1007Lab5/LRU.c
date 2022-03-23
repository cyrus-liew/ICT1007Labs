#include<stdio.h>
void main()
{
    int pageNumbers[25], frameContents[25];
    int i = 0, j = 0, k = 0;
    int numPages = 0, numFrames = 0, totalPageFaults = 0;
    int min = 0, next = 1, check = 0, max, maxIndex = 0;
    int count[25], flag[25];

    printf("\n Page Replacement Method: LRU (Least Recently Used)\n");
    printf("\n Enter the number of pages in the page sequence: ");
    // 20
    scanf("%d", &numPages);

    printf("\n Enter the page numbers in sequence as a string: ");
    // 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
    for (i = 0; i < numPages; i++){
        scanf("%d", &pageNumbers[i]);
        flag[i] = 0;
    }

    printf("\n Enter the number of frames: ");
    // 3
    scanf("%d", &numFrames);

    for (i = 0; i < numFrames; i++){
        count[i] = 0;
        frameContents[i] = -1;
    }
    printf("\nThe Page Replacement process is\n");
    printf("\tREF STRING");

    for (j = 0; j < numFrames; j++)
        printf("\tPAGE_FRAME_%d", j + 1);

    printf("\tPAGE_FAULT_NUMBER\n");

    j = 0;
    for(i = 0; i < numPages; i++){
        check = 0;
        for(k = 0; k < numFrames; k++){
            flag[k]++;
        }

        printf("\t%d\t\t", pageNumbers[i]);
        if(j < 3){
            frameContents[j] = pageNumbers[i];
            flag[j] = 0;
            j++;
            for(k = 0; k < numFrames; k++){
                printf("%d\t\t", frameContents[k]);
            }
            totalPageFaults++;
            printf("%d\n", totalPageFaults);
            continue;
        }

        for(k = 0; k < numFrames; k++){
            if(frameContents[k] == pageNumbers[i]){
                for(int x = 0; x < numFrames; x++){
                    printf("%d\t\t", frameContents[x]);
                }
                flag[k] = 0;
                check = 1;
                printf("\n");
                break;
            }
        }
        if(check == 1){
            continue;
        }

        max = flag[0];
        maxIndex = 0;
        for(k = 0; k < numFrames; k++){
            if(flag[k] > max){
                    max = flag[k];
                    maxIndex = k;
                }
        }

        frameContents[maxIndex] = pageNumbers[i];
        flag[maxIndex] = 0;

        for(k = 0; k < numFrames; k++){
            printf("%d\t\t", frameContents[k]);
        }
        totalPageFaults++;
        printf("%d\n", totalPageFaults);
    }

    /* Find the occurance of page faults and the total number of page faults */
    printf("\n\n Total number of page faults using LRU: %d \n", totalPageFaults);
}