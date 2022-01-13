// Circular Scan Disk Scheduling
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
        printf("%d -> ",0);
        seek_time += abs(limit - 0);
        initial_head = 0;
        for(int i=0;i<=max_track_request;i++)//max_track_request can be replaced by copy of initial_head 
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
        for(int i=initial_head;i>=0;i--) // 0 can be replaced by copy of initial_head 
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
        printf("%d -> ",limit);
        seek_time += abs(0 - limit);
        initial_head = abs(0 - limit);
        for(int i=limit;i >= min_track_request;i--)
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

Enter Number of Disk Requests : 10
Enter Disk Requests : 14 67 41 183 53 65 98 122 124 199
Enter initial Position of R/W head : 50
Enter Number of Tracks(Cylinder Size) : 200
Enter Direction (1 to Right, 2 to Left) : 1

50 -> 53 -> 65 -> 67 -> 98 -> 122 -> 124 -> 183 -> 199 -> 199 -> 0 -> 14 -> 41 ->

Seek Time(Head movement)    =  389
Average Seek Time           =  38.90
*/

/*
Enter Number of Disk Requests : 10
Enter Disk Requests : 14 67 41 183 53 65 98 122 124 199
Enter initial Position of R/W head : 53
Enter Number of Tracks(Cylinder Size) : 200
Enter Direction (1 to Right, 2 to Left) : 1

53 -> 53 -> 65 -> 67 -> 98 -> 122 -> 124 -> 183 -> 199 -> 199 -> 0 -> 14 -> 41 ->

Seek Time(Head movement)    =  386
Average Seek Time           =  38.60

*/

/*
Enter Number of Disk Requests : 10
Enter Disk Requests : 14 67 41 183 53 65 98 122 124 199
Enter initial Position of R/W head : 53
Enter Number of Tracks(Cylinder Size) : 200
Enter Direction (1 to Right, 2 to Left) : 2

53 -> 53 -> 41 -> 14 -> 0 -> 199 -> 199 -> 183 -> 124 -> 122 -> 98 -> 67 -> 65 ->

Seek Time(Head movement)    =  386
Average Seek Time           =  38.60
*/

/*
Enter Number of Disk Requests : 10
Enter Disk Requests :  14 67 41 183 53 65 98 122 124 199
Enter initial Position of R/W head : 50
Enter Number of Tracks(Cylinder Size) : 200
Enter Direction (1 to Right, 2 to Left) : 2

50 -> 41 -> 14 -> 0 -> 199 -> 199 -> 183 -> 124 -> 122 -> 98 -> 67 -> 65 -> 53 ->

Seek Time(Head movement)    =  395
Average Seek Time           =  39.50

*/

/*

Enter Number of Disk Requests : 8
Enter Disk Requests : 98 183 41 122 14 124 65 67
Enter initial Position of R/W head : 53
Enter Number of Tracks(Cylinder Size) : 200
Enter Direction (1 to Right, 2 to Left) : 1

53 -> 65 -> 67 -> 98 -> 122 -> 124 -> 183 -> 199 -> 0 -> 14 -> 41 ->

Seek Time(Head movement)    =  386
Average Seek Time           =  48.25

*/

/*

Enter Number of Disk Requests : 8
Enter Disk Requests : 176 79 34 60 92 11 41 114
Enter initial Position of R/W head : 50
Enter Number of Tracks(Cylinder Size) : 200
Enter Direction (1 to Right, 2 to Left) : 1

50 -> 60 -> 79 -> 92 -> 114 -> 176 -> 199 -> 0 -> 11 -> 34 -> 41 ->

Seek Time(Head movement)    =  389
Average Seek Time           =  48.63

*/

/*

Enter Number of Disk Requests : 8
Enter Disk Requests : 176 79 34 60 92 11 41 114
Enter initial Position of R/W head : 50
Enter Number of Tracks(Cylinder Size) : 200
Enter Direction (1 to Right, 2 to Left) : 2

50 -> 41 -> 34 -> 11 -> 0 -> 199 -> 176 -> 114 -> 92 -> 79 -> 60 ->

Seek Time(Head movement)    =  388
Average Seek Time           =  48.50

*/