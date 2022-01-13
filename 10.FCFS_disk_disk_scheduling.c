#include<stdio.h>
#include<stdlib.h> // for abs
int main()
{
    int n;
    printf("Enter Number of Disk Requests : "); // disk track requests
    scanf(" %d",&n);
    printf("Enter Disk Requests : ");
    int request[n];
    for(int i=0;i<n;i++)
    {
        scanf(" %d",&request[i]);
    }
    int initial_head;
    printf("Enter initial Position of R/W head : ");
    scanf(" %d",&initial_head);
    int seek_time = 0;
    printf("\n%5d  ->",initial_head);
    for(int i=0;i<n;i++)
    {
        if(i == n-1)
        {
            printf("%5d",request[i]);
        }
        else
        {
            printf("%5d  ->",request[i]);
        }
        seek_time+= abs(initial_head - request[i]);
        initial_head  = request[i];
    }
    printf("\n\nSeek Time(Head movement)    = %d",seek_time);
    printf("\nAverage Seek Time           =  %.2f\n",(float)seek_time/n);
    return 0;
}
/*

Enter Number of Disk Requests : 7
Enter Disk Requests : 82 170 43 140 24 16 190
Enter initial Position of R/W head : 50

   50  ->   82  ->  170  ->   43  ->  140  ->   24  ->   16  ->  190

Seek Time(Head movement)    = 642
Average Seek Time           =  91.71

*/