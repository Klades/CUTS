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
// agent
//
CUTS_INLINE
Benchmark_Agent_i * CUTS_MPI_Env::agent (void)
{
  return this->agent_;
}

//
// instance_name
//
CUTS_INLINE
const ACE_CString & CUTS_MPI_Env::instance_name (void) const
{
  return this->instance_name_;
}
