#include <stdio.h>
#include <limits.h>
#include <string.h>

// Input validation
int getPositiveInt(char *prompt) {
    int num;
    char term;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d%c", &num, &term) != 2 || term != '\n' || num <= 0) {
            printf("Invalid input! Enter a positive integer.\n");
            while(getchar()!='\n');
        } else return num;
    }
}
int getNonNegativeInt(char *prompt) {
    int num;
    char term;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d%c", &num, &term) != 2 || term != '\n' || num < 0) {
            printf("Invalid input! Enter a non-negative integer.\n");
            while(getchar()!='\n');
        } else return num;
    }
}
// Print Gantt Chart
void printGantt(int n,int *proc,int *start,int *finish){
    printf("\nGantt Chart:\n|");
    for(int i=0;i<n;i++) printf("  P%-2d  |",proc[i]+1);
    printf("\n");
    for(int i=0;i<n;i++){
        if(i==0) printf("%-7d",start[i]);
        printf("%-7d",finish[i]);
    }
    printf("\n");
}
// FCFS
void fcfs(){
    int n=getPositiveInt("Enter number of processes: ");
    int at[20],bt[20],start[20],finish[20],wt[20],tat[20],order[20];
    for(int i=0;i<n;i++){
        char temp[50];
        sprintf(temp,"Process %d Arrival Time: ",i+1);
        at[i]=getNonNegativeInt(temp);
        sprintf(temp,"Process %d CPU Burst Time: ",i+1);
        bt[i]=getNonNegativeInt(temp);
        order[i]=i;
    }
    start[0]=(at[0]>0)?at[0]:0;
    finish[0]=start[0]+bt[0];
    wt[0]=start[0]-at[0];
    tat[0]=finish[0]-at[0];
    for(int i=1;i<n;i++){
        start[i]=(finish[i-1]>at[i])?finish[i-1]:at[i];
        finish[i]=start[i]+bt[i];
        wt[i]=start[i]-at[i];
        tat[i]=finish[i]-at[i];
    }
    printGantt(n,order,start,finish);
    printf("\nP\tAT\tBT\tST\tFT\tWT\tTAT\n");
    float total_wt=0,total_tat=0;
    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],start[i],finish[i],wt[i],tat[i]);
        total_wt+=wt[i]; total_tat+=tat[i];
    }
    printf("\nAverage Waiting Time=%.2f\nAverage Turnaround Time=%.2f\n",total_wt/n,total_tat/n);
}

// SJF Non-preemptive - Fixed table & Gantt
void sjf(){
    int n=getPositiveInt("Enter number of processes: ");
    int at[20],bt[20],used[20],wt[20],tat[20],st[20],ft[20];
    int gantt_proc[20],gantt_start[20],gantt_finish[20];
    for(int i=0;i<n;i++){
        char temp[50];
        sprintf(temp,"Process %d Arrival Time: ",i+1);
        at[i]=getNonNegativeInt(temp);
        sprintf(temp,"Process %d CPU Burst Time: ",i+1);
        bt[i]=getNonNegativeInt(temp);
        used[i]=0;
    }
    int done=0,current_time=0,idx_gantt=0;
    while(done<n){
        int idx=-1,min=INT_MAX;
        for(int i=0;i<n;i++){
            if(!used[i] && at[i]<=current_time && bt[i]<min){min=bt[i]; idx=i;}
        }
        if(idx==-1){current_time++; continue;}
        gantt_proc[idx_gantt]=idx;
        gantt_start[idx_gantt]=current_time;
        st[idx]=current_time;
        current_time+=bt[idx];
        gantt_finish[idx_gantt]=current_time;
        ft[idx]=current_time;
        used[idx]=1;
        tat[idx]=ft[idx]-at[idx];
        wt[idx]=tat[idx]-bt[idx];
        idx_gantt++;
        done++;
    }
    printGantt(idx_gantt,gantt_proc,gantt_start,gantt_finish);
    printf("\nP\tAT\tBT\tST\tFT\tWT\tTAT\n");
    float total_wt=0,total_tat=0;
    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],st[i],ft[i],wt[i],tat[i]);
        total_wt+=wt[i]; total_tat+=tat[i];
    }
    printf("\nAverage Waiting Time=%.2f\nAverage Turnaround Time=%.2f\n",total_wt/n,total_tat/n);
}

// SRJF Preemptive
void srjf(){
    int n=getPositiveInt("Enter number of processes: ");
    int at[20],bt[20],rt[20],ft[20],wt[20],tat[20];
    int gantt_proc[1000],gantt_start[1000],gantt_finish[1000];
    for(int i=0;i<n;i++){
        char temp[50];
        sprintf(temp,"Process %d Arrival Time: ",i+1);
        at[i]=getNonNegativeInt(temp);
        sprintf(temp,"Process %d CPU Burst Time: ",i+1);
        bt[i]=getNonNegativeInt(temp);
        rt[i]=bt[i]; ft[i]=0; wt[i]=0; tat[i]=0;
    }
    int complete=0,time=0,idx_gantt=0,last=-1;
    while(complete<n){
        int idx=-1,min=INT_MAX;
        for(int i=0;i<n;i++){
            if(at[i]<=time && rt[i]>0 && rt[i]<min){min=rt[i]; idx=i;}
        }
        if(idx==-1){time++; continue;}
        if(last!=idx){
            gantt_proc[idx_gantt]=idx;
            gantt_start[idx_gantt]=time;
            if(last!=-1) gantt_finish[idx_gantt-1]=time;
            idx_gantt++;
            last=idx;
        }
        rt[idx]--; time++;
        if(rt[idx]==0){ft[idx]=time; tat[idx]=ft[idx]-at[idx]; wt[idx]=tat[idx]-bt[idx]; complete++;}
    }
    gantt_finish[idx_gantt-1]=time;
    printGantt(idx_gantt,gantt_proc,gantt_start,gantt_finish);
    printf("\nP\tAT\tBT\tFT\tWT\tTAT\n");
    float total_wt=0,total_tat=0;
    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],ft[i],wt[i],tat[i]);
        total_wt+=wt[i]; total_tat+=tat[i];
    }
    printf("\nAverage Waiting Time=%.2f\nAverage Turnaround Time=%.2f\n",total_wt/n,total_tat/n);
}

// Main menu
int main(){
    char again[10];
    do{
        int choice=getPositiveInt("\nCPU Scheduling Algorithms\n1.FCFS\n2.SJF\n3.SRJF\nEnter choice: ");
        switch(choice){
            case 1: fcfs(); break;
            case 2: sjf(); break;
            case 3: srjf(); break;
            default: printf("Invalid choice!\n");
        }
        printf("\nCheck another algorithm? (yes/no): ");
        scanf("%s",again);
    }while(strcmp(again,"yes")==0);
    printf("Program Ended.\n");
    return 0;
}
