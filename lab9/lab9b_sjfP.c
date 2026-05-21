/*Implement  the  following  CPU  scheduling  algorithms  by  defining  the 
process structure: 
a. SJF 
b. SJF (Preemptive)
*/

//b) SJF (Preemptive)

#include <stdio.h>

typedef struct process {
    int processId;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
    int responseTime;
} Process;

void sjfPreemptive(Process[], int);

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Accept process details from the user
    for (int i = 0; i < n; i++) {
        printf("Process %d\n", i + 1);
        printf("Enter Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter Burst Time: ");
        scanf("%d", &processes[i].burstTime);
        processes[i].processId = i + 1;
        processes[i].remainingTime = processes[i].burstTime;  // Copy of burst time
        printf("\n");
    }

    sjfPreemptive(processes, n);
    return 0;
}

void sjfPreemptive(Process processes[], int n) {
    int timeProgress[100], processTrack[100], j = -1, k = -1;
    float avgWaitingTime = 0;
    float avgTurnAroundTime = 0;
    float avgResponseTime = 0;
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;
    int totalResponseTime = 0;
    int elapsedTime = 0;
    int remainingProcesses = n;

    timeProgress[++j] = 0;

    while (remainingProcesses > 0) {
        int exec = -1;
        int shortestBurstTime = 9999;

        // Find process with shortest remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= elapsedTime && 
                processes[i].remainingTime > 0) {
                if (processes[i].remainingTime < shortestBurstTime) {
                    shortestBurstTime = processes[i].remainingTime;
                    exec = i;
                }
            }
        }

        if (exec == -1) {
            // Idle time
            processTrack[++k] = 0;
            elapsedTime++;
            timeProgress[++j] = elapsedTime;
            continue;
        }

        // Record response time for first execution
        if (processes[exec].remainingTime == processes[exec].burstTime) {
            processes[exec].responseTime = elapsedTime - processes[exec].arrivalTime;
        }

        // Execute for 1 unit time
        processes[exec].remainingTime--;
        elapsedTime++;

        processTrack[++k] = processes[exec].processId;
        timeProgress[++j] = elapsedTime;

        // If process completed
        if (processes[exec].remainingTime == 0) {
            processes[exec].completionTime = elapsedTime;
            processes[exec].turnAroundTime = processes[exec].completionTime - processes[exec].arrivalTime;
            processes[exec].waitingTime = processes[exec].turnAroundTime - processes[exec].burstTime;

            totalTurnAroundTime += processes[exec].turnAroundTime;
            totalWaitingTime += processes[exec].waitingTime;
            totalResponseTime += processes[exec].responseTime;
            remainingProcesses--;
        }
    }

    // Print Observation Table
    printf("\nObservation Table\n");
    printf("PID\tAT\tBT\tCT\tTT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].processId,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].completionTime,
               processes[i].turnAroundTime,
               processes[i].waitingTime,
               processes[i].responseTime);
    }

    // Clean Gantt Chart
    printf("\nGantt Chart\n(P0 --> idle time)\n");

    printf("| P%d\t", processTrack[0]);

    int prev = processTrack[0];

    for (int i = 1; i <= k; i++) {
        if (processTrack[i] != prev) {
            printf("| P%d\t", processTrack[i]);
            prev = processTrack[i];
        }
    }
    printf("|\n");

    // Print corresponding times
    printf("%d\t", timeProgress[0]);

    prev = processTrack[0];

    for (int i = 1; i <= k; i++) {
        if (processTrack[i] != prev) {
            printf("%d\t", timeProgress[i]);
            prev = processTrack[i];
        }
    }

    printf("%d\n", timeProgress[j]);

    // Print Averages
    avgTurnAroundTime = (float)totalTurnAroundTime / n;
    avgWaitingTime = (float)totalWaitingTime / n;
    avgResponseTime = (float)totalResponseTime / n;

    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnAroundTime);
    printf("Average Response Time: %.2f\n", avgResponseTime);
}