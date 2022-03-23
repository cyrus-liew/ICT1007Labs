#include <stdio.h>
void main()
{
    int pageNumbers[25], frameContents[25];
    int i = 0, j = 0, k = 0, x= 0, check = 0;
    int numPages = 0, numFrames = 0, totalPageFaults = 0;
    int frameNumber = 0;

    printf("\n Page Replacement Method: FIFO");
    printf("\n Enter the number of pages in the page sequence: ");
    // 20
    scanf("%d", &numPages);

    printf("\n Enter the page numbers in sequence as a string: ");
    // 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
    for (i = 0; i < numPages; i++)
        scanf("%d", &pageNumbers[i]);

    printf("\n Enter the number of frames: ");
    // 3
    scanf("%d", &numFrames);
    for (i = 0; i < numFrames; i++)
        frameContents[i] = -1;

    printf("\n The Page Replacement Process is \n");
    printf("\tREF STRING");
    for (j = 0; j < numFrames; j++)
        printf("\tPAGE_FRAME_%d", j + 1);

    printf("\tPAGE_FAULT_NUMBER\n");
    /* Find the occurance of page faults and the total number of page faults */

    j = 0;
    for(i = 0; i < numPages; i++){
        check = 0;
        if(j > 2){
            j = 0;
        }
        printf("\t%d\t\t", pageNumbers[i]);
        for(k = 0; k < numFrames; k++){
            if(frameContents[k] == pageNumbers[i]){
                check = 1;
                for(x = 0; x < numFrames; x++){
                    printf("%d\t\t", frameContents[x]);
                }
                printf("\n");
                break;
            }
        }
        if(check == 1){
            continue;
        }

        frameContents[j] = pageNumbers[i];
        for(k = 0; k < numFrames; k++){
            printf("%d\t\t", frameContents[k]);
        }
        totalPageFaults++;
        j++;
        printf("%d\n", totalPageFaults);

    }

    printf("\n\n Total number of Page Faults using FIFO: %d \n", totalPageFaults);
}