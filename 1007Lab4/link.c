#include<stdio.h>  
#include<stdlib.h> 
 
#define TOTAL_DISK_BLOCKS 32 
#define TOTAL_DISK_INODES 8  
int blockStatus[TOTAL_DISK_BLOCKS]; // free = 0 
int blockList[TOTAL_DISK_BLOCKS - TOTAL_DISK_INODES]; // list of blocks of a file 
 
struct file_table {  
    char fileName[20];  
    int fileSize;  
    struct block *sb;  
}; 
struct file_table fileTable[TOTAL_DISK_BLOCKS - TOTAL_DISK_INODES]; 
 
struct block {  
    int blockNumber;  
    struct block *next;  
};  
 
int AllocateBlocks(int Size) { 
    int i = 0, count = 0, checkBlock = 0; 
    int allocStartBlock = TOTAL_DISK_INODES; 
    int allocEndBlock = TOTAL_DISK_BLOCKS - 1; 
 
    // check whether sufficient free blocks are available 
    for (i = 0; i < (TOTAL_DISK_BLOCKS - TOTAL_DISK_INODES); i++) 
        if (blockStatus[i] == 0) 
            count++; 
    if (count < Size) 
        return 1;  // not enough free blocks

    count = 0;
    i = 0;
    while(count < Size){
        checkBlock = (rand() % (allocEndBlock - allocStartBlock + 1)) + allocStartBlock;
        if(blockStatus[checkBlock] == 0){
            blockList[i] = checkBlock;
            blockStatus[checkBlock] = 1;
            count++;
            i++;
        }
    }

    return 0;
    
} 
 
int main()  
{  
    int i = 0, j = 0, numFiles = 0, nextBlock= 0, ret = 1;  
    char s[20]; struct block *temp = NULL; struct block *head = NULL; struct block *new = NULL;
    head = malloc(sizeof(struct block));
    temp = malloc(sizeof(struct block));
    new = malloc(sizeof(struct block));
    
    printf("File allocation method: LINKED LIST\n");
    printf("Totla blocks: 32\n");
    printf("File allocation start t block: 8\n");
    printf("File allocation end at block: 31\n");
    printf("Size (kB) of each block: 1\n\n");

    printf("Enter no of files: ");
    scanf("%d", &numFiles);

    for(i = 0; i< numFiles; i++){
        printf("\nEnter the name of file #%d: ", i + 1);
        scanf("%19s", fileTable[i].fileName);
        printf("\nEnter the size (kB) of file #%d:", i + 1);
        scanf("%d", &fileTable[i].fileSize);
    }

    for(i = 0; i < numFiles; i++) {  
      
        ret = AllocateBlocks(fileTable[i].fileSize); 
        
        if (ret == 1){
            return 0;
        }
        else{
            head->blockNumber = blockList[0];
            head->next = NULL;
            for(j = 1; j < fileTable[i].fileSize; j++){
                new->blockNumber = blockList[j];
                new->next = NULL;
                temp = head;

                while(temp->next != NULL){
                    temp = temp->next;
                }

                temp->next = new;
            }

            fileTable[i].sb = head;
            

        }
      
    } 
    
    printf("FILE_fileName\tFILE_SIZE\tBLOCKS_OCCUPIED\n");

    for(i = 0; i < numFiles; i++){
        printf("%s\t%d\t", fileTable[i].fileName, fileTable[i].fileSize);
        temp = fileTable[i].sb;
        //while(temp->next != NULL){
            printf("-%d", temp->blockNumber);
            temp = temp->next;
        //}
        printf("\n");
    }

    printf("File allocation completed. Exiting.");

//Seed the pseudo-random number generator used by rand() with the value seed 
srand(1234); 

}