// Shortest Seek Time First
#include<stdio.h>
#include<stdlib.h> // for abs and 1e9
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
    for(int i=0;i<n;i++)
    {
        scanf(" %d",&req[i].request_track_number);
        req[i].visited = 0;
    }
    int initial_head;
    printf("Enter initial Position of R/W head : ");
    scanf(" %d",&initial_head);
    int seek_time = 0;
    printf("\n%d -> ",initial_head);
    int c = 0;
    while(c<n)
    {
        int min = 1e9; // 10 power 9
        int min_track_number,position;
        for(int i=0;i<n;i++)
        {
            if(abs(initial_head - req[i].request_track_number) < min && req[i].visited == 0)
            {
                min = abs(initial_head - req[i].request_track_number);
                min_track_number = req[i].request_track_number;
                position = i;
            }
        }
        initial_head = req[position].request_track_number;
        req[position].visited = 1;
        printf("%d -> ",min_track_number);
        seek_time+= min;
        c++;
    }
    printf("\n\nSeek Time(Head movement)    = %d",seek_time);
    printf("\nAverage Seek Time           =  %.2f\n",(float)seek_time/n);
    return 0;
}
/*

Enter Number of Disk Requests : 7
Enter Disk Requests : 82 170 43 140 24 16 190
Enter initial Position of R/W head : 50

50 -> 43 -> 24 -> 16 -> 82 -> 140 -> 170 -> 190 ->

Seek Time(Head movement)    = 208
Average Seek Time           =  29.71

*/