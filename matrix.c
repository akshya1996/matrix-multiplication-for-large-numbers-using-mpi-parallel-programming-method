/*
 *Akshya Srinivasa Raghavan
 *1001547268
 *axs7268
 *
 *
 *
 *
 *Compilation Steps: ./job2.sh
 *
 *
 *
 *
 */

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    int world_rank, world_size,namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int  filestatus = 1;// to check if data.txt file has been read or not
    MPI_Status status;
    int n;
    int m;
    int p;
    //int *a[n];
    int *a;
    FILE *fp;
    //int *b[m];
    int *b;
   double start_time;
   double end_time;
   double actual_time;
    MPI_Init(&argc,&argv);
    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD,&world_size);
    // Get the rank of the processa[irpow]=M
    MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
    
//reading the file
 	if(world_rank==0)
 	{	
		
		if ((fp = fopen ("data.txt", "r")) == NULL)
		{
    		filestatus = 0;
		}
		if(filestatus != 0)
	 	{
		int irow,icol,i,j;
   		fscanf(fp, "%d\n", &n);
		printf("%d\n",n);
	        a=(int *)malloc(n*n*sizeof(int));
  		for (irow = 0; irow < n; irow++)
			{
     				//a[irow]=malloc(n*sizeof(int*));                            
       		 		for (icol = 0; icol < n; icol++)
				{
     		  		fscanf(fp, "%d", &a[irow*n+icol]);
				//mata[irow][icol]=a[irow][icol];
				}
   			}   	
	        b=(int *)malloc(n*n*sizeof(int));	
   		for(i = 0; i < n; i++)
			{
				//b[i]=malloc(n*sizeof(int*));
   				 for(j = 0; j < n; j++)
				 {
     				 fscanf(fp, "%d", &b[i*n+j]);
				 //matb[i][j]=b[i][j];
				 }
				 
 			 }

  		fclose(fp);
                 }
			 
	int irow,icol;
	//printing matrix a and b
	printf("Matrix A :\n");
	for (irow = 0; irow < n ; irow++)
			{
       		 		for (icol = 0; icol < n; icol++)
     		  		printf("%d\t", a[irow*n+icol]);
				printf("\n");
   			}
	printf("\n");
	printf("Matrix B:\n");
	for(irow = 0; irow < n; irow++)
			{
   				 for(icol = 0; icol < n; icol++)
     				 printf("%d\t", b[irow*n+icol]);

				 printf("\n");
			}
	
	}

MPI_Barrier(MPI_COMM_WORLD);
	start_time=MPI_Wtime();
//	printf("Start Time=%f\n",start_time);


	//Broadcasting the value of n to all the processes
MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
//MPI_Bcast(b,n*n,MPI_INT,0,MPI_COMM_WORLD);
if(world_rank!=0)
{
	b=(int *) malloc(n*n*sizeof(int *));
}
//printf("Value of n:%d\n",n);
int rsize=n/world_size;
//printf("Rsize:%d\n",rsize);
 int irow,q,s;
 int *blockC;
 blockC=(int *) malloc( rsize*n*sizeof(int *));

 int *blockA;
 blockA=(int *)malloc(rsize*n*sizeof(int *));
 //scattering each block of matrix a
if(MPI_Scatter(a,rsize*n,MPI_INT,blockA,rsize*n,MPI_INT,0,MPI_COMM_WORLD)!=MPI_SUCCESS)
{
	printf("Scatter Error\n");
}

int *final_mat;
final_mat=(int *)malloc(n*n*sizeof(int *));
//Matrix B
//printf("A matrix after we broadcast\n");
int i,j,k;
//Broadcasting b matrix to all the processes
MPI_Bcast(b,n*n,MPI_INT,0,MPI_COMM_WORLD);
//printf("Broadcasted B matrix\n");
/*for(i=0;i<n;i++)
{
	for(j=0;j<n;j++)
	{
		printf("%d\t",b[i*n+j]);
	}
	printf("\n");
	
}
*/
//MPI_Bcast(b,n*n,MPI_INT,0,MPI_COMM_WORLD);
//multiplying each block A with block C and storing the value
    for(i=0;i<rsize;i++)
    {
	    for(j=0;j<n;j++)
	    {
		    blockC[i*n+j]=0;
		    for(k=0;k<n;k++)
		    {
	blockC[i*n+j]=blockC[i*n+j]+(blockA[i*n+k]*(b[k*n+j]));
	//		printf("A:%d\n",blockA[i*n+k]);
	                //  printf("C:%d\n",blockC[i*n+j]);
			//printf("B:%d\n",b[k*n+j]);
	    }

	    }
  }
    
 //   MPI_Get_processor_name(processor_name,&namelen);
  //  printf("Hello world from processor %s, rank %d out of %d processors\n",processor_name, world_rank, world_size);
MPI_Gather(blockC,rsize*n,MPI_INT,final_mat,rsize*n,MPI_INT,0,MPI_COMM_WORLD);
//printf("All gather done\n");
//if(world_rank==0)
{
//MPI_Barrier(MPI_COMM_WORLD);
//end_time=MPI_Wtime();
//printf("End Time:%f\n",end_time);
//actual_time=end_time-start_time;
//printf("Time taken=%f\n",actual_time);

}
//printf("Final Result:\n");
//printing the final result
if(world_rank==0)
{
	printf("Final Result\n");
for(i=0;i<n;i++)
{
	for(j=0;j<n;j++)
	{
		printf("%d\t",final_mat[i*n+j]);

	}
	printf("\n");
}
}


MPI_Barrier(MPI_COMM_WORLD);
end_time=MPI_Wtime();
if(world_rank==0)
{
//printf("End Time:%f\n",end_time);
actual_time=end_time-start_time;
printf("Time taken=%f\n",actual_time);
}

    MPI_Finalize();
    return 0;
 
}
