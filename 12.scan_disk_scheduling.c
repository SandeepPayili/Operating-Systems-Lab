//Scan Disk Scheduling
#include<stdio.h>
#include<stdlib.h> // for abs
#include<limits.h>
struct request
{
    int request_track_number;
    int visited;
};
int main()
{
    int n;
    printf("Enter Number of Disk Requests : "); // disk track requests
    scanf(" %d",&n);
    struct request req[n];
    printf("Enter Disk Requests : ");
    int max_track_request = INT_MIN;
    int min_track_request = INT_MAX;
    for(int i=0;i<n;i++)
    {
        scanf(" %d",&req[i].request_track_number);
        req[i].visited = 0;
        if(req[i].request_track_number > max_track_request )
        {
            max_track_request = req[i].request_track_number;
        }
        if(req[i].request_track_number < min_track_request )
        {
            min_track_request = req[i].request_track_number;
        }
    }
    int initial_head;
    printf("Enter initial Position of R/W head : ");
    scanf(" %d",&initial_head);
    int temp_initial_head = initial_head;

    int limit;
    printf("Enter Number of Tracks(Cylinder Size) : "); //there are 200 cylinders numbered from 0 - 199
    scanf(" %d",&limit);
    limit -= 1;// for inclusive condition

    int direction;
    printf("Enter Direction (1 to Right, 2 to Left) : ");
    scanf(" %d",&direction);
 
    int seek_time = 0;
    printf("\n%d -> ",initial_head);
    if(direction == 1)
    {
        for(int i= initial_head;i<=limit;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(req[j].request_track_number == i && req[j].visited == 0)
                {
                    printf("%d -> ",req[j].request_track_number);
                    req[j].visited = 1;
                    seek_time += abs(req[j].request_track_number - initial_head);
                    initial_head = req[j].request_track_number;
                }
            }
        } 
        printf("%d -> ",limit);
        seek_time+= abs(limit - initial_head);
        initial_head = limit;
        for(int i=limit;i>=min_track_request;i--)
        {
            for(int j=0;j<n;j++)
            {
                if(req[j].request_track_number == i && req[j].visited == 0)
                {
                    printf("%d -> ",req[j].request_track_number);
                    seek_time += abs(initial_head - req[j].request_track_number);
                    initial_head = req[j].request_track_number;
                    req[j].visited = 1; 
                }
            }
        }
        // printf("%d ",0);
        // seek_time += abs(initial_head - 0);
        // initial_head = 0;
    }
    else // direction 2 for left
    {
        for(int i=initial_head;i>=0;i--)
        {
            for(int j= 0;j<n;j++)
            {
                if(req[j].request_track_number == i && req[j].visited == 0)
                {
                    printf("%d -> ",req[j].request_track_number);
                    seek_time += abs(req[j].request_track_number - initial_head);
                    req[j].visited = 1;
                    initial_head = req[j].request_track_number;
                }
            }
        }
        printf("%d -> ",0);
        seek_time += abs(initial_head - 0);
        initial_head = 0;
        for(int i=0;i<=max_track_request;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(req[j].request_track_number == i && req[j].visited == 0)
                {
                    printf("%d -> ",req[j].request_track_number);
                    seek_time += abs(initial_head - req[j].request_track_number);
                    req[j].visited = 1;
                    initial_head = req[j].request_track_number;
                }
            }
        }
        // printf("%d -> ",limit);
        // seek_time += (limit - initial_head);
        // initial_head = limit;
    }
    printf("\n\nSeek Time(Head movement)    =  %d",seek_time);
    printf("\nAverage Seek Time           =  %.2f\n",(float)seek_time/n);
    return 0;
}
/*
Enter Number of Disk Requests : 9
Enter Disk Requests : 53 98 183 37 122 14 124 65 67
Enter initial Position of R/W head : 53
Enter Number of Tracks(Cylinder Size) : 200
Enter Direction (1 to Right, 2 to Left) : 1

53 -> 53 -> 65 -> 67 -> 98 -> 122 -> 124 -> 183 -> 199 -> 37 -> 14 ->

Seek Time(Head movement)    =  331
Average Seek Time           =  36.78
*/

/*

Enter Number of Disk Requests : 8
Enter Disk Requests : 98 183 41 122 14 124 65 67
Enter initial Position of R/W head : 53
Enter Number of Tracks(Cylinder Size) : 200
Enter Direction (1 to Right, 2 to Left) : 1

53 -> 65 -> 67 -> 98 -> 122 -> 124 -> 183 -> 199 -> 41 -> 14 ->

Seek Time(Head movement)    =  331
Average Seek Time           =  41.38
*/
