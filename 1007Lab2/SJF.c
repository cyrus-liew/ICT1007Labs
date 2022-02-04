#include <stdio.h>

int main(){
    int i = 0, numProc = 0, temp = 0, loc = 0, max = 0;
    int burstTime[10], waitTime[10], turnArdTime[10], resTime[10], backupBurstTime[10];
    float totalWaitTime = 0, totalTurnArdTime = 0, totalResTime = 0;

    printf("\t CPU Scheduling Method: Shortest Job First \n");

    //read input
    printf("\n\t Enter the no of processes: "); 
    scanf("%d", &numProc); 
    for (i = 0; i < numProc; i++) 
    { 
        printf("\n\t Enter Burst Time for process %d: ", i + 1); 
        scanf("%d", &burstTime[i]); 
        backupBurstTime[i] = burstTime[i];
    }

    //find highest value in queue
    for(int i = 0; i < numProc; i++){
        if(burstTime[i] > burstTime[loc]){
            loc = i;
        }
    }
    max = burstTime[loc] + 1;
    loc = 0;

    for(int j = 0; j < numProc; j++){
        //find shortest burst time
        for (int i = 1; i < numProc; i++){
            if(burstTime[i] < burstTime[loc]){
                loc = i;
            }
        }

        //calculate turnaround time
        turnArdTime[loc] = temp + backupBurstTime[loc];

        //store total time so far
        temp = temp + backupBurstTime[loc];

        //calculate wait time
        waitTime[loc] = turnArdTime[loc] - backupBurstTime[loc];

        //calculate response time, since this is SJF the response time = wait time
        resTime[loc] = waitTime[loc];

        //remove task from queue by setting it to highest val
        burstTime[loc] = max;

        //calculate totals
        totalResTime = totalResTime + resTime[loc];
        totalTurnArdTime = totalTurnArdTime + turnArdTime[loc];
        totalWaitTime = totalWaitTime + waitTime[loc];

        loc = 0;
    }

    printf("\n\t PROCESS\t BURST TIME\t WAITING TIME\t TURNAROUND TIME\t RESPONSE TIME\n"); 
    for (i = 0; i < numProc; i++) 
        printf("\t P%d \t\t %d \t\t %d \t\t %d \t\t\t %d \n",  
            i + 1, backupBurstTime[i], waitTime[i], turnArdTime[i], resTime[i]); 
 

    printf("\n\t The Average Waiting time: %.2f\n", totalWaitTime / numProc); 
    printf("\n\t The Average Turnaround time: %.2f\n", totalTurnArdTime / numProc); 
    printf("\n\t The Average Response time: %.2f\n", totalResTime / numProc); 
 
    return 0;
}