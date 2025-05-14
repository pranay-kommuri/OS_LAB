#include <stdio.h>
#include <stdlib.h>
#define MAX 10

int main(){
    int n, temp;
    int AT[MAX], BT[MAX], CT[MAX], TAT[MAX], WT[MAX], RT[MAX], order[MAX];

    printf("\n -- FCFS CPU SCHEDULING PROGRAM --");
    printf("\n\n Enter the number of processes(max 10): ");
    scanf("%d", &n);

    if(n<1){
        printf("\n Number of processes is equal or lesser than 0. Exiting . . .\n\n\n");
        return 0;
    }if(n>MAX){
        printf("\n Number of processes is greater than 10. Exiting . . .\n\n\n");
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
        order[i] = i;
    }

    //ORDER BY FIRST ARRIVAL TIME
    for(int i=0; i<n; i++){
        for(int j=(n-1); j>i; j--){
            if(AT[j]<AT[i]){
                temp = AT[i]; AT[i] = AT[j]; AT[j] = temp;
                temp = BT[i]; BT[i] = BT[j]; BT[j] = temp;
                temp = order[i]; order[i] = order[j]; order[j] = temp;
    }   }   }

    //Calculate CT
    for(int i=0; i<n; i++){
        if(CT[i-1]>AT[i] && i){
            CT[i] = CT[i-1] + BT[i];
            RT[i] = CT[i-1] - AT[i];
        }else{
            CT[i] = AT[i] + BT[i];
            RT[i] = 0;
        }
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];
    }

    //ORDER BACK
    for(int i=0; i<n; i++){
        for(int j=(n-1); j>i; j--){
            if(order[j]<order[i]){
                temp = AT[i]; AT[i] = AT[j]; AT[j] = temp;
                temp = BT[i]; BT[i] = BT[j]; BT[j] = temp;
                temp = CT[i]; CT[i] = CT[j]; CT[j] = temp;
                temp = TAT[i]; TAT[i] = TAT[j]; TAT[j] = temp;
                temp = WT[i]; WT[i] = WT[j]; WT[j] = temp;
                temp = RT[i]; RT[i] = RT[j]; RT[j] = temp;
                temp = order[i]; order[i] = order[j]; order[j] = temp;
    }   }   }

    //OUTPUT RESULTS CORRECTLY
    printf("\n\n\n -- RESULT TABLE -- \n\a");
    printf(" +-----------+------+------+------+-------+------+------+\n");
    printf(" |  Process  |  AT  |  BT  |  CT  |  TAT  |  WT  |  RT  |\n");
    printf(" +-----------+------+------+------+-------+------+------+\n");
    for(int i=0; i<n; i++){
        printf(" |  P%d\t     |%4d  |%4d  |%4d  |%5d  |%4d  |%4d  |\n", (i+1), AT[i], BT[i], CT[i], TAT[i], WT[i], RT[i]);
    }
    printf(" +-----------+------+------+------+-------+------+------+\n\n");

    return 0;
}
