#include "Activemq_Adapter.h"
#include "ace/svc_export.h"
#include "ace/CORBA_macros.h"
#include "cuts/utils/unite/Log_Format.h"
#include "cuts/utils/unite/Variable.h"


//
// Init method
//
void Activemq_Adapter::init (void)
{
  this->id_ = 0;
}



//
// Reset method
//
void Activemq_Adapter::reset (void)
{
  this->id_ = 0;
}



//
// Close method
//
void Activemq_Adapter::close (void)
{

    delete this;
}



//
// update_log_format method
//
void Activemq_Adapter::update_log_format (CUTS_Log_Format * lfmt)
{

  // Get the name of the log format
  const ACE_CString & name = lfmt->name ();
  // Check whether this is an adaptive log format
  // The log format will be adapted by adding new variables
  if (name == "LF1")
  {
      this->add_variable (lfmt, "uid", "int");
  }

  else if (name == "LF2")
  {
      this->add_variable (lfmt, "uid", "int");
  }

  else
    return;
}


//
// update_log_format_relations method
//
void Activemq_Adapter::update_log_format_relations (CUTS_Log_Format * lfmt)
{

  // Get the name of the log format
  const ACE_CString & name = lfmt->name ();
  // Get the name of the log format
  // New causlilities will be created and added
  if (name == "LF1")
  {
      this->add_relation (lfmt, "LF2", "uid", "uid");
  }

  else
    return;
}


//
// update_log_format_variable_values method
//
bool Activemq_Adapter::update_log_format_variable_values (
    ACE_CString &key, CUTS_Log_Format_Variable *var, CUTS_Log_Format * lfmt)
{

  // This flag tells whether this need to be update further from the traces
  bool update_further = false;
  const ACE_CString & name = lfmt->name ();
  // If the log format variable is updated from the adapter
  // set the flag to false otherwise it will be true
  if (name == "LF1")
  {
    if(key == "uid")
    {

        this->id_ = this->id_ + 1;

        int32_var * ivar = dynamic_cast <int32_var *> (var);

        ivar->value (this->id_);
    }



    else
    {
      update_further = true;
    }
  }

  else if (name == "LF2")
  {
    update_further = false;
    if(key == "uid")
    {

        this->id_ = this->id_ + 1;

        int32_var * ivar = dynamic_cast <int32_var *> (var);

        ivar->value (this->id_);
    }



    else
    {
      update_further = true;
    }
  }

  else
  {
    update_further = true;
  }


  return update_further;
}

//
// create method
//
CUTS_Log_Format_Adapter  * create_Cuts_Log_Format_Adapter (void)
{
  CUTS_Log_Format_Adapter * adapter = 0;
  ACE_NEW_RETURN (adapter, Activemq_Adapter, 0);
  return adapter;
}

