#include <stdio.h>
#include <stdlib.h>
void setscore(){
		
		int i;
int HScore[5];
		FILE *fread, *fwrite;
		fread = fopen("NewScore.txt", "r");
                if (fread == NULL)
                {
                 printf("Error Reading File\n");
                 exit (0);
                 }
		for(i=0;i<5;i++)
		{
		fscanf(fread, "%d", &HScore[i]);
		}
                
		
		fwrite = fopen("NewScore.txt", "w");
		for(i=0;i<5;i++)
		{
                if (score*10 > HScore[i])
                {
                    int index=i;
                    int value=score*10;
                    int temp=0;
                  for(index;index<5;index++)
		   {
			   temp=HScore[index];
			   HScore[index]=value;
			   value=temp;

		   } 
                  break;

		  }
                  }
                  for(i=0;i<5;i++)
		   {
			   fprintf(fwrite, "%d", HScore[i]);
		   }
                  fclose(fread);
				  fclose(fwrite);
		
		
}