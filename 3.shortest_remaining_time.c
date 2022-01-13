//shortest remaining time first
// shortest job first + preemption
// in case of tie consider FCFS
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
struct process{
    int pid;
    int at;
    int bt;
    int copy_bt;
    int ct;
    int tat;
    int wt;
    int rt;
    int flag;
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
    printf("Enter Arrival Time and Brust Time Of Processes : \n");
    for(int i=0;i<n;i++)
    {
        p[i].pid = i;
        scanf(" %d %d",&p[i].at,&p[i].bt);
        p[i].flag = 0;
        p[i].rt = -1;
        p[i].copy_bt = p[i].bt;
    }
    sort_by_arrival_time(p,n);
    int time = 0;
    int c = 0;
    printf("Gantt Chart :  \n");
    printf("----------------------------------------------------------------------------------------\n");
    while(c<n)
    {
        int min_bt = INT_MAX;
        int min_bt_pid = -1;
         for(int i=0;i<n;i++)
         {
             if( p[i].bt < min_bt && time >= p[i].at && p[i].bt > 0)
             {
                 min_bt = p[i].bt;
                 min_bt_pid = i;
             }
         }
         if(min_bt_pid == -1)
         {
             for(int i=0;i<n;i++)
             {
                 if( p[i].flag == 0 )
                 {
                    //  printf("%d Idle %d\n",time,(time+p[i].at));
                    //  time += p[i].at;                  
                    printf("%d Idle %d\n",time,p[i].at);
                    time = p[i].at;                  
                     break;
                 }
             }
             continue;
         }
        if( p[min_bt_pid].rt == -1)
        {
            p[min_bt_pid].rt = (time - p[min_bt_pid].at);
        }
        printf("%d P%d %d\n",time,p[min_bt_pid].pid,time+1);
        time += 1;
        p[min_bt_pid].bt -=1;
        if(p[min_bt_pid].bt  == 0)
        {
            p[min_bt_pid].flag = 1;
            p[min_bt_pid].ct  = time;
            p[min_bt_pid].tat = (p[min_bt_pid].ct - p[min_bt_pid].at);
            p[min_bt_pid].wt = (p[min_bt_pid].tat - p[min_bt_pid].copy_bt);
            p[min_bt_pid].flag = 1;
            c++;
        }
    }
    sort_by_proccess_id(p,n); 
    int sum_tat=0;
    int sum_wt=0;
    printf("----------------------------------------------------------------------------------------\n");
    printf("\n\nPid\t\tAT\t\tBT\t\tCT\t\tTAT\t\tWT\t\tRT\n\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].pid,p[i].at,p[i].copy_bt,p[i].ct,p[i].tat,p[i].wt,p[i].rt);
        sum_tat += p[i].tat;
        sum_wt += p[i].wt;
    }
    printf("\n\n Average TAT  =  %.2f\n",((float)sum_tat/n));
    printf("\n\n Average WT   =  %.2f\n",((float)sum_wt/n));
    return 0;
}
/*

Enter Number of Processes : 6
Enter Arrival Time and Brust Time Of Processes :
0 8
1 4
2 2
3 1
4 3
5 2
Gantt Chart :
----------------------------------------------------------------------------------------
0 P0 1
1 P1 2
2 P2 3
3 P2 4
4 P3 5
5 P5 6
6 P5 7
7 P1 8
8 P1 9
9 P1 10
10 P4 11
11 P4 12
12 P4 13
13 P0 14
14 P0 15
15 P0 16
16 P0 17
17 P0 18
18 P0 19
19 P0 20
----------------------------------------------------------------------------------------


Pid             AT              BT              CT              TAT             WT              RT

0               0               8               20              20              12              0
1               1               4               10              9               5               0
2               2               2               4               2               0               0
3               3               1               5               2               1               1
4               4               3               13              9               6               6
5               5               2               7               2               0               0


 Average TAT  =  7.33


 Average WT   =  4.00

 */