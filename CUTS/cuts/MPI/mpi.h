// $Id$

//=============================================================================
/**
 * @file          mpi.h
 *
 * Defines CUTS wrappers for the MPI functions. This allows us to adapt
 * the CUTS benchmarking framework to MPI.
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_MPI_H_
#define _CUTS_MPI_H_

#include "cuts/config.h"
#include "mpi_export.h"

extern "C"
{
  int CUTS_MPI_Export MPI_Init (int * argc, char *** argv);
  int CUTS_MPI_Export MPI_Finalize (void);
}

#endif  // !defined _CUTS_MPI_H_
