// -*- C++ -*-

//=============================================================================
/**
 * @file      calibration.cpp
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#include "Calibrate_App.h"
#include "ace/Null_Mutex.h"
#include "ace/Singleton.h"

/// Helper for using the options as a singleton.
#define CUTS_CALIBRATE_APP() \
  ACE_Singleton <CUTS_Calibrate_App, ACE_Null_Mutex>::instance ()

//
// main
//
int main (int argc, char * argv [])
{
  try
  {
    return CUTS_CALIBRATE_APP ()->run_main (argc, argv);
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - caught known exception\n"));
  }

  return 1;
}
