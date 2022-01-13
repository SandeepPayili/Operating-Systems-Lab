// priority scheduling preemptive
// lower the value higher the priority
#include<stdio.h>
#include<limits.h>
struct process{
    int pid;
    int at;
    int bt;
    int ct;
    int copy_bt;
    int tat;
    int wt;
    int rt;
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
    printf("Enter Number Of process : ");
    scanf(" %d",&n);
    struct process p[n];
    printf("Enter Processes Arrival Time,Brust Time and Priority : \n");
    for(int i=0;i<n;i++)
    {
        p[i].pid = i;
        scanf(" %d %d %d",&p[i].at,&p[i].bt,&p[i].priority);
        p[i].copy_bt = p[i].bt;
        p[i].rt = -1;
    }
    sort_by_arrival_time(p,n);
    int c = 0;
    int time = 0;
    printf("\nGantt Chart :  \n");
    while(c<n)
    {
        int max_priority_id = -1;
        int max_priority = INT_MAX;
        for(int i=0;i<n;i++)
        {
            if(time >= p[i].at && p[i].priority < max_priority && p[i].bt > 0 )
            {
                max_priority = p[i].priority;
                max_priority_id = i;
            }
        }
        if(max_priority_id == -1)
        {
            for(int i=0;i<n;i++)
            {
                if(p[i].bt > 0)
                {
                    printf("%d Idle %d\n",time,time+p[i].at);
                    time+= p[i].at;
                }
            }
            continue;
        }
        if(p[max_priority_id].rt == -1)
        {
            p[max_priority_id].rt = (time - p[max_priority_id].at);
        }
        printf("%d P%d %d\n",time,p[max_priority_id].pid,time+1);
        time+=1;
        p[max_priority_id].bt -= 1;
        if(p[max_priority_id].bt == 0)
        {
            //printf("%d P%d %d\n",time,p[max_priority_id].pid,(time+p[max_priority_id].copy_bt));
            p[max_priority_id].ct = (time+p[max_priority_id].bt);
            p[max_priority_id].tat = p[max_priority_id].ct - p[max_priority_id].at;
            p[max_priority_id].wt = p[max_priority_id].tat - p[max_priority_id].copy_bt;
            c++;
        }
    }
    sort_by_proccess_id(p,n);
    int sum_tat=0;
    int sum_wt=0;
    printf("\n\nPid\t\tAT\t\tBT\t\tPriority\tCT\t\tTAT\t\tWT\t\tRT\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].pid,p[i].at,p[i].copy_bt,p[i].priority,p[i].ct,p[i].tat,p[i].wt,p[i].rt);
        sum_tat += p[i].tat;
        sum_wt += p[i].wt;
    }
    printf("\n\n Average TAT  =  %.2f\n",((float)sum_tat/n));
    printf("\n\n Average WT   =  %.2f\n",((float)sum_wt/n));
    return 0;
}
/*
Enter Number Of process : 7
Enter Processes Arrival Time,Brust Time and Priority :
0 1 2
1 7 6
2 3 3
3 6 5
4 5 4
5 15 10
6 8 9

Gantt Chart :
0 P0 1
1 P1 2
2 P2 3
3 P2 4
4 P2 5
5 P4 6
6 P4 7
7 P4 8
8 P4 9
9 P4 10
10 P3 11
11 P3 12
12 P3 13
13 P3 14
14 P3 15
15 P3 16
16 P1 17
17 P1 18
18 P1 19
19 P1 20
20 P1 21
21 P1 22
22 P6 23
23 P6 24
24 P6 25
25 P6 26
26 P6 27
27 P6 28
28 P6 29
29 P6 30
30 P5 31
31 P5 32
32 P5 33
33 P5 34
34 P5 35
35 P5 36
36 P5 37
37 P5 38
38 P5 39
39 P5 40
40 P5 41
41 P5 42
42 P5 43
43 P5 44
44 P5 45


Pid             AT              BT              Priority        CT              TAT             WT              RT
0               0               1               2               1               1               0               0
1               1               7               6               22              21              14              0
2               2               3               3               5               3               0               0
3               3               6               5               16              13              7               7
4               4               5               4               10              6               1               1
5               5               15              10              45              40              25              25
6               6               8               9               30              24              16              16


 Average TAT  =  15.43


 Average WT   =  9.00
 */