#include "Tomcat_Adapter.h"
#include "ace/svc_export.h"
#include "ace/CORBA_macros.h"
#include "cuts/utils/unite/Log_Format.h"
#include "cuts/utils/unite/Variable.h"


//
// Init method
//
void Tomcat_Adapter::init (void)
{

  /* Your Initialization code here */
}



//
// Reset method
//
void Tomcat_Adapter::reset (void)
{

  /* Your Resetting code here */
}



//
// Close method
//
void Tomcat_Adapter::close (void)
{

    delete this;
}



//
// update_log_format method
//
void Tomcat_Adapter::update_log_format (CUTS_Log_Format * lfmt)
{

  // Get the name of the log format
  const ACE_CString & name = lfmt->name ();
  // Check whether this is an adaptive log format
  // The log format will be adapted by adding new variables
  if (name == "LF1")
  {
      this->add_variable (lfmt, "ServerName", "string");
  }

  else if (name == "LF2")
  {
      this->add_variable (lfmt, "ServerName", "string");
  }

  else if (name == "LF3")
  {
      this->add_variable (lfmt, "ServerName", "string");
  }

  else if (name == "LF4")
  {
      this->add_variable (lfmt, "ServerName", "string");
  }

  else if (name == "LF5")
  {
      this->add_variable (lfmt, "ServerName", "string");
  }

  else if (name == "LF6")
  {
      this->add_variable (lfmt, "ServerName", "string");
  }

  else if (name == "LF7")
  {
      this->add_variable (lfmt, "ServerName", "string");
  }

  else if (name == "LF8")
  {
      this->add_variable (lfmt, "ServerName", "string");
  }

  else if (name == "LF9")
  {
      this->add_variable (lfmt, "ServerName", "string");
  }

  else if (name == "LF10")
  {
      this->add_variable (lfmt, "ServerName", "string");
  }

  else if (name == "LF11")
  {
      this->add_variable (lfmt, "ServerName", "string");
  }

  else if (name == "LF12")
  {
      this->add_variable (lfmt, "ServerName", "string");
  }

  else
    return;
}


//
// update_log_format_relations method
//
void Tomcat_Adapter::update_log_format_relations (CUTS_Log_Format * lfmt)
{

  // Get the name of the log format
  const ACE_CString & name = lfmt->name ();
  // Get the name of the log format
  // New causlilities will be created and added
  if (name == "LF1")
  {
      this->add_relation (lfmt, "LF2", "ServerName", "ServerName");
  }

  else if (name == "LF2")
  {
      this->add_relation (lfmt, "LF3", "ServerName", "ServerName");
  }

  else if (name == "LF3")
  {
      this->add_relation (lfmt, "LF4", "ServerName", "ServerName");
  }

  else if (name == "LF4")
  {
      this->add_relation (lfmt, "LF5", "ServerName", "ServerName");
  }

  else if (name == "LF5")
  {
      this->add_relation (lfmt, "LF6", "ServerName", "ServerName");
  }

  else if (name == "LF6")
  {
      this->add_relation (lfmt, "LF7", "ServerName", "ServerName");
  }

  else if (name == "LF7")
  {
      this->add_relation (lfmt, "LF8", "ServerName", "ServerName");
  }

  else if (name == "LF8")
  {
      this->add_relation (lfmt, "LF9", "ServerName", "ServerName");
  }

  else if (name == "LF9")
  {
      this->add_relation (lfmt, "LF10", "ServerName", "ServerName");
  }

  else if (name == "LF10")
  {
      this->add_relation (lfmt, "LF11", "ServerName", "ServerName");
  }

  else if (name == "LF11")
  {
      this->add_relation (lfmt, "LF12", "ServerName", "ServerName");
  }

  else
    return;
}


//
// update_log_format_variable_values method
//
bool Tomcat_Adapter::update_log_format_variable_values (
    ACE_CString &key, CUTS_Log_Format_Variable *var, CUTS_Log_Format * lfmt)
{

  // This flag tells whether this need to be update further from the traces
  bool update_further = false;
  const ACE_CString & name = lfmt->name ();
  // If the log format variable is updated from the adapter
  // set the flag to false otherwise it will be true
  if (name == "LF1")
  {
    if(key == "ServerName")
    {

        var->value("Tomcat");
    }


    else
    {
      update_further = true;
    }
  }

  else if (name == "LF2")
  {
    update_further = false;
    if(key == "ServerName")
    {

        var->value("Tomcat");
    }


    else
    {
      update_further = true;
    }
  }

  else if (name == "LF3")
  {
    update_further = false;
    if(key == "ServerName")
    {

        var->value("Tomcat");
    }


    else
    {
      update_further = true;
    }
  }

  else if (name == "LF4")
  {
    update_further = false;
    if(key == "ServerName")
    {

        var->value("Tomcat");
    }


    else
    {
      update_further = true;
    }
  }

  else if (name == "LF5")
  {
    update_further = false;
    if(key == "ServerName")
    {

        var->value("Tomcat");
    }


    else
    {
      update_further = true;
    }
  }

  else if (name == "LF6")
  {
    update_further = false;
    if(key == "ServerName")
    {

        var->value("Tomcat");
    }


    else
    {
      update_further = true;
    }
  }

  else if (name == "LF7")
  {
    update_further = false;
    if(key == "ServerName")
    {

        var->value("Tomcat");
    }


    else
    {
      update_further = true;
    }
  }

  else if (name == "LF8")
  {
    update_further = false;
    if(key == "ServerName")
    {

        var->value("Tomcat");
    }


    else
    {
      update_further = true;
    }
  }

  else if (name == "LF9")
  {
    update_further = false;
    if(key == "ServerName")
    {

        var->value("Tomcat");
    }


    else
    {
      update_further = true;
    }
  }

  else if (name == "LF10")
  {
    update_further = false;
    if(key == "ServerName")
    {

        var->value("Tomcat");
    }


    else
    {
      update_further = true;
    }
  }

  else if (name == "LF11")
  {
    update_further = false;
    if(key == "ServerName")
    {

        var->value("Tomcat");
    }


    else
    {
      update_further = true;
    }
  }

  else if (name == "LF12")
  {
    update_further = false;
    if(key == "ServerName")
    {

        var->value("Tomcat");
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
  ACE_NEW_RETURN (adapter, Tomcat_Adapter, 0);
  return adapter;
}

