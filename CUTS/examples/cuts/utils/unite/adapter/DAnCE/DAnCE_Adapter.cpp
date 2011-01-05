#include "DAnCE_Adapter.h"
#include "ace/svc_export.h"
#include "ace/CORBA_macros.h"
#include "cuts/utils/unite/Log_Format.h"
#include "cuts/utils/unite/Variable.h"


//
// Init method
//
void DAnCE_Adapter::init (void)
{
  this->lf13_update_count_ = 0;
}



//
// Reset method
//
void DAnCE_Adapter::reset (void)
{
  this->lf13_update_count_ = 0;
}



//
// Close method
//
void DAnCE_Adapter::close (void)
{

    delete this;
}



//
// update_log_format method
//
void DAnCE_Adapter::update_log_format (CUTS_Log_Format * lfmt)
{

  // Get the name of the log format
  const ACE_CString & name = lfmt->name ();
  // Check whether this is an adaptive log format
  // The log format will be adapted by adding new variables
  if (name == "LF1")
  {
      this->add_variable (lfmt, "planid", "string");
  }

  else if (name == "LF2")
  {
      this->add_variable (lfmt, "planid", "string");
  }

  else if (name == "LF5")
  {
      this->add_variable (lfmt, "planid", "string");
  }

  else if (name == "LF6")
  {
      this->add_variable (lfmt, "planid", "string");
  }

  else if (name == "LF9")
  {
      this->add_variable (lfmt, "planid", "string");
  }

  else if (name == "LF11")
  {
      this->add_variable (lfmt, "planid", "string");
  }

  else if (name == "LF13")
  {
      this->add_variable (lfmt, "node", "string");
  }

  else
    return;
}


//
// update_log_format_relations method
//
void DAnCE_Adapter::update_log_format_relations (CUTS_Log_Format * lfmt)
{

  // Get the name of the log format
  const ACE_CString & name = lfmt->name ();
  // Get the name of the log format
  // New causlilities will be created and added
  if (name == "LF1")
  {
      this->add_relation (lfmt, "LF2", "planid", "planid");
  }

  else if (name == "LF5")
  {
      this->add_relation (lfmt, "LF6", "planid", "planid");
  }

  else if (name == "LF6")
  {
      this->add_relation (lfmt, "LF7", "planid", "planid");
  }

  else if (name == "LF8")
  {
      this->add_relation (lfmt, "LF9", "planid", "planid");
  }

  else if (name == "LF9")
  {
      this->add_relation (lfmt, "LF10", "planid", "planid");
  }

  else if (name == "LF10")
  {
      this->add_relation (lfmt, "LF11", "planid", "planid");
  }

  else if (name == "LF11")
  {
      this->add_relation (lfmt, "LF12", "planid", "planid");
  }

  else if (name == "LF12")
  {
      this->add_relation (lfmt, "LF13", "node", "node");
  }

  else
    return;
}


//
// update_log_format_variable_values method
//
bool DAnCE_Adapter::update_log_format_variable_values (
    ACE_CString &key, CUTS_Log_Format_Variable *var, CUTS_Log_Format * lfmt)
{

  // This flag tells whether this need to be update further from the traces
  bool update_further = false;
  const ACE_CString & name = lfmt->name ();
  // If the log format variable is updated from the adapter
  // set the flag to false otherwise it will be true
  if (name == "LF1")
  {
    if(key == "planid")
    {

        var->value("BasicSP_Unhomed");
    }



    else
    {
      update_further = true;
    }
  }

  else if (name == "LF2")
  {
    update_further = false;
    if(key == "planid")
    {

        var->value("BasicSP_Unhomed");
    }



    else
    {
      update_further = true;
    }
  }

  else if (name == "LF5")
  {
    update_further = false;
    if(key == "planid")
    {

        var->value("BasicSP_Unhomed");
    }



    else
    {
      update_further = true;
    }
  }

  else if (name == "LF6")
  {
    update_further = false;
    if(key == "planid")
    {

        var->value("BasicSP_Unhomed");
    }



    else
    {
      update_further = true;
    }
  }

  else if (name == "LF9")
  {
    update_further = false;
    if(key == "planid")
    {

        var->value("BasicSP_Unhomed");
    }



    else
    {
      update_further = true;
    }
  }

  else if (name == "LF11")
  {
    update_further = false;
    if(key == "planid")
    {

        var->value("BasicSP_Unhomed");
    }



    else
    {
      update_further = true;
    }
  }

  else if (name == "LF13")
  {
    update_further = false;
    if(key == "node")
    {

        if (this->lf13_update_count_ == 0)
          var->value ("EC");

        else if (this->lf13_update_count_ == 1)
          var->value ("BMDevice");

        else if (lf13_update_count_ == 2)
          var->value ("BMClosedED");

        else if(lf13_update_count_ == 3)
          var->value ("BMDisplay");

        this->lf13_update_count_ = this->lf13_update_count_ + 1;

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
  ACE_NEW_RETURN (adapter, DAnCE_Adapter, 0);
  return adapter;
}

