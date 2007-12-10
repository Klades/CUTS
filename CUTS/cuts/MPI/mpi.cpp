// $Id$

#include "mpi.h"
#include "MPI_Env.h"

//
// MPI_Init
//
int MPI_Init (int * argc, char *** argv)
{
  return CUTS_MPI_Env::instance ()->init (*argc, *argv);
}

//
// MPI_Finalize
//
int MPI_Finalize (void)
{
  int retval = CUTS_MPI_Env::instance ()->fini ();
  CUTS_MPI_Env::close_singleton ();

  return retval;
}
