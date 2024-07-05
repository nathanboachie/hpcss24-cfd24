#include <stdio.h>
#include <mpi.h>

#include "boundary.h"

//grid is parallelised in the x direction

void boundarypsi(int m, int n, double psi[m+2][n+2], int b, int h, int w,
		 MPI_Comm comm)
{

  int size, rank,i,j;
  int istart, istop;

  MPI_Comm_size(comm,&size);
  MPI_Comm_rank(comm,&rank);

  istart = m*rank + 1;
  istop = istart + m -1;

  //BCs on bottom edge

  for (i=b+1;i<=b+w-1;i++)
    {
      if (i >= istart && i <= istop)
	{
	  psi[i-istart+1][0] = (double)(i-b);
        }
    }

  for (i=b+w;i<=m*size;i++)
    {
      if (i >= istart && i <= istop)
	{
	  psi[i-istart+1][0] = (double)(w);
	}
    }

  //BCS on RHS

  if (rank == size-1)
    {
      for (j=1; j <= h; j++)
	{
	  psi[m+1][j] = (double) w;
	}

      for (j=h+1;j<=h+w-1; j++)
	{
	  psi[m+1][j]=(double)(w-j+h);
	}
    }
}

void boundaryzet(int m, int n, double zet[m+2][n+2], double psi[m+2][n+2], MPI_Comm comm)
{
  int size, rank, i,j;

  MPI_Comm_rank(comm,&rank);
  MPI_Comm_size(comm,&size);

  //set top/bottom BCs:

  for (i=1;i<m+1;i++)
    {
      zet[i][0] = 2.0*(psi[i][1]-psi[i][0]);
      zet[i][n+1] = 2.0*(psi[i][n]-psi[i][n+1]);
    }

  //set left BC:
  if (rank == 0)
    {
      for (j=1;j<n+1;j++)
	{
	  zet[0][j] = 2.0*(psi[1][j]-psi[0][j]);
	}
    }

  //set left BCs

  if (rank == size-1)
    {
      for (j=1;j<n+1;j++)
	{
	  zet[m+1][j] = 2.0*(psi[m][j]-psi[m+1][j]);
	}
    }
}

void haloswap(int m, int  n, double x[m+2][n+2], MPI_Comm comm)
{
  int rank, size;
  int tag = 1;
  int dest;
  int src;

  MPI_Status status,status2;

  MPI_Comm_rank(comm,&rank);
  MPI_Comm_size(comm,&size);

  MPI_Request request;
  //no need to halo swap if serial:

  	if(size > 1)
  	{
      		//send right boundaries and receive left ones
      		dest=rank+1;
      		src=rank-1;
		if(rank !=size-1)
		{
      			MPI_Isend(&x[m][1],n,MPI_DOUBLE,dest,tag,comm,&request);
		}
		if(rank !=0)
		{
      			MPI_Recv(&x[0][1],n,MPI_DOUBLE,src,tag,comm,MPI_STATUS_IGNORE);
		}
		if(rank!=size-1)
		{
			MPI_Wait(&request,&status);
		}
     		 //send left boundary and receive right

      		dest=rank-1;
      		src=rank+1;
		if(rank !=0)
		{
      			MPI_Isend(&x[1][1],n,MPI_DOUBLE,dest,tag,comm,&request);
		}
		if(rank !=size-1)
		{
      			MPI_Recv(&x[m+1][1],n,MPI_DOUBLE,src,tag,comm,&status);
		}
		if(rank!=0)
		{
			MPI_Wait(&request,&status);
		}
  	}
}
