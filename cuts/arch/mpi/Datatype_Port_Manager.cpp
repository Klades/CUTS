// $Id$

#include "Datatype_Port_Manager.h"

#if !defined (__CUTS_INLINE__)
#include "Datatype_Port_Manager.inl"
#endif

#include "cuts/Port_Agent.h"
#include "cuts/Benchmark_Agent.h"

//
// get
//
CUTS_Port_Agent *
CUTS_MPI_Datatype_Port_Manager::get (MPI_Datatype datatype)
{
  CUTS_Port_Agent * agent = 0;
  if (this->find (datatype, agent) == 0)
    return agent;

  this->install (datatype, &agent);
  return agent;
}

//
// ~CUTS_MPI_Datatype_Port_Manager
//
CUTS_MPI_Datatype_Port_Manager::~CUTS_MPI_Datatype_Port_Manager (void)
{
  MPI_Datatype_Map::ITERATOR iter (this->datatype_map_);

  for (; !iter.done (); iter ++)
    delete iter->item ();
}

//
// init
//
int CUTS_MPI_Datatype_Port_Manager::init (void)
{
  // Right now, we are going to load all the predefined types into
  // the hash map. In the near future, it may be worthwhile to use
  // an array for predefined types an a hash map for user-defined
  // datatypes.
  this->install (MPI_CHAR, "MPI_CHAR");
  this->install (MPI_SIGNED_CHAR, "MPI_SIGNED_CHAR");
  this->install (MPI_BYTE, "MPI_BYTE");
  this->install (MPI_WCHAR, "MPI_WCHAR");
  this->install (MPI_SHORT, "MPI_SHORT");
  this->install (MPI_UNSIGNED_SHORT, "MPI_UNSIGNED_SHORT");
  this->install (MPI_INT, "MPI_INT");
  this->install (MPI_UNSIGNED, "MPI_UNSIGNED");
  this->install (MPI_LONG, "MPI_LONG");
  this->install (MPI_SIGNED_CHAR, "MPI_SIGNED_CHAR");
  this->install (MPI_UNSIGNED_LONG, "MPI_UNSIGNED_LONG");
  this->install (MPI_FLOAT, "MPI_FLOAT");
  this->install (MPI_DOUBLE, "MPI_DOUBLE");
  this->install (MPI_LONG_DOUBLE, "MPI_LONG_DOUBLE");
  this->install (MPI_LONG_LONG_INT, "MPI_LONG_LONG_INT");
  this->install (MPI_UNSIGNED_LONG_LONG, "MPI_UNSIGNED_LONG_LONG");
  this->install (MPI_LONG_LONG, "MPI_LONG_LONG");
  return 0;
}

//
// install
//
int CUTS_MPI_Datatype_Port_Manager::
install (MPI_Datatype datatype, CUTS_Port_Agent ** agent)
{
  // Create a new datatype.
  CUTS_Port_Agent * temp = 0;
  ACE_NEW_RETURN (temp, CUTS_Port_Agent (), -1);

  // Add the datatype the listings.
  this->datatype_map_.bind (datatype, temp);
  this->agent_->register_agent (temp, datatype);

  // Return the agent the caller, if necessary.
  if (agent != 0)
    *agent = temp;

  return 0;
}

//
// install
//
int CUTS_MPI_Datatype_Port_Manager::
install (MPI_Datatype datatype,
         const ACE_CString & name,
         CUTS_Port_Agent ** agent)
{
  int retval = this->install (datatype, agent);

  if (retval == 0 && agent != 0)
    (*agent)->name (name);

  return retval;
}
