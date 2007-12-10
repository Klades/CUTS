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
