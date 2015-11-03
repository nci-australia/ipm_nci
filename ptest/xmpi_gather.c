
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

#define COUNT     10
#define DATATYPE  MPI_DOUBLE
#define ROOT      0
#define REPEAT    1

int main( int argc, char* argv[] )
{
  int i, j;
  int myrank, nprocs;
  char *sbuf,  *rbuf;
  int dsize;

  MPI_Init( &argc, &argv );

  MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
  MPI_Comm_size( MPI_COMM_WORLD, &nprocs );
  PMPI_Type_size(DATATYPE, &dsize);

  rbuf=0;
  if( myrank==ROOT )
    {
      rbuf=(char*)malloc(COUNT*nprocs*dsize);
    }
  sbuf=(char*)malloc(COUNT*dsize);

  for( i=0; i<REPEAT; i++ )
    {
      MPI_Gather( sbuf, COUNT, DATATYPE,
		  rbuf, (myrank==ROOT?COUNT:0), DATATYPE,
		  ROOT, MPI_COMM_WORLD );
    } 
   
  fprintf(stdout, "DONE (rank %d)!\n", myrank);
  
  MPI_Finalize();
}
