// $Id$

//
// CUTS_MPI_Env
//
CUTS_INLINE
CUTS_MPI_Env::CUTS_MPI_Env (void)
: agent_ (0),
  grp_id_ (-1)
{

}

//
// ~CUTS_MPI_Env
//
CUTS_INLINE
CUTS_MPI_Env::~CUTS_MPI_Env (void)
{
  this->fini ();
}

//
// instance_name
//
CUTS_INLINE
const ACE_CString & CUTS_MPI_Env::instance_name (void) const
{
  return this->instance_name_;
}

//
// datatype_mgr
//
CUTS_INLINE
CUTS_MPI_Datatype_Port_Manager &
CUTS_MPI_Env::datatype_mgr (void)
{
  return *this->datatype_mgr_;
}

//
// datatype_mgr
//
CUTS_INLINE
const CUTS_MPI_Datatype_Port_Manager &
CUTS_MPI_Env::datatype_mgr (void) const
{
  return *this->datatype_mgr_;
}

//
// timer
//
CUTS_INLINE
ACE_High_Res_Timer & CUTS_MPI_Env::timer (void)
{
  return this->timer_;
}
