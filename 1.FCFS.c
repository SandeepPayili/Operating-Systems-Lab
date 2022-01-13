// non preemptice First Come First Serve
#include<stdio.h>
#include<stdlib.h>
struct process{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
};
void sort(struct process *p,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-1;j++)
        {
            if(p[j].at > p[j+1].at)
            {
                struct process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}
int main()
{
    int n;
    printf("Enter Number of Processes : ");
    scanf(" %d",&n);
    struct process p[n];
    printf("Enter Arrival Time and Brust Time Of Processes : \n");
    for(int i=0;i<n;i++)
    {
        p[i].pid = i;
        scanf(" %d %d",&p[i].at,&p[i].bt);
    }
    sort(p,n);
    int time = 0;
    printf("Gantt Chart :  \n");
    printf("---------------------------------------------------------------------------------\n");
    for(int i=0;i<n;i++)
    {
        if(p[i].at > time)
        {
            // printf("%d Idle %d\t\t",time,time+p[i].at);
            printf("%d Idle %d\t\t",time,p[i].at);
            time += (p[i].at - time);
        }  
        printf("%d P%d %d\t\t",time,p[i].pid,time+p[i].bt);
        time += p[i].bt;     
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;       
    }
    printf("\n---------------------------------------------------------------------------------");
    printf("\n\n");
    printf("Pid\t\tAT\t\tBT\t\tCT\t\tTAT\t\tWT\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
    }
    return 0;
}
/*

Enter Number of Processes : 5
Enter Arrival Time and Brust Time Of Processes :
0 2
1 6
2 4
3 9
4 12
Gantt Chart :
---------------------------------------------------------------------------------
0 P0 2          2 P1 8          8 P2 12         12 P3 21                21 P4 33
---------------------------------------------------------------------------------

Pid             AT              BT              CT              TAT             WT
0               0               2               2               2               0
1               1               6               8               7               1
2               2               4               12              10              6
3               3               9               21              18              9
4               4               12              33              29              17

*/