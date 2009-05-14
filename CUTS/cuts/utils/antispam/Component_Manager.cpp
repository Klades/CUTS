// $Id$

#include "Component_Manager.h"
#include "Component.h"
#include "ace/CORBA_macros.h"

//
// CUTS_Component_Manager
//
CUTS_Component_Manager::CUTS_Component_Manager (void)
{

}

//
// ~CUTS_Component_Manager
//
CUTS_Component_Manager::~CUTS_Component_Manager (void)
{
  //map_type::ITERATOR iter (this->map_);

  //for (; !iter.done (); ++ iter)
  //delete iter->item ();
}

//
// items
//
CUTS_Component_Manager::map_type & CUTS_Component_Manager::items (void)
{
  return this->map_;
}

//
// items
//
const CUTS_Component_Manager::map_type &
CUTS_Component_Manager::items (void) const
{
  return this->map_;
}

//
// create
//
int CUTS_Component_Manager::
create (const ACE_CString & name, CUTS_Component * & type)
{
  if (this->map_.find (name, type) == 0)
    return 0;

  CUTS_Component * temp = 0;
  ACE_NEW_THROW_EX (temp,
                    CUTS_Component (name),
                    ACE_bad_alloc ());

  ACE_Auto_Ptr <CUTS_Component> auto_clean (temp);

  int retval = this->map_.bind (name, temp);

  if (retval == 0)
    type = auto_clean.release ();

  return retval;
}
