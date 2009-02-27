// $Id$

#include "Unit_Test.h"
#include "Unit_Test_Graph.h"
#include "Log_Format.h"
#include "ace/CORBA_macros.h"

//
// CUTS_Unit_Test
//
CUTS_Unit_Test::CUTS_Unit_Test (void)
: name_ ("noname"),
  graph_ (0)
{
  ACE_NEW_THROW_EX (this->graph_,
                    CUTS_Unit_Test_Graph (),
                    ACE_bad_alloc ());
}

//
// CUTS_Unit_Test
//
CUTS_Unit_Test::CUTS_Unit_Test (const ACE_CString & name)
: name_ (name),
  graph_ (0)
{
  ACE_NEW_THROW_EX (this->graph_,
                    CUTS_Unit_Test_Graph (),
                    ACE_bad_alloc ());
}

//
// ~CUTS_Unit_Test
//
CUTS_Unit_Test::~CUTS_Unit_Test (void)
{
  formats_type::ITERATOR iter (this->formats_);

  for ( ; !iter.done (); ++ iter)
    delete iter->item ();

  if (this->graph_ != 0)
    delete this->graph_;
}

//
// name
//
const ACE_CString & CUTS_Unit_Test::name (void) const
{
  return this->name_;
}

//
// name
//
void CUTS_Unit_Test::name (const ACE_CString & n)
{
  this->name_ = n;
}

//
// aggregation
//
const ACE_CString & CUTS_Unit_Test::aggregation (void) const
{
  return this->aggr_;
}

//
// aggregation
//
void CUTS_Unit_Test::aggregation (const ACE_CString & aggr)
{
  this->aggr_ = aggr;
}

//
// evaluation
//
const ACE_CString & CUTS_Unit_Test::evaluation (void) const
{
  return this->evaluation_;
}

//
// evaluation
//
void CUTS_Unit_Test::evaluation (const ACE_CString & eval)
{
  this->evaluation_ = eval;
}

//
// create_log_format
//
bool CUTS_Unit_Test::
create_log_format (const ACE_CString & name)
{
  CUTS_Log_Format * format = 0;
  return this->create_log_format (name, format);
}

//
// create_log_format
//
bool CUTS_Unit_Test::
create_log_format (const ACE_CString & name, CUTS_Log_Format *& format)
{
  if (this->formats_.find (name, format) == 0)
    return true;

  // Allocate a new log format.
  CUTS_Log_Format * temp = 0;
  ACE_NEW_RETURN (temp, CUTS_Log_Format (name), false);
  ACE_Auto_Ptr <CUTS_Log_Format> auto_clean (temp);

  // Store the log format in the hash map.
  int retval = this->formats_.bind (name, temp);

  if (retval != 0)
    return false;

  format = auto_clean.release ();

  // Insert the log format into the graph
  return this->graph_->insert (format);
}

//
// associate
//
bool CUTS_Unit_Test::
associate (const ACE_CString & cause, const ACE_CString & effect)
{
  return this->graph_->connect (cause, effect);
}

//
// graph
//
const CUTS_Unit_Test_Graph * CUTS_Unit_Test::graph (void) const
{
  return this->graph_;
}

//
// log_formats
//
const CUTS_Unit_Test::formats_type & CUTS_Unit_Test::log_formats (void) const
{
  return this->formats_;
}

//
// groupings
//
const CUTS_Unit_Test::grouping_type & CUTS_Unit_Test::groupings (void) const
{
  return this->grouping_;
}

//
// groupings
//
CUTS_Unit_Test::grouping_type & CUTS_Unit_Test::groupings (void)
{
  return this->grouping_;
}

