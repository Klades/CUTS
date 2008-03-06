// $Id$

#include "BE_Manager_Factory_Repo.h"

#if !defined (__CUTS_INLINE__)
#include "BE_Manager_Factory_Repo.inl"
#endif

#include "BE_Manager_Factory.h"
#include "ace/DLL.h"
#include "ace/DLL_Manager.h"
#include <algorithm>

//
// load
//
bool CUTS_BE_Manager_Factory_Repo::
load (const std::string & id, 
      const std::string & module, 
      CUTS_BE_Manager_Factory * & factory)
{
  ACE_DLL be_dll;

  if (be_dll.open (module.c_str (), ACE_DEFAULT_SHLIB_MODE, 0) == 0)
  {
    // Load the creation function symbol from the loaded module.
    typedef CUTS_BE_Manager_Factory * (* CREATION_FUNCTION) (void);

    CREATION_FUNCTION creation_function =
      (CREATION_FUNCTION) be_dll.symbol (CUTS_BE_CREATE_MANAGER_FACTORY_STR);

    if (creation_function != 0)
    {
      // Create the factory using the loaded symbol. We then are going
      // to store the factory for later usage.
      factory = (*creation_function) ();
      this->path_map_.insert (std::make_pair (id, module));
      this->factories_.insert (std::make_pair (id, factory));

      return true;
    }
  }

  return false;
}

//
// unload
//
void CUTS_BE_Manager_Factory_Repo::unload (const char * name)
{
  // Locate the specified module.
  CUTS_BE_Manager_Factory_Set::
    iterator iter = this->factories_.find (name);

  if (iter != this->factories_.end ())
  {
    // Close the factory thereby releasing its resources
    if (iter->second)
      iter->second->close ();

    ACE_DLL_Manager::instance ()->
      close_dll (this->path_map_[iter->first].c_str ());

    // Remove the factory from the listing.
    this->path_map_.erase (iter->first);
    this->factories_.erase (iter);
  }
}

//
// find
//
bool CUTS_BE_Manager_Factory_Repo::
find (const char * name, CUTS_BE_Manager_Factory * &factory)
{
  CUTS_BE_Manager_Factory_Set::
    iterator iter = this->factories_.find (name);

  if (iter != this->factories_.end ())
  {
    factory = iter->second;
    return true;
  }
  else
    return false;
}

//
// unload_all
//
void CUTS_BE_Manager_Factory_Repo::unload_all (void)
{
  // Close all the factories in the listing.
  for (CUTS_BE_Manager_Factory_Set::iterator iter = this->factories_.begin ();
       iter != this->factories_.end ();
       iter ++)
  {
    if (iter->second)
      iter->second->close ();

    ACE_DLL_Manager::instance ()->
      close_dll (this->path_map_[iter->first].c_str ());
  }

  // Clear all the items in the listing.
  this->path_map_.clear ();
  this->factories_.clear ();
}
