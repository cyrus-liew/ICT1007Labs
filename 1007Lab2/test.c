#include<stdio.h>
#include<string.h>
#include<stdlib.h>
 
int main()
{
    int count,j,n,time,remain,flag=0,time_quantum;
    int wait_time=0,turnaround_time=0;
    
    FILE *file;
    char buff[10], c;
    const char s[2] = " ";
    char *token;

    file = fopen("./data.txt", "r");
    if(file == NULL){
        printf("Could not open file");
        return 0;
    }

    for (c = getc(file); c != EOF; c = getc(file)){
        if (c == '\n'){ // Increment count if this character is newline
            count = count + 1;
            //printf("%d", count);
         }
    }

    int at[count], bt[count], rt[count];
    count = 0;

    fclose(file);
    file = fopen("./data.txt", "r");
    if(file == NULL){
        printf("Could not open file");
        return 0;
    }

    while(fgets(buff, 10, file)){
        //printf("%s", buff);
        buff[strcspn(buff, "\n")] = 0;
        token = strtok(buff, s);
        at[count] = atoi(token);
        token = strtok(NULL, s);
        printf("%s", token);
        bt[count] = atoi(token);
        //printf("%d %d", at[count], bt[count]);
        count++;
    }

    fclose(file);
    //printf("%d", bt[4]);
    /*
    printf("Enter Total Process:\t ");
    scanf("%d",&n);
    remain=n;
    for(count=0;count<n;count++)
    {
        printf("Enter Arrival Time and Burst Time for Process Process Number %d :",count+1);
        scanf("%d",&at[count]);
        scanf("%d",&bt[count]);
        rt[count]=bt[count];
    }
    printf("Enter Time Quantum:\t");
    scanf("%d",&time_quantum);
    printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n");
    for(time=0,count=0;remain!=0;)
    {
        if(rt[count]<=time_quantum && rt[count]>0)
        {
        time+=rt[count];
        rt[count]=0;
        flag=1;
        }
        else if(rt[count]>0)
        {
        rt[count]-=time_quantum;
        time+=time_quantum;
        }
        if(rt[count]==0 && flag==1)
        {
        remain--;
        printf("P[%d]\t|\t%d\t|\t%d\n",count+1,time-at[count],time-at[count]-bt[count]);
        wait_time+=time-at[count]-bt[count];
        turnaround_time+=time-at[count];
        flag=0;
        }
        if(count==n-1)
        count=0;
        else if(at[count+1]<=time)
        count++;
        else
        count=0;
    }
    printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n);
    printf("Avg Turnaround Time = %f",turnaround_time*1.0/n);
    */
    return 0;
}
