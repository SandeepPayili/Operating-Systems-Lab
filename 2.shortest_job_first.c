// non preemptive shortest job first
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
struct process{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int flag;
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
        p[i].flag = 0;
    }
    sort(p,n);
    int time = 0;
    int c=0;
    printf("Gantt Chart :  \n");
    printf("----------------------------------------------------------------------------------------\n");
    while(c < n)
    {
        int min_bt_pid  = -1;
        int min_bt = INT_MAX;
        for(int i=0;i<n;i++)
        {
            if( time >= p[i].at)
            {
                if(p[i].bt < min_bt && p[i].flag == 0 )
                {
                    min_bt = p[i].bt;
                    min_bt_pid = i;  
                }
            }
        }
        if(min_bt_pid == -1)
        {
            for(int i=0;i<n;i++)
            {
                if(p[i].flag == 0)
                {
                    printf("%d Idle %d\t\t",time,(time+p[i].at));
                    // time+= (p[i].at -  time);
                    time = p[i].at; // p[i].at > time
                    break;
                }
            }
            continue;
        }
        printf("%d P%d %d\t\t",time,p[min_bt_pid].pid,time+p[min_bt_pid].bt);
        time += p[min_bt_pid].bt;
        p[min_bt_pid].ct  = time;
        p[min_bt_pid].tat = (p[min_bt_pid].ct - p[min_bt_pid].at);
        p[min_bt_pid].wt = (p[min_bt_pid].tat - p[min_bt_pid].bt);
        p[min_bt_pid].flag = 1;
        c++;
    }
    printf("\n----------------------------------------------------------------------------------------\n");
    printf("\n\nPid\t\tAT\t\tBT\t\tCT\t\tTAT\t\tWT\n\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
    }
    return 0;
}
/*

Enter Number of Processes : 5
Enter Arrival Time and Brust Time Of Processes :
1 7
3 3
6 2
7 10
9 8
Gantt Chart :
----------------------------------------------------------------------------------------
0 Idle 1                1 P0 8          8 P2 10         10 P1 13                13 P4 21                21 P3 31
----------------------------------------------------------------------------------------


Pid             AT              BT              CT              TAT             WT

0               1               7               8               7               0
1               3               3               13              10              7
2               6               2               10              4               2
3               7               10              31              24              14
4               9               8               21              12              4

*/