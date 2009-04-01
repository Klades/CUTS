// $Id$

//
// CUTS_Unit_Test_Graph
//
CUTS_INLINE
CUTS_Unit_Test_Graph::CUTS_Unit_Test_Graph (void)
{

}

//
// CUTS_Unit_Test_Graph
//
CUTS_INLINE
CUTS_Unit_Test_Graph::CUTS_Unit_Test_Graph (const ACE_CString & name)
: name_ (name)
{

}

//
// ~CUTS_Unit_Test_Graph
//
CUTS_INLINE
CUTS_Unit_Test_Graph::~CUTS_Unit_Test_Graph (void)
{

}

//
// graph
//
CUTS_INLINE
const CUTS_Unit_Test_Graph::graph_type
CUTS_Unit_Test_Graph::graph (void) const
{
  return this->graph_;
}

//
// name
//
CUTS_INLINE
void CUTS_Unit_Test_Graph::name (const ACE_CString & name)
{
  this->name_ = name;
}

//
// name
//
CUTS_INLINE
const ACE_CString & CUTS_Unit_Test_Graph::name (void) const
{
  return this->name_;
}

//
// log_format
//
CUTS_INLINE
const CUTS_Log_Format *
CUTS_Unit_Test_Graph::log_format (vertex_iterator iter) const
{
  return boost::get (CUTS_Unit_Test_Graph::log_format_t (),
                     this->graph_,
                     *iter);
}
