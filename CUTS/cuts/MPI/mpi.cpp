// $Id$

#include "mpi.h"
#include "MPI_Env.h"
#include "ace/streams.h"

//
// MPI_Init
//
int MPI_Init (int * argc, char *** argv)
{
  int retval = PMPI_Init (argc, argv);
  return CUTS_MPI_Env::instance ()->init (*argc, *argv);
}

//
// MPI_Finalize
//
int MPI_Finalize (void)
{
  int retval = CUTS_MPI_Env::instance ()->fini ();
  CUTS_MPI_Env::close_singleton ();

  return PMPI_Finalize ();
}

//
// MPI_Recv
//
int MPI_Recv (void * buf,
              int count,
              MPI_Datatype datatype,
              int source,
              int tag,
              MPI_Comm comm,
              MPI_Status *status)
{
  std::cout << "entered MPI_Recv" << std::endl;
  return PMPI_Recv (buf, count, datatype, source, tag, comm, status);
}

//
// MPI_Send
//
int MPI_Send (void * buf,
              int count,
              MPI_Datatype datatype,
              int dest,
              int tag,
              MPI_Comm comm)
{
  std::cout << "entered MPI_Send" << std::endl;
  return PMPI_Send (buf, count, datatype, dest, tag, comm);
}
