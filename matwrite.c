#include <stdio.h>
#include <stdlib.h>
int main()
{
   int num;
   int i, j;
   FILE *fptr;
   fptr = fopen("input.txt","w");

   if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }
num=512;//dimensions of the matrix
int val=2;
      fprintf(fptr,"%d\n",num);
      fprintf(fptr,"\n");
      for(i=0;i<num;i++)
      {
	      for(j=0;j<num;j++)
	      {
		      fprintf(fptr,"%d\t",val);
	      }
	      fprintf(fptr,"\n");
      }
      fprintf(fptr,"\n");
for(i=0;i<num;i++)
      {
	      for(j=0;j<num;j++)
	      {
		      fprintf(fptr,"%d\t",val);
	      }
	      fprintf(fptr,"\n");
      }

   fclose(fptr);

   return 0;
}
