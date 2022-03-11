#include<stdio.h>  
#include<stdlib.h>  
 
#define TOTAL_DISK_BLOCKS 32 
#define TOTAL_DISK_INODES 8  
#define BLOCK_SIZE 2
int blockStatus[TOTAL_DISK_BLOCKS]; // free = 0  
int blockStart; 
 
struct file_table {  
    char fileName[20];  
    int startBlock; 
    int fileSize;
    int numBlocks;
    int allotStatus; 
}; 
struct file_table fileTable[TOTAL_DISK_BLOCKS - TOTAL_DISK_INODES]; 
 
int AllocateBlocks(int Size) { 
    int i = 0, count = 0, inList = 0, nextBlock = 0; 
    int allocStartBlock = TOTAL_DISK_INODES; 
    int allocEndBlock = TOTAL_DISK_BLOCKS - 1; 
 
    // check whether sufficient free blocks are available 
    for (i = 0; i < (TOTAL_DISK_BLOCKS - TOTAL_DISK_INODES); i++) 
        if (blockStatus[i] == 0) 
            count++; 
    if (count < Size) 
        return 1;  // not enough free blocks     
 
    count = 0; 
    while (count < Size) { 
        nextBlock = (rand() % (allocEndBlock - allocStartBlock + 1)) + allocStartBlock;  
        for (i = nextBlock; i < (nextBlock + Size); i++) 
        { 
            if (blockStatus[i] == 0) 
                count = count + 1; 
            else { 
                count = 0; 
                break; 
            } 
        }  
    }             
    blockStart = nextBlock; 
 
    if (count == Size)  
        return 0; // success 
    else 
        return 1; // not successful 
} 
 
int main()  
{  
    int i =0, j = 0, numFiles = 0, nextBlock = 0, ret = 1;  
    char s[20];  
    //Seed the pseudo-random number generator used by rand() with the value seed 
    srand(654); 
    
    printf("File allocation method: SEQUENTIAL\n");
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

        if(fileTable[i].fileSize % BLOCK_SIZE == 0){
            fileTable[i].numBlocks = fileTable[i].fileSize / BLOCK_SIZE;
        }
        else{
            fileTable[i].numBlocks = fileTable[i].fileSize / BLOCK_SIZE + 1;
        }
    }

    for(i = 0; i < numFiles; i++) {  
      
      ret = AllocateBlocks(fileTable[i].numBlocks); 
      
      if (ret == 1){
          return 0;
      }
      else{
          fileTable[i].startBlock = blockStart;
          for(j = blockStart; j < blockStart + fileTable[i].numBlocks; j++){
              blockStatus[j] = 1;
          }
      }
      
    } 

    printf("FILE_fileName\tFILE_SIZE\tBLOCKS_OCCUPIED\n");

    for(i = 0; i < numFiles; i++){
        printf("%s\t\t%d\t\t%d", fileTable[i].fileName, fileTable[i].fileSize, fileTable[i].startBlock);
        for(j = 1; j < fileTable[i].numBlocks; j++){
            printf("-%d", fileTable[i].startBlock + j);
        }
        printf("\n");
    }

    printf("File allocation completed. Exiting.");



return 0;
}