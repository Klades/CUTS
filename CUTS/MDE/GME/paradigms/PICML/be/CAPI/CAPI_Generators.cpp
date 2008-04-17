// $Id$

#include "CAPI_Generators.h"
#include "be/BE_Options.h"
#include "be/BE_Scope_Manager.h"
#include "be/BE_Preprocessor.h"
#include "boost/bind.hpp"
#include "Uml.h"

// ACE headers
#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"

// code generation headers
#include "CCF/CodeGenerationKit/IndentationCxx.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"

#define CUTS_BE_CAPI() \
  ACE_Singleton <CUTS_BE_Capi, ACE_Null_Mutex>::instance ()

//
// CUTS_BE_Capi
//
CUTS_BE_Capi::CUTS_BE_Capi (void)
{

}

//
// CUTS_BE_File_Open_T
//
bool CUTS_BE_File_Open_T <CUTS_BE_Capi>::
generate (const PICML::ComponentImplementationContainer & container,
          const PICML::MonolithicImplementation & impl)
{
  // Locate the preprocessing of the implementation. If this is a
  // proxy implementation, then we ignore it. It's going to cause
  // more problems than we would like.
  const CUTS_BE_Impl_Node * node = 0;
  CUTS_BE_PREPROCESSOR ()->impls ().find (container.name (), node);

  if (node != 0 && node->is_proxy_)
    return false;

  std::string filename =
    CUTS_BE_OPTIONS ()->output_directory_ + "/"
    + (std::string) container.name () + ".java";

  if (!CUTS_BE_CAPI ()->outfile_.good ())
    CUTS_BE_CAPI ()->outfile_.clear ();

  // Open the XML file for writing.
  CUTS_BE_CAPI ()->outfile_.open (filename.c_str ());

  if (CUTS_BE_CAPI ()->outfile_.is_open ())
  {
    // Create a formatter for the XML file.
    CUTS_BE_CAPI ()->formatter_.reset (
      new CUTS_BE_Capi::_formatter_type (CUTS_BE_CAPI ()->outfile_));

    return true;
  }
  else
  {
    return false;
  }
}

//
// CUTS_BE_File_Close_T
//
bool CUTS_BE_File_Close_T <CUTS_BE_Capi>::
generate (const PICML::ComponentImplementationContainer & container,
          const PICML::MonolithicImplementation & impl)
{
  if (CUTS_BE_CAPI ()->outfile_.is_open ())
  {
    CUTS_BE_CAPI ()->formatter_.reset ();
    CUTS_BE_CAPI ()->outfile_.close ();
  }

  return true;
}

//
// CUTS_BE_Prologue_T
//
bool CUTS_BE_Prologue_T <CUTS_BE_Capi>::
generate (const PICML::ComponentImplementationContainer & container,
          const PICML::MonolithicImplementation & impl)
{
  CUTS_BE_CAPI ()->outfile_
    << "/**" << std::endl
    << " * @file        " << container.name () << ".java" << std::endl
    << " *" << std::endl
    << " * $Id$" << std::endl
    << " *" << std::endl
    << " * @author      James H. Hill (hillj@dre.vanderbilt.edu)" << std::endl
    << " *              CUTS Modeling Tools for CoSMIC" << std::endl
    << " *              http://www.dre.vanderbilt.edu/CUTS" << std::endl
    << " */" << std::endl
    << std::endl
    << "import cuts.java.PeriodicTask;"
    << "import cuts.java.jbi.client.JbiClient;"
    << std::endl;

  return true;
}

//
// CUTS_BE_Component_Impl_Begin_T
//
bool CUTS_BE_Component_Impl_Begin_T <CUTS_BE_Capi>::
generate (const PICML::MonolithicImplementation & mono,
          const PICML::Component & component)
{
  CUTS_BE_CAPI ()->outfile_
    << "/**" << std::endl
    << " * @class " << component.name () << std::endl
    << " */" << std::endl
    << "public class " << component.name () << " extends JbiClient"
    << "{"
    << "/**" << std::endl
    << " * Default constructor" << std::endl
    << " */" << std::endl
    << "public " << component.name () << " ()"
    << "{"
    << "}";

  return true;
}

