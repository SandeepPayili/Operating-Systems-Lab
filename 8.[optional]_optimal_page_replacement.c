// optimal page replacement
#include <stdio.h>
#include <limits.h>
int main()
{
	int n_p;
	printf("Enter Numer of Pages : ");
	scanf(" %d", &n_p);
	int n_f;
	printf("Enter Number of Frames : ");
	scanf(" %d", &n_f);
	int pages[n_p];
	printf("Enter Page Reference String : ");
	for (int i = 0; i < n_p; i++)
	{
		scanf(" %d", &pages[i]);
	}
	int frames[n_f];
	for (int i = 0; i < n_f; i++)
	{
		frames[i] = -1;
	}
	int page_faults = 0;
	for (int i = 0; i < n_p; i++)
	{
		printf("\n%d : ", pages[i]);
		int flag = 0;
		for (int j = 0; j < n_f; j++)
		{
			if (frames[j] == pages[i])
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)	//  page fault
		{
			page_faults++;
			int replacement_index = -1;
			for (int j = 0; j < n_f; j++)
			{
				if (frames[j] == -1)
				{
					replacement_index = j;
					break;
				}
			}
			if (replacement_index != -1)
			{
				frames[replacement_index] = pages[i];
				for (int k = 0; k < n_f; k++)
				{
					printf(" %3d ", frames[k]);
				}

				printf("   MISS ");
				continue;
			}
			int bool_first[n_f];
			int index_first[n_f];
			for (int j = 0; j < n_f; j++)
			{
				bool_first[j] = 1;
				index_first[j] = -1;
			}
			for (int j = 0; j < n_f; j++)
			{
				for (int k = i + 1; k < n_p; k++)
				{
					if (bool_first[j] == 1 && pages[k] == frames[j])
					{
						index_first[j] = k;
						bool_first[j] = 0;
					}
				}
			}

			replacement_index = -1;
			for (int j = 0; j < n_f; j++)
			{
				if (index_first[j] == -1)
				{
					replacement_index = j;
					break;
				}
			}
			if (replacement_index != -1)
			{
				frames[replacement_index] = pages[i];
				for (int k = 0; k < n_f; k++)
				{
					printf(" %3d ", frames[k]);
				}

				printf("   MISS ");
				continue;
			}

			int max_index = INT_MIN;
			for (int j = 0; j < n_f; j++)
			{
				if (index_first[j] > max_index)
				{
					max_index = index_first[j];
				}
			}

			
      for(int j=0;j<n_f;j++)
      {
        if(frames[j] == pages[max_index])
        {
          replacement_index = j;
        }
      }
      // printf("\n Max index = %d\n",max_index);
			frames[replacement_index] = pages[i];
      	for (int k = 0; k < n_f; k++)
				{
					printf(" %3d ", frames[k]);
				}

				printf("   MISS ");
		}
		else	// page hit
		{
			for (int k = 0; k < n_f; k++)
			{
				printf(" %3d ", frames[k]);
			}

			printf("   HIT ");
		}
	}

	printf("\nPage Faults = %d\n", page_faults);
	return 0;
}