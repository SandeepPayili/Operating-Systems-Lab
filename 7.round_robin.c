// Round Robin (Preemptive FCFS)
// time sharing schedule
#include<stdio.h>
struct process{
    int pid;
    int at;
    int bt;
    int copy_bt;
    int ct;
    int tat;
    int wt;
    int rt;
};
struct queue{
    int qa[100];
    int f;
    int r;
};
void enqueue(struct queue *q,int i)
{
    q->r++;
    q->qa[q->r] = i;
}
int dequeue(struct queue *q)
{
    if(q->f == q->r )
    {
        return -1;
    }
    q->f++;
    return q->qa[q->f];
}
void sort_by_arrival_time(struct process *p,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<j-1;j++)
        {
            if(p[j].at > p[j+1].at)
            {
                struct process temp   = p[j];
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
    struct queue q;
    q.f = -1;
    q.r  = -1;
    int tq;
    printf("Enter Time Quanta : ");
    scanf(" %d",&tq);
    printf("Enter Arrival Time and Brust of Processes : \n");
    for(int i=0;i<n;i++)
    {
        p[i].pid = i;
        scanf(" %d %d",&p[i].at,&p[i].bt);
        p[i].copy_bt = p[i].bt;
        p[i].rt  = -1;
        p[i].ct = -1;
        p[i].tat = -1;
        p[i].wt = -1;
    }
    sort_by_arrival_time(p,n);
    printf("\nGANTT CHART :   \n");
    printf("---------------------------------------------------------------------------------------\n");
    int time = 0;
    int c = 0;
    for(int i=0;i<n;i++)
    {
        if(time >= p[i].at)
        {
            enqueue(&q,i);
        }
    }
    while(c < n)
    {
        int next_pid = dequeue(&q);
        if(next_pid == -1)
        {
            for(int i=0;i<n;i++)
            {
                if(p[i].bt > 0)
                {
                    printf(" %d Idle  %d\n",time,time+p[i].at);
                    time += p[i].at;
                    enqueue(&q,i);
                    break;
                }
            }
            continue;
        }
        if(p[next_pid].rt  == -1)
        {
            p[next_pid].rt = ( time - p[next_pid].at );
        }
        if(p[next_pid].bt <= tq)
        {
            printf("%3d   P%d  %3d\n",time,p[next_pid].pid,time+p[next_pid].bt);
            for(int i=0;i<n;i++)
            {
                if( p[i].at >time && p[i].at <= (time+p[next_pid].bt)   && i != next_pid  )// = bug
                {
                    enqueue(&q,i);
                }
            }
            time+= p[next_pid].bt;
            p[next_pid].bt = 0;
            p[next_pid].ct  = time;
            p[next_pid].tat = p[next_pid].ct - p[next_pid].at;
            p[next_pid].wt = p[next_pid].tat - p[next_pid].copy_bt;
            c++;
            continue;
        }
        printf("%3d   P%d  %3d\n",time,p[next_pid].pid,time+tq);
        for(int i=0;i<n;i++)
        {
                if( p[i].at >time && p[i].at <= (time+tq)   && i != next_pid  )// = bug
                {
                    enqueue(&q,i);
                }
        }
        time+=tq;
        p[next_pid].bt -= tq;
        enqueue(&q,next_pid);   
    }
    printf("---------------------------------------------------------------------------------------\n");
    printf("\n\nPid\t\tAT\t\tBT\t\tCT\t\tTAT\t\tWT\t\tRT\n\n");
    float total_tat = 0;
    float total_wt = 0;
    for(int i=0;i<n;i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].pid,p[i].at,p[i].copy_bt,p[i].ct,p[i].tat,p[i].wt,p[i].rt);
        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }
    printf("\n\nReady Queue :  \n\n");
    for(int i=0;i<=q.r;i++)
    {
        printf(" %d ",q.qa[i]);
    }
    printf("\n");
    printf("\nAverage   TAT = %.2f\n",total_tat/n);
    printf("Average    WT = %.2f\n\n",total_wt/n);
    return 0;
}

/*

Enter Number of Processes : 6
Enter Time Quanta : 4
Enter Arrival Time and Brust of Processes :
0 5
1 6
2 3
3 1
4 5
5 4

GANTT CHART :
---------------------------------------------------------------------------------------
  0   P0    4
  4   P1    8
  8   P2   11
 11   P3   12
 12   P4   16
 16   P0   17
 17   P5   21
 21   P1   23
 23   P4   24
---------------------------------------------------------------------------------------


Pid             AT              BT              CT              TAT             WT              RT

0               0               5               17              17              12              0
1               1               6               23              22              16              3
2               2               3               11              9               6               6
3               3               1               12              9               8               8
4               4               5               24              20              15              8
5               5               4               21              16              12              12


Ready Queue :

 0  1  2  3  4  0  5  1  4

Average   TAT = 15.50
Average    WT = 11.50


*/