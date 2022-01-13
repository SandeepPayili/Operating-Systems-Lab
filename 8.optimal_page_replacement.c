// optimal page replacement
#include<stdio.h>
int main()
{
    int n_p;
    printf("Enter Number of Pages : ");
    scanf(" %d",&n_p);
    int n_f;
    printf("Enter Number of Frames : ");
    scanf(" %d",&n_f);
    int pages[n_p];
    int frames[n_f];
    printf("Enter Page Reference String : ");
    for(int i=0;i<n_p;i++)
    {
        scanf(" %d",&pages[i]);
    }
    for(int i=0;i<n_f;i++)
    {
        frames[i] = -1;
    }
    int page_hits = 0;
    int page_faults = 0;
    for(int i=0;i<n_p;i++)
    {
        printf("\n%3d : ",pages[i]);
        int flag = 0;
        for(int j=0;j<n_f;j++)
        {
            if(pages[i] == frames[j])
            {
                flag = 1;
                break;
            }
        }
        if( flag == 1) // page hit
        {
            page_hits++;
            for(int j=0;j<n_f;j++){
                printf(" %3d ",frames[j]);
            }
            printf("\tHIT");
        }
        else
        {
            page_faults++;
            // frames are empty
            int empty_flag = 0;
            int empty_frame_index = -1;
            for(int j= 0;j<n_f;j++)
            {
                if(frames[j] == -1)
                {
                   empty_flag = 1;
                   empty_frame_index = j;
                   break;
                }
            }
            if(empty_flag == 1)
            {
                    frames[empty_frame_index] = pages[i];
                    for(int k= 0;k<n_f;k++)
                    {
                        printf(" %3d ",frames[k]);
                    }
                    printf("\tMISS");
            }
            else
            {
                    // replace page
                    int pos = -1;//to find optimal position
                    int index = -1; // index  of frame array to replace with page
                    for(int j=0;j<n_f;j++)
                    {
                        int found = 0;
                        for(int k = i+1;k<n_p;k++)
                        {
                            if(frames[j] == pages[k])
                            {
                                found = 1;
                                if( k > pos )
                                {
                                    pos  = k;
                                    index = j;
                                }
                                break; // must to ensure first match
                            }
                        }
                        if( found == 0)
                        {
                            pos = n_p;
                            index = j;
                        }
                    }
                    frames[index] = pages[i];
                    for(int j=0;j<n_f;j++)
                    {
                        printf(" %3d ",frames[j]);
                    }
                    printf("\tMISS");
            }
            
        }
    }
    printf("\n\nPage Hits   = %3d\n",page_hits);
    printf("\nPage Faults  = %3d\n",page_faults);
    return 0;
}
/*

Enter Number of Pages : 19
Enter Number of Frames : 3
Enter Page Reference String : 3 2 1 3 4 1 6 2 4 3 4 2 1 4 5 2 1 3 4

  3 :    3   -1   -1    MISS
  2 :    3    2   -1    MISS
  1 :    3    2    1    MISS
  3 :    3    2    1    HIT
  4 :    4    2    1    MISS
  1 :    4    2    1    HIT
  6 :    4    2    6    MISS
  2 :    4    2    6    HIT
  4 :    4    2    6    HIT
  3 :    4    2    3    MISS
  4 :    4    2    3    HIT
  2 :    4    2    3    HIT
  1 :    4    2    1    MISS
  4 :    4    2    1    HIT
  5 :    5    2    1    MISS
  2 :    5    2    1    HIT
  1 :    5    2    1    HIT
  3 :    5    2    3    MISS
  4 :    5    2    4    MISS

Page Hits   =   9

Page Faults  =  10
*/