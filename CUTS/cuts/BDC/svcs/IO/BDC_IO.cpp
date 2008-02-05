// $Id$

#include "BDC_IO.h"
#include "IO_System_Metric_Visitor.h"
#include "cuts/Component_Info.h"
#include "cuts/Host_Table.h"
#include "cuts/Host_Table_Entry.h"
#include "cuts/System_Metric.h"
#include "cuts/Testing_Service.h"
#include "cuts/BDC/BDC_Service_Manager.h"
#include <iostream>
#include <sstream>

// Define the implementation.
CUTS_BDC_SERVICE_IMPL (CUTS_BDC_IO_Service);

//
// state_str_
//
const char * CUTS_BDC_IO_Service::
state_cstr_[2] = {"activate", "passivate"};

//
// CUTS_BDC_IO_Service
//
CUTS_BDC_IO_Service::CUTS_BDC_IO_Service (void)
{

}

//
// ~CUTS_BDC_IO_Service
//
CUTS_BDC_IO_Service::~CUTS_BDC_IO_Service (void)
{

}

//
// handle_metrics
//
int CUTS_BDC_IO_Service::
handle_metrics (const CUTS_System_Metric & metrics)
{
  // Get the current metrics and testing service.
  CUTS_Testing_Service * tsvc = this->svc_mgr ()->testing_service ();

  CUTS_IO_System_Metric_Visitor visitor (tsvc);
  metrics.accept (visitor);
  return 0;
}

//
// handle_component
//
int CUTS_BDC_IO_Service::
handle_component (const CUTS_Component_Info & info)
{
  std::ostringstream ostr;

  ostr
    << "************************************************" << std::endl
    << "*** Component Registration" << std::endl
    << "************************************************" << std::endl
    << "instance : " << info.inst_.c_str () << std::endl
    << "location : " << info.host_info_->hostname_.c_str ()
    << " (" << info.host_info_->ipaddr_.c_str () << ")" << std::endl
    << "state    : "
    << CUTS_BDC_IO_Service::state_cstr_[info.state_] << std::endl
    << std::endl
    << "    type : " << info.type_->name_.c_str () << std::endl;

  this->print_port_description (ostr, "   sinks", info.type_->sinks_);
  this->print_port_description (ostr, " sources", info.type_->sources_);
  ostr << std::endl << std::ends;

  // Write the string to the window.
  ACE_DEBUG ((LM_INFO, "%s", ostr.str ().c_str ()));
  return 0;
}

//
// write_port_description
//
void CUTS_BDC_IO_Service::
print_port_description (std::ostringstream & ostr,
                        const ACE_CString & title,
                        const CUTS_Port_Description_Map & desc)
{
  // Print the header for the port descriptions.
  ostr << title.c_str () << std::string (" : ");

  if (desc.current_size () != 0)
  {
    CUTS_Port_Description_Map::CONST_ITERATOR iter (desc);

    for (iter; !iter.done (); iter ++)
      ostr << iter->item ().c_str () << " ";
  }
  else
    ostr << std::string ("<none>");

  // Start output on the next line.
  ostr << std::endl;
}
