#include <stdio.h>

int main(){
    int i = 0, j = 0, numProc = 0, timeSlice = 0, temp = 0, maxBurstTime = 0;
    int burstTime[10], backupBurstTime[10], waitTime[10], turnArdTime[10], resTime[10];
    float totalWaitTime = 0, totalTurnArdTime = 0, totalResTime = 0;

    printf("\t CPU Scheduling Method: Round Robin \n");

    //read input
    printf("\n\t Enter the no of processes: "); 
    scanf("%d", &numProc); 
    for (i = 0; i < numProc; i++) 
    { 
        printf("\n\t Enter Burst Time for process %d: ", i + 1); 
        scanf("%d", &burstTime[i]); 
        backupBurstTime[i] = burstTime[i]; 
    }

    printf("\n\t Enter the size of time slice: "); 
    scanf("%d", &timeSlice); 

    //find the highest burst time
    maxBurstTime = burstTime[0]; 
    for (i = 1; i < numProc; i++){ 
        if (maxBurstTime < burstTime[i]) 
            maxBurstTime = burstTime[i]; 
    } 

    //calculate turnaround time
    for (j = 0; j < (maxBurstTime / timeSlice) + 1; j++){ 
        for (i = 0; i < numProc; i++){ 
            if (burstTime[i] != 0){ 
                if (burstTime[i] <= timeSlice){ 
                    turnArdTime[i] = temp + burstTime[i]; 
                    temp = temp + burstTime[i]; 
                    burstTime[i] = 0; 
                } 
                else{ 
                    burstTime[i] = burstTime[i] - timeSlice; 
                    temp = temp + timeSlice; 
                } 
            } 
        } 
    }
    
    for (i = 0; i < numProc; i++){
        //calculate wait time
        waitTime[i] = turnArdTime[i] - backupBurstTime[i];

        //calculate response time
        resTime[i] = i * timeSlice;

        //calculate total time
        totalWaitTime = totalWaitTime + waitTime[i];
        totalTurnArdTime = totalTurnArdTime + turnArdTime[i];
        totalResTime = totalResTime + resTime[i];
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