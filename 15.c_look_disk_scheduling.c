// Circular look disk scheduling
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

    int direction;
    printf("Enter Direction (1 to Right, 2 to Left) : ");
    scanf(" %d",&direction);
 
    int seek_time = 0;
    printf("\n%d -> ",initial_head);
    if(direction == 1)
    {
        for(int i= initial_head;i<=max_track_request;i++)
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
        printf("%d -> ",min_track_request);
        seek_time += abs(initial_head - min_track_request);
        initial_head = min_track_request;
        for(int i=initial_head;i<=max_track_request;i++) // max_track_request can be replaced with copy of initial_head
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
    }
    else // direction 2 for left
    {
        for(int i=initial_head;i>=min_track_request;i--)
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
        printf("%d -> ",max_track_request);
        seek_time += abs(initial_head - max_track_request);
        initial_head  = max_track_request;
        for(int i=initial_head;i>=min_track_request;i--)
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
    }
    printf("\n\nSeek Time(Head movement)    =  %d",seek_time);
    printf("\nAverage Seek Time           =  %.2f\n",(float)seek_time/n);
    return 0;
}

/*

Enter Number of Disk Requests : 6
Enter Disk Requests : 10 15 75 25 95 85
Enter initial Position of R/W head : 50
Enter Direction (1 to Right, 2 to Left) : 1

50 -> 75 -> 85 -> 95 -> 10 -> 10 -> 15 -> 25 -> 

Seek Time(Head movement)    =  145
Average Seek Time           =  24.17

*/

/*

Enter Number of Disk Requests : 8
Enter Disk Requests : 176 79 34 60 92 11 41 114
Enter initial Position of R/W head : 50
Enter Direction (1 to Right, 2 to Left) : 2

50 -> 41 -> 34 -> 11 -> 176 -> 176 -> 114 -> 92 -> 79 -> 60 ->

Seek Time(Head movement)    =  320
Average Seek Time           =  40.00

*/

/*

Enter Number of Disk Requests : 6
Enter Disk Requests : 10 15 75 25 95 85
Enter initial Position of R/W head : 50
Enter Direction (1 to Right, 2 to Left) : 1

50 -> 75 -> 85 -> 95 -> 10 -> 10 -> 15 -> 25 ->

Seek Time(Head movement)    =  145
Average Seek Time           =  24.17

*/

/*

Enter Number of Disk Requests : 6
Enter Disk Requests :  10 15 75 25 95 85
Enter initial Position of R/W head : 50
Enter Direction (1 to Right, 2 to Left) : 2

50 -> 25 -> 15 -> 10 -> 95 -> 95 -> 85 -> 75 ->

Seek Time(Head movement)    =  145
Average Seek Time           =  24.17

*/

/*

Enter Number of Disk Requests : 8
Enter Disk Requests : 98 183 41 122 14 124 65 67
Enter initial Position of R/W head : 53
Enter Direction (1 to Right, 2 to Left) : 1

53 -> 65 -> 67 -> 98 -> 122 -> 124 -> 183 -> 14 -> 14 -> 41 ->

Seek Time(Head movement)    =  326
Average Seek Time           =  40.75

*/

/*
Enter Number of Disk Requests : 8
Enter Disk Requests : 98 183 41 122 14 124 65 67
Enter initial Position of R/W head : 53
Enter Direction (1 to Right, 2 to Left) : 2

53 -> 41 -> 14 -> 183 -> 183 -> 124 -> 122 -> 98 -> 67 -> 65 -> 

Seek Time(Head movement)    =  326
Average Seek Time           =  40.75
*/

/*

Enter Number of Disk Requests : 8
Enter Disk Requests : 47 38 121 191 87 11 92 10
Enter initial Position of R/W head : 63
Enter Direction (1 to Right, 2 to Left) : 1

63 -> 87 -> 92 -> 121 -> 191 -> 10 -> 10 -> 11 -> 38 -> 47 -> 

Seek Time(Head movement)    =  346
Average Seek Time           =  43.25

*/