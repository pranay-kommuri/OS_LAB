
#include <stdio.h>
#include <stdlib.h>
#define MAX 10

int main(){
    int n, temp;
    int AT[MAX], BT[MAX], priority[MAX], CT[MAX], TAT[MAX], WT[MAX], RT[MAX], order[MAX];

    printf("\n -- PRIORITY(NON) CPU SCHEDULING PROGRAM --");
    printf("\n\n Enter the number of processes(max 10): ");
    scanf("%d", &n);

    if(n<1){
        printf("\n Number of processes is equal or lesser than 0. Exiting . . .\a\n\n\n");
        return 0;
    }if(n>MAX){
        printf("\n Number of processes is greater than 10. Exiting . . .\a\n\n\n");
        return 0;
    }

    printf("\n Enter the Arrival Times: \n");
    for(int i=0; i<n; i++){
        printf(" AT[%d]: ",(i+1));
        scanf("%d", &AT[i]);
    }

    printf("\n Enter the Burst Times: \n");
    for(int i=0; i<n; i++){
        printf(" BT[%d]: ",(i+1));
        scanf("%d", &BT[i]);
    }

    printf("\n Enter the Priorities: \n");
    for(int i=0; i<n; i++){
        printf(" Priority[%d]: ",(i+1));
        scanf("%d", &priority[i]);
        order[i] = i;
        CT[i] = 0;
    }

    //ORDER BY INCREASING ARRIVAL TIME
    for(int i=0; i<n; i++){
        for(int j=(n-1); j>i; j--){
            if(AT[j]<AT[i]){
                temp = AT[i]; AT[i] = AT[j]; AT[j] = temp;
                temp = BT[i]; BT[i] = BT[j]; BT[j] = temp;
                temp = order[i]; order[i] = order[j]; order[j] = temp;
    }   }   }

    int currentTime=0, minPriority, index;
    //Calculate CT, TAT, WT, RT
    for(int i=0; i<n; i++){

        //FINDING SHORTEST ARRIVED JOB
        minPriority = 9999;
        for(int j=0; j<n; j++){
            if(!CT[j] && AT[j]<=currentTime && priority[j]<minPriority){
                minPriority = priority[j];
                index = j;
            }
        }
        CT[index] = currentTime + BT[index];
        RT[index] = currentTime - AT[index];
        currentTime += BT[index];
        TAT[index] = CT[index] - AT[index];
        WT[index] = TAT[index] - BT[index];
    }

    //ORDER BACK
    for(int i=0; i<n; i++){
        for(int j=(n-1); j>i; j--){
            if(order[j]<order[i]){
                temp = AT[i]; AT[i] = AT[j]; AT[j] = temp;
                temp = BT[i]; BT[i] = BT[j]; BT[j] = temp;
                temp = priority[i]; priority[i] = priority[j]; priority[j] = temp;
                temp = CT[i]; CT[i] = CT[j]; CT[j] = temp;
                temp = TAT[i]; TAT[i] = TAT[j]; TAT[j] = temp;
                temp = WT[i]; WT[i] = WT[j]; WT[j] = temp;
                temp = RT[i]; RT[i] = RT[j]; RT[j] = temp;
                temp = order[i]; order[i] = order[j]; order[j] = temp;
    }   }   }

    //OUTPUT RESULTS CORRECTLY
    printf("\n\n\n -- RESULT TABLE -- \n\a");
    printf(" +-----------+------+------+------------+------+-------+------+------+\n");
    printf(" |  Process  |  AT  |  BT  |  Priority  |  CT  |  TAT  |  WT  |  RT  |\n");
    printf(" +-----------+------+------+------------+------+-------+------+------+\n");
    for(int i=0; i<n; i++){
        printf(" |  P%d\t     |%4d  |%4d  |%10d  |%4d  |%5d  |%4d  |%4d  |\n", (i+1), AT[i], BT[i], priority[i], CT[i], TAT[i], WT[i], RT[i]);
    }
    printf(" +-----------+------+------+------------+------+-------+------+------+\n");

    float avgTAT=0.0, avgWT=0.0, avgRT=0.0;
    for(int i=0; i<n; i++){
        avgTAT += TAT[i];
        avgWT += WT[i];
        avgRT += RT[i];
    }
    avgTAT /= n;
    avgWT /= n;
    avgRT /= n;

    printf("\n Average Turn-Around time(TAT): %.2f", avgTAT);
    printf("\n Average Waiting time(TAT): %.2f", avgWT);
    printf("\n Average Response time(TAT): %.2f\n\n", avgRT);
    return 0;
}
