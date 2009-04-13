// $Id$

//
// CUTS_MPI_Datatype_Port_Manager
//
CUTS_INLINE
CUTS_MPI_Datatype_Port_Manager::
CUTS_MPI_Datatype_Port_Manager (CUTS_Benchmark_Agent * agent)
: agent_ (agent)
{
  this->init ();
}

//
// find_agent
//
CUTS_INLINE
int CUTS_MPI_Datatype_Port_Manager::
find (MPI_Datatype datatype, CUTS_Port_Agent * & agent) const
{
  return this->datatype_map_.find (datatype, agent);
}
