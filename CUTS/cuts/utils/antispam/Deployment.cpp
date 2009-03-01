// $Id$

#include "Deployment.h"
#include "Host.h"
#include "ace/CORBA_macros.h"

//
// CUTS_Deployment
//
CUTS_Deployment::CUTS_Deployment (void)
{

}

//
// ~CUTS_Deployment
//
CUTS_Deployment::~CUTS_Deployment (void)
{
  map_type::ITERATOR iter (this->map_);

  for (; !iter.done (); ++ iter)
    delete iter->item ();
}

//
// items
//
CUTS_Deployment::map_type & CUTS_Deployment::items (void)
{
  return this->map_;
}

//
// items
//
const CUTS_Deployment::map_type &
CUTS_Deployment::items (void) const
{
  return this->map_;
}

//
// create
//
int CUTS_Deployment::
create (const ACE_CString & name, CUTS_Host * & type)
{
  if (this->map_.find (name, type) == 0)
    return 0;

  CUTS_Host * temp = 0;

  ACE_NEW_THROW_EX (temp,
                    CUTS_Host (),
                    ACE_bad_alloc ());

  ACE_Auto_Ptr <CUTS_Host> auto_clean (temp);

  int retval = this->map_.bind (name, temp);

  if (retval == 0)
    type = auto_clean.release ();

  return retval;
}
