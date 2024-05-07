#include<stdio.h>

int max(int x, int y)
{
  return (x > y) ? x : y;
}

int main(){
    //at, bt
    //ct, tat, wt
    //tat = ct - at         wt = tat - bt
    //response time

    int n;
    printf("Enter no. of processes: ");
    scanf("%d",&n);

    int pid[n], at[n], bt[n];
    for(int i=0;i<n;i++){
        pid[i] = i+1;

        printf("Enter AT of process %d: ", i+1);
        scanf("%d",&at[i]);
    
        printf("Enter BT of process %d: ", i+1);
        scanf("%d",&bt[i]);
    }

    //sorting the array
    for(int i=0;i<n;i++){
        for(int j=0;j<n-1;j++){
            if(at[j]>at[j+1]){
                int temp = at[j];
                at[j]=at[j+1];
                at[j+1]=temp;

                temp = bt[j];
                bt[j]=bt[j+1];
                bt[j+1]=temp;

                temp = pid[j];
                pid[j]=pid[j+1];
                pid[j+1]=temp;
            }
        }
    }

    //writing algo
    int ct[n], tat[n], wt[n];
    int curr = 0;
    for(int i=0;i<n;i++){
        ct[i] = max(at[i], curr) + bt[i];
        curr = ct[i];

        tat[i] = ct[i]-at[i];
        wt[i] = tat[i]-bt[i];
    }
    //printing
    printf("Pid    AT    BT    CT    TAT    WT\n");
    for(int i=0;i<n;i++){
        printf("P%d    %d    %d    %d    %d    %d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    float avgtat=0;
    float avgwt=0;
    for(int i=0;i<n;i++){
        avgtat=avgtat+tat[i];
        avgwt=avgwt+wt[i];
    }
    avgtat=(avgtat*1.0)/n;
    avgwt=(avgwt*1.0)/n;
    printf("Average TAT: %f\n", avgtat);
    printf("Average WT: %f\n", avgwt);

    return 0;
}