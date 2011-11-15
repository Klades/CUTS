// $Id$

#include "mpi.h"
#include "boost/test/unit_test.hpp"
#include "ace/OS_NS_unistd.h"

namespace MPI
{
  int argc = 0;
  char ** argv = 0;
}

//=============================================================================
/*
 * Unit_Test: CUTS_MPI_Init
 */
//=============================================================================

void CUTS_MPI_Init (void)
{
  BOOST_CHECK (MPI_Init (&MPI::argc, &MPI::argv) == 0);
  ACE_OS::sleep (20);
}

//=============================================================================
/*
 * Unit_Test: CUTS_MPI_Finalize
 */
//=============================================================================

void CUTS_MPI_Finalize (void)
{
  BOOST_CHECK (MPI_Finalize () == 0);
}

//
// init_unit_test_suite
//
boost::unit_test::test_suite *
init_unit_test_suite (int argc, char * argv [])
{
  boost::unit_test::test_suite * ts =
    BOOST_TEST_SUITE ("CUTS_MPI");

  // Save the command-line arguments for the unit test.
  MPI::argc = argc;
  MPI::argv = argv;

  // Add the unit test to the test suite.
  ts->add (BOOST_TEST_CASE (&CUTS_MPI_Init));
  ts->add (BOOST_TEST_CASE (&CUTS_MPI_Finalize));

  return ts;
}
