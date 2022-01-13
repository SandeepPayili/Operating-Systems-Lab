// priority scheduling non preemptive
// lower the value higher the priority
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
    int rt;
    int flag;
    int priority;
}; 

void sort_by_proccess_id(struct process *p,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-1;j++)
        {
            if(p[j].pid > p[j+1].pid)
            {
                struct process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}
void sort_by_arrival_time(struct process *p,int n)
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
    printf("Enter Arrival Time , Brust Time and Priority Of Processes : \n");
    for(int i=0;i<n;i++)
    {
        p[i].pid = i;
        scanf(" %d %d %d",&p[i].at,&p[i].bt,&p[i].priority);
        p[i].flag = 0;
        p[i].rt = -1;
    }
    sort_by_arrival_time(p,n);
    int c = 0;
    int time = 0;
    printf("Gantt Chart :  \n");
    printf("----------------------------------------------------------------------------------------\n");
    while(c<n)
    {
        int max_priority_pid = -1;
        int max_priority  = INT_MAX;
        for(int i=0;i<n;i++)
        {
            if(time >= p[i].at && p[i].priority < max_priority && p[i].flag == 0)
            {
                max_priority = p[i].priority;
                max_priority_pid = i;
            }
        }
        if(max_priority_pid == -1)
        {
            for(int i=0;i<n;i++)
            {
                if(p[i].flag == 0)
                {
                    printf(" %d idle %d\n",time,(time+p[i].at));
                    time+= p[i].at;
                    break;
                }
            }       
            continue;
        }
        if( p[max_priority_pid].rt == -1 )
        {
            p[max_priority_pid].rt = (time-p[max_priority_pid].at);
        }
        printf("%d P%d %d\n",time,p[max_priority_pid].pid,(time+p[max_priority_pid].bt));
        time+= p[max_priority_pid].bt;
        p[max_priority_pid].ct = time;
        p[max_priority_pid].tat = p[max_priority_pid].ct - p[max_priority_pid].at;
        p[max_priority_pid].wt = p[max_priority_pid].tat - p[max_priority_pid].bt;
        p[max_priority_pid].flag = 1;
        c++;
    }
    sort_by_proccess_id(p,n);
    int sum_tat=0;
    int sum_wt=0;
    printf("----------------------------------------------------------------------------------------\n");
    printf("\nPid\t\tAT\t\tBT\t\tPriority\tCT\t\tTAT\t\tWT\t\tRT\n\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].priority,p[i].ct,p[i].tat,p[i].wt,p[i].rt);
        sum_tat += p[i].tat;
        sum_wt += p[i].wt;
    }
    printf("\n\n Average TAT  =  %.2f\n",((float)sum_tat/n));
    printf("\n\n Average WT   =  %.2f\n",((float)sum_wt/n));
    return 0;
}

/*
Enter Number of Processes : 7
Enter Arrival Time , Brust Time and Priority Of Processes :
0 3 2
2 5 6
1 4 3
4 2 5
6 9 7
5 4 4
7 10 10
Gantt Chart :
----------------------------------------------------------------------------------------
0 P0 3
3 P2 7
7 P5 11
11 P3 13
13 P1 18
18 P4 27
27 P6 37
----------------------------------------------------------------------------------------

Pid             AT              BT              Priority        CT              TAT             WT              RT

0               0               3               2               3               3               0               0
1               2               5               6               18              16              11              11
2               1               4               3               7               6               2               2
3               4               2               5               13              9               7               7
4               6               9               7               27              21              12              12
5               5               4               4               11              6               2               2
6               7               10              10              37              30              20              20


 Average TAT  =  13.00


 Average WT   =  7.71
 */