//
// CUTS_BE_Component_Impl_End_T
//
bool CUTS_BE_Component_Impl_End_T <CUTS_BE_Capi>::
generate (const PICML::MonolithicImplementation & mono,
          const PICML::Component & component)
{
  CUTS_BE_CAPI ()->outfile_
    << "/**" << std::endl
    << " * Main entry point for the CAPI client" << std::endl
    << " */" << std::endl
    << "public static void main (String [] args) throws Exception {"
    << "// create the client object" << std::endl
    << "JbiClient client = new " << component.name () << " ();"
    << std::endl
    << std::endl
    << "// set its environment information" << std::endl
    << "client.setServerAddress (\"localhost\");"
    << "  client.setUserCredentials (\"testUser\", \"test\");"
    << std::endl
    << "  // run the client (eventually may run in seperate thread)" << std::endl
    << "  client.run ();"
    << "  }"
    << "}"
    << "// end of auto generated file" << std::endl;

  return true;
}

//
// CUTS_BE_Variables_Begin_T
//
bool CUTS_BE_Variables_Begin_T <CUTS_BE_Capi>::
generate (const PICML::Component & component)
{

  return true;
}

//
// CUTS_BE_Variable_T
//
bool CUTS_BE_Variable_T <CUTS_BE_Capi>::
generate (const PICML::Variable & variable)
{
  return true;
}

//
// CUTS_BE_Worker_Variable_T
//
bool CUTS_BE_Worker_Variable_T <CUTS_BE_Capi>::
generate (const PICML::WorkerType & type, const PICML::Worker & worker)
{
  return true;
}

//
// CUTS_BE_Variables_Begin_T
//
bool CUTS_BE_Variables_End_T <CUTS_BE_Capi>::
generate (const PICML::Component & component)
{
  return true;
}

//
// CUTS_BE_WorkerAction_Begin_T
//
bool CUTS_BE_WorkerAction_Begin_T <CUTS_BE_Capi>::
generate (const PICML::Worker & worker, const PICML::Action & action)
{
  return true;
}

//
// CUTS_BE_Action_Property_T
//
bool CUTS_BE_Action_Property_T <CUTS_BE_Capi>::
generate (const PICML::Property & property)
{
  return true;
}

//
// CUTS_BE_Action_End_T
//
bool CUTS_BE_Action_End_T <CUTS_BE_Capi>::generate (void)
{
  return true;
}

//
// CUTS_BE_InEventPort_Begin_T
//
bool CUTS_BE_InEventPort_Begin_T <CUTS_BE_Capi>::
generate (const PICML::InEventPort & sink)
{
  return true;
};

//
// CUTS_BE_InEventPort_End_T
//
bool CUTS_BE_InEventPort_End_T <CUTS_BE_Capi>::
generate (const PICML::InEventPort & sink)
{
  return true;
}

//
// CUTS_BE_Environment_Begin_T
//
bool CUTS_BE_Environment_Begin_T <CUTS_BE_Capi>::
generate (const PICML::Component & component)
{
  return true;
}

//
// CUTS_BE_Environment_Method_Begin_T
//
bool CUTS_BE_Environment_Method_Begin_T <CUTS_BE_Capi>::
generate (const PICML::InputAction & action)
{
  return true;
}

//
// CUTS_BE_Environment_Method_Begin_T
//
bool CUTS_BE_Environment_Method_End_T <CUTS_BE_Capi>::
generate (const PICML::InputAction & action)
{
  return true;
}

//
// CUTS_BE_Environment_End_T
//
bool CUTS_BE_Environment_End_T <CUTS_BE_Capi>::
generate (const PICML::Component & component)
{
  return true;
}

