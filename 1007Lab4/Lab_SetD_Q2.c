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
            //printf("%d ", blockList[i]);
            count++;
            i++;
        }
    }

    return 0;
    
} 
 
int main()  
{  
    int i = 0, j = 0, numFiles = 0, nextBlock= 0, ret = 1;  
    char s[20];
    struct block *temp = (struct block*) malloc(sizeof(struct block)); 
    struct block *head = (struct block*) malloc(sizeof(struct block));
    blockStatus[11] = 1;
    blockStatus[12] = 1;
    blockStatus[13] = 1;
    srand(654); 
    
    printf("File allocation method: LINKED LIST\n");
    printf("Total blocks: 32\n");
    printf("File allocation start at block: 8\n");
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
        printf("\n");
        
        if (ret == 1){
            return 0;
        }
        else{
            head = NULL;
            for(j = 0; j < fileTable[i].fileSize; j++){
                struct block *new = (struct block*) malloc(sizeof(struct block));
                new->blockNumber = blockList[j];
                new->next = NULL;

                if(head == NULL){
                    head = new;
                    continue;
                }

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
        printf("%s\t\t%d\t\t%d", fileTable[i].fileName, fileTable[i].fileSize, fileTable[i].sb->blockNumber);
        temp = fileTable[i].sb->next;
        while(temp != NULL){
            printf("-%d", temp->blockNumber);
            temp = temp->next;
        }
        printf("\n");
    }

    printf("File allocation completed. Exiting.");


return 0;

}