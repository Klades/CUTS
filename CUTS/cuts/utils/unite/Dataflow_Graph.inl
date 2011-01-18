// $Id$


//
// CUTS_Dataflow_Graph
//
CUTS_INLINE
CUTS_Dataflow_Graph::CUTS_Dataflow_Graph (void)
: adapter_ (0)
{

}

//
// CUTS_Dataflow_Graph
//
CUTS_INLINE
CUTS_Dataflow_Graph::CUTS_Dataflow_Graph (const ACE_CString & name)
: name_ (name), adapter_ (0)
{

  this->normalize_name ();
}

//
// ~CUTS_Dataflow_Graph
//
CUTS_INLINE
CUTS_Dataflow_Graph::~CUTS_Dataflow_Graph (void)
{

}

//
// name
//
CUTS_INLINE
void CUTS_Dataflow_Graph::name (const ACE_CString & name)
{
  this->name_ = name;
  this->normalize_name ();
}

//
// name
//
CUTS_INLINE
const ACE_CString & CUTS_Dataflow_Graph::name (void) const
{
  return this->name_;
}

//
// create_log_format
//
CUTS_INLINE
bool CUTS_Dataflow_Graph::create_log_format (const ACE_CString & name)
{
  CUTS_Log_Format * format = 0;
  return this->create_log_format (name, format);
}

//
// get_log_format
//
CUTS_INLINE
CUTS_Log_Format *
CUTS_Dataflow_Graph::get_log_format (vertex_descriptor vertex) const
{
  return boost::get (CUTS_Unit_Test_Graph_Traits::log_format_t (),
                     this->graph_,
                     vertex);
}

//
// graph
//
CUTS_INLINE
const CUTS_Unit_Test_Graph_Type & CUTS_Dataflow_Graph::graph (void) const
{
  return this->graph_;
}