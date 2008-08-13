// $Id$

#include "BE_Manager_Factory.h"

#if !defined (__CUTS_INLINE__)
#include "BE_Manager_Factory.inl"
#endif

#include "ace/DLL.h"
#include "ace/DLL_Manager.h"

//
// open
//
int CUTS_BE_Manager_Factory::
open (const char * module, CUTS_BE_Manager_Factory *& factory)
{
  ACE_DLL be_dll;

  if (be_dll.open (module, ACE_DEFAULT_SHLIB_MODE, 0) == 0)
  {
    typedef CUTS_BE_Manager_Factory * (* CREATION_FUNCTION) (void);

    // Load the creation function symbol from the loaded module.
    CREATION_FUNCTION creation_function =
      (CREATION_FUNCTION) be_dll.symbol (CUTS_BE_CREATE_MANAGER_FACTORY_STR);

    if (creation_function != 0)
    {
      // Create the factory using the loaded symbol.
      factory = (*creation_function) ();
      return 0;
    }

  }
  return -1;
}

//
// close
//
void CUTS_BE_Manager_Factory::close (void)
{
  delete this;
}

//
// name
//
const char * CUTS_BE_Manager_Factory::name (void) const
{
  return "No Name";
}

//
// description
//
const char * CUTS_BE_Manager_Factory::description (void) const
{
  return "No description provided";
}