//
// CUTS_BE_PeriodicEvent_Begin_T
//
bool CUTS_BE_PeriodicEvent_Begin_T <CUTS_BE_Capi>::
generate (const PICML::PeriodicEvent & periodic)
{
  // Get the parent of the periodic event.
  PICML::Component parent = PICML::Component::Cast (periodic.parent ());
  PICML::Input input = periodic.dstInput ();

  if (input != Udm::null)
  {
    PICML::InputAction input_action = input.dstInput_end ();
    std::string periodic_name = input_action.name ();

    CUTS_BE_CAPI ()->outfile_
      << "public void " << periodic_name << " ()"
      << "{";
  }

  return true;
}

//
// CUTS_BE_PeriodicEvent_End_T
//
bool CUTS_BE_PeriodicEvent_End_T <CUTS_BE_Capi>::
generate (const PICML::PeriodicEvent & periodic)
{
  // Get the parent of the periodic event.
  PICML::Component parent = PICML::Component::Cast (periodic.parent ());
  std::string parent_name = parent.name ();

  PICML::Input input = periodic.dstInput ();
 
  if (input != Udm::null)
  {
    PICML::InputAction input_action = input.dstInput_end ();
    std::string periodic_name = input_action.name ();

    CUTS_BE_CAPI ()->outfile_
      << "}"
      << "/**"
      << " * @class " << periodic_name << std::endl
      << " * Defines the handler for the periodicSend PeriodicEvent element" << std::endl
      << " * specified in the component's behavior model." << std::endl
      << " */" << std::endl
      << "private class " << periodic_name << "PeriodicTask extends PeriodicTask" 
      << "{"
      << "/// The owner of the task" << std::endl
      << "private " << parent_name << " component_ = null;" << std::endl
      << std::endl
      << "public " << periodic_name << "PeriodicTask (" 
      << parent_name << " component)"
      << "{"
      << "super (" << periodic.Period () << ");" << std::endl
      << "this.component_ = component;"
      << "}"
      << "public void handleTimeout () {"
      << "this.component_." << periodic_name << "();"
      << "}"
      << "}";
  }
  return true;
}

//
// CUTS_BE_OutputAction_Begin_T
//
bool CUTS_BE_OutputAction_Begin_T <CUTS_BE_Capi>::
generate (const PICML::OutputAction & action)
{
  return true;
}

//
// CUTS_BE_OutputAction_End_T
//
bool CUTS_BE_OutputAction_End_T <CUTS_BE_Capi>::
generate (const PICML::OutputAction & action)
{
  return true;
}

//
// CUTS_BE_Action_Property_T
//
bool CUTS_BE_OutputAction_Property_T <CUTS_BE_Capi>::
generate (const PICML::OutputAction & action,
          const PICML::Property & property)
{
  return CUTS_BE_Action_Property_T <CUTS_BE_Capi>::generate (property);
}

//
// CUTS_BE_Branches_Begin_T
//
bool CUTS_BE_Branches_Begin_T <CUTS_BE_Capi>::generate (size_t branches)
{
  return true;
}

//
// CUTS_BE_Branch_Condition_Begin_T
//
bool CUTS_BE_Branch_Condition_Begin_T <CUTS_BE_Capi>::generate (void)
{
  return true;
}

//
// CUTS_BE_Branch_End_T
//
bool CUTS_BE_Branch_End_T <CUTS_BE_Capi>::generate (void)
{
  return true;
}

//
// CUTS_BE_Branches_End_T
//
bool CUTS_BE_Branches_End_T <CUTS_BE_Capi>::generate (void)
{
  return true;
};

//
// CUTS_BE_Precondition_T
//
bool CUTS_BE_Precondition_T <CUTS_BE_Capi>::
generate (const std::string & precondition)
{
  return true;
}
