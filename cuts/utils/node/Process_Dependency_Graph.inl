// -*- C++ -*-
// $Id$

//
// CUTS_Process_Dependency_Graph
//
CUTS_INLINE
CUTS_Process_Dependency_Graph::CUTS_Process_Dependency_Graph (void)
{

}

//
// CUTS_Process_Dependency_Graph
//
CUTS_INLINE
CUTS_Process_Dependency_Graph::CUTS_Process_Dependency_Graph (size_t vertices)
: graph_type (vertices)
{

}

//
// ~CUTS_Process_Dependency_Graph
//
CUTS_INLINE
CUTS_Process_Dependency_Graph::~CUTS_Process_Dependency_Graph (void)
{

}

//
// insert
//
CUTS_INLINE
int CUTS_Process_Dependency_Graph::
insert (const char * name, CUTS_Process_Options * opts)
{
  return this->insert (ACE_CString (name), opts);
}

//
// connect
//
CUTS_INLINE
int CUTS_Process_Dependency_Graph::
connect (const char * src_name, const char * dst_name)
{
  return this->connect (ACE_CString (src_name), ACE_CString (dst_name));
}
