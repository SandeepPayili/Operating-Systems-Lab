// First In First Out Page Replacement 
#include<stdio.h>
#include<limits.h>
int main()
{
    int n_p;
    int n_f;
    printf("Enter Number of Pages       : ");
    scanf(" %d",&n_p);
    printf("Enter Number of Frames      : ");
    scanf(" %d",&n_f);
    int frames[n_f];
    for(int i= 0;i<n_f;i++)
    {
        frames[i] = -1;
    }
    int pages[n_p];// page reference string
    printf("Enter Page Reference String : ");
    for(int i=0;i<n_p;i++)
    {
        scanf(" %d",&pages[i]);
    }
    int page_faults = 0;
    printf("\n\n");

    int queue_pointer = -1;
    for(int i=0;i<n_p;i++)
    {
        int flag = 0;
        for(int j=0;j<n_f;j++)
        {
            if(frames[j] == pages[i])
            {
                flag = 1;
                break;
            }
        }
        if(flag == 1) // page hit
        {
            printf("%d : ",pages[i]);
            for(int k=0;k<n_f;k++){
                if(frames[k] == -1)
                {
                    printf(" - ");
                    continue;    
                }
                printf(" %d ",frames[k]);
            }
            printf("\t\tHit\n");
        }else // page fault
        {
            queue_pointer = ((queue_pointer + 1)% n_f );
            frames[queue_pointer] = pages[i];
            printf("%d : ",pages[i]);
            for(int k=0;k<n_f;k++){
                if(frames[k] == -1)
                {
                    printf(" - ");
                    continue;    
                }
                printf(" %d ",frames[k]);
            }
            printf("\t\tFault   \n");
            page_faults++;
        }
    }
    printf("\n\nPage Faults =  %d\n\n",page_faults);
    return 0;
}
/*

Enter Number of Pages       : 12
Enter Number of Frames      : 4
Enter Page Reference String : 0 2 1 6 4 0 1 0 3 1 2 1


0 :  0  -  -  -                 Fault
2 :  0  2  -  -                 Fault
1 :  0  2  1  -                 Fault
6 :  0  2  1  6                 Fault
4 :  4  2  1  6                 Fault
0 :  4  0  1  6                 Fault
1 :  4  0  1  6                 Hit
0 :  4  0  1  6                 Hit
3 :  4  0  3  6                 Fault
1 :  4  0  3  1                 Fault
2 :  2  0  3  1                 Fault
1 :  2  0  3  1                 Hit


Page Faults =  9

*/