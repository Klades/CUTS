// $Id$

//=============================================================================
/**
 * @file        uuidgen.cpp
 *
 * $Id$
 *
 * @author      James H. Hill <hillj@isis.vanderbilt.edu>
 */
//=============================================================================

#include "ace/streams.h"
#include "ace/UUID.h"

//
// ACE_TMAIN
//
int ACE_TMAIN (int argc, char * argv [])
{
  // Initialize the UUID generator.
  ACE_Utils::UUID_GENERATOR::instance ()->init ();

  // Generator a new UUID
  ACE_Utils::UUID uuid;
  ACE_Utils::UUID_GENERATOR::instance ()->generate_UUID (uuid);

  // Write the UUID to the console
  std::cout << uuid.to_string ()->c_str () << std::endl;

  return 0;
}
