#include <stdio.h>

int main(){
    int i = 0, numProc = 0, temp = 0;
    int burstTime[10], waitTime[10], turnArdTime[10], resTime[10];
    float totalWaitTime = 0, totalTurnArdTime = 0, totalResTime = 0;

    printf("\t CPU Scheduling Method: First Come First Serve \n");

    //read input
    printf("\n\t Enter the no of processes: "); 
    scanf("%d", &numProc); 
    for (i = 0; i < numProc; i++) 
    { 
        printf("\n\t Enter Burst Time for process %d: ", i + 1); 
        scanf("%d", &burstTime[i]); 
    }

    //main loop to calculate all the times
    for(i = 0; i < numProc; i++){
        //calculates turnaround time
        turnArdTime[i] = temp + burstTime[i];

        //calculate wait time
        waitTime[i] = turnArdTime[i] - burstTime[i];

        //calculate response time, since this is FCFS the response time = wait time
        resTime[i] = waitTime[i];

        //stores total burst time from the beginning of execution time
        temp = temp + burstTime[i];

        //calculate total time
        totalWaitTime = totalWaitTime + waitTime[i];
        totalTurnArdTime = totalTurnArdTime + turnArdTime[i];
        totalResTime = totalResTime + resTime[i];
    }

    printf("\n\t PROCESS\t BURST TIME\t WAITING TIME\t TURNAROUND TIME\t RESPONSE TIME\n"); 
    for (i = 0; i < numProc; i++) 
        printf("\t P%d \t\t %d \t\t %d \t\t %d \t\t\t %d \n",  
            i + 1, burstTime[i], waitTime[i], turnArdTime[i], resTime[i]); 
 

    printf("\n\t The Average Waiting time: %.2f\n", totalWaitTime / numProc); 
    printf("\n\t The Average Turnaround time: %.2f\n", totalTurnArdTime / numProc); 
    printf("\n\t The Average Response time: %.2f\n", totalResTime / numProc); 
 
    return 0;
}