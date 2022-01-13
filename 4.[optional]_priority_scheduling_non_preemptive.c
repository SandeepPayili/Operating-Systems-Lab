// priority scheduling non preemptive
// higher the value higher the priority
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
    int priority;
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
    printf("Enter Arrival Time , Brust Time and Priority Of Processes : \n");
    for(int i=0;i<n;i++)
    {
        p[i].pid = i;
        scanf(" %d %d %d",&p[i].at,&p[i].bt,&p[i].priority);
        p[i].flag = 0;
    }
    sort(p,n);
    int c = 0;
    int time = 0;
    printf("Gantt Chart :  \n");
    printf("----------------------------------------------------------------------------------------\n");
    while(c<n)
    {
        int max_priority_pid = -1;
        int max_priority  = INT_MIN;
        for(int i=0;i<n;i++)
        {
            if(time >= p[i].at && p[i].priority > max_priority && p[i].flag == 0)
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
        printf("%d P%d %d\n",time,p[max_priority_pid].pid,(time+p[max_priority_pid].bt));
        time+= p[max_priority_pid].bt;
        p[max_priority_pid].ct = time;
        p[max_priority_pid].tat = p[max_priority_pid].ct - p[max_priority_pid].at;
        p[max_priority_pid].wt = p[max_priority_pid].tat - p[max_priority_pid].bt;
        p[max_priority_pid].flag = 1;
        c++;
    }
    printf("----------------------------------------------------------------------------------------\n");
    printf("\nPid\t\tAT\t\tBT\t\tPriority\tCT\t\tTAT\t\tWT\n\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].priority,p[i].ct,p[i].tat,p[i].wt);
    }
    return 0;
}