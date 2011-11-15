// $Id$

#include "XML_Generators.h"

#if !defined (__CUTS_INLINE__)
#include "XML_Generators.inl"
#endif

#include "../BE_Options.h"
#include "../BE_Scope_Manager.h"
#include "../BE_Preprocessor_T.h"
#include "boost/bind.hpp"
#include "Uml.h"

// ACE headers
#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_File_Open_T

void CUTS_BE_File_Open_T <CUTS_BE_Xml>::
generate (const PICML::ComponentImplementationContainer & container,
          const PICML::MonolithicImplementation & impl)
{
  std::string filename (CUTS_BE_OPTIONS ()->output_directory_);
  filename += "/" + std::string (container.name ()) + ".xml";

  // Open the XML file for writing.
  this->ctx_.outfile_.open (filename.c_str ());

  if (this->ctx_.outfile_.is_open ())
    this->ctx_.formatter_.reset (new CUTS_BE_Xml::_formatter_type (this->ctx_.outfile_));
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_File_Close_T

void CUTS_BE_File_Close_T <CUTS_BE_Xml>::
generate (const PICML::ComponentImplementationContainer & container,
          const PICML::MonolithicImplementation & impl)
{
  this->ctx_.formatter_.reset ();

  if (this->ctx_.outfile_.is_open ())
    this->ctx_.outfile_.close ();
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Prologue_T

void CUTS_BE_Prologue_T <CUTS_BE_Xml>::
generate (const PICML::ComponentImplementationContainer & container,
          const PICML::MonolithicImplementation & impl)
{
  this->ctx_.outfile_
    << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
    << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Component_Impl_Begin_T

void CUTS_BE_Component_Impl_Begin_T <CUTS_BE_Xml>::
generate (const PICML::MonolithicImplementation & mono,
          const PICML::Component & component)
{
  this->ctx_.outfile_
    << "<cuts:behavior type=\"" << component.name () << "\">" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Component_Impl_End_T

void CUTS_BE_Component_Impl_End_T <CUTS_BE_Xml>::
generate (const PICML::MonolithicImplementation & mono,
          const PICML::Component & component)
{
  this->ctx_.outfile_
    << "</cuts:behavior>" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Variables_Begin_T

void CUTS_BE_Variables_Begin_T <CUTS_BE_Xml>::
generate (const PICML::Component & component)
{
  this->ctx_.outfile_ << "<variables>" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Variable_T

void CUTS_BE_Variable_T <CUTS_BE_Xml>::
generate (const PICML::Variable & variable)
{
  PICML::PredefinedType type = variable.ref ();

  if (type != Udm::null)
  {
    this->ctx_.outfile_
      << "<variable name=\"" << variable.name () << "\" "
      << "type=\"" << type.name () << "\" />" << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Worker_Variable_T

void CUTS_BE_Worker_Variable_T <CUTS_BE_Xml>::
generate (const PICML::WorkerType & type,
          const PICML::Worker & worker)
{
  this->ctx_.outfile_
    << "<worker name=\"" << type.name () << "\" type=\""
    << worker.name () << "\" />" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Variables_Begin_T

void CUTS_BE_Variables_End_T <CUTS_BE_Xml>::
generate (const PICML::Component & component)
{
  this->ctx_.outfile_ << "</variables>" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_WorkerAction_Begin_T

void CUTS_BE_WorkerAction_Begin_T <CUTS_BE_Xml>::
generate (const PICML::Worker & worker, const PICML::Action & action)
{
  PICML::Action action_type =
    const_cast <PICML::Action &> (action).Archetype ();

  this->ctx_.outfile_
    << "<action parent=\"" << action.name () << "\" name=\""
    << action_type.name () << "\">" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Action_Property_T

void CUTS_BE_Action_Property_T <CUTS_BE_Xml>::
generate (const PICML::Property & property)
{
  // Get the datatype for the property.
  PICML::DataType datatype = property.DataType_child ();

  if (datatype != Udm::null)
  {
    try
    {
      PICML::PredefinedType type =
        PICML::PredefinedType::Cast (datatype.ref ());

      this->ctx_.outfile_
        << "<property name=\"" << property.name () << "\" "
        << "type=\"" << type.name () << "\" value=\""
        << property.DataValue () << "\" />" << std::endl;
    }
    catch (...)
    {

    }
  }
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Action_End_T

void CUTS_BE_Action_End_T <CUTS_BE_Xml>::generate (void)
{
  this->ctx_.outfile_ << "</action>" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_InEventPort_Begin_T

void CUTS_BE_InEventPort_Begin_T <CUTS_BE_Xml>::
generate (const PICML::InEventPort & sink,
          const std::vector <PICML::Property> &)
{
  this->ctx_.outfile_
    << "<inevent name=\"" << sink.name () << "\" >" << std::endl;
};

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_InEventPort_End_T

void CUTS_BE_InEventPort_End_T <CUTS_BE_Xml>::
generate (const PICML::InEventPort & sink,
          const std::vector <PICML::Property> &)
{
  this->ctx_.outfile_ << "</inevent>" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Environment_Begin_T

void CUTS_BE_Environment_Begin_T <CUTS_BE_Xml>::
generate (const PICML::Component & component)
{
  this->ctx_.outfile_ << "<environments>" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Environment_Method_Begin_T

void CUTS_BE_Environment_Method_Begin_T <CUTS_BE_Xml>::
generate (const PICML::MultiInputAction & action)
{
  this->ctx_.outfile_
    << "<environment name=\"" << action.name () << "\">" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Environment_Method_End_T

void CUTS_BE_Environment_Method_End_T <CUTS_BE_Xml>::
generate (const PICML::MultiInputAction & action)
{
  this->ctx_.outfile_ << "</environment>" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Environment_End_T

void CUTS_BE_Environment_End_T <CUTS_BE_Xml>::
generate (const PICML::Component & component)
{
  this->ctx_.outfile_ << "</environments>" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_PeriodicEvent_Begin_T

void CUTS_BE_PeriodicEvent_Begin_T <CUTS_BE_Xml>::
generate (const PICML::PeriodicEvent & periodic)
{
  this->ctx_.outfile_
    << "<periodic hertz=\"" << periodic.Hertz ()
    << "\" distribution=\"" << periodic.Distribution () << "\">" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_PeriodicEvent_End_T

void CUTS_BE_PeriodicEvent_End_T <CUTS_BE_Xml>::
generate (const PICML::PeriodicEvent & periodic)
{
  this->ctx_.outfile_ << "</periodic>" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_OutputAction_Begin_T

void CUTS_BE_OutputAction_Begin_T <CUTS_BE_Xml>::
generate (const PICML::OutputAction & action)
{
  this->ctx_.outfile_
    << "<output name=\"" << action.name () << "\">" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_OutputAction_End_T

void CUTS_BE_OutputAction_End_T <CUTS_BE_Xml>::
generate (const PICML::OutputAction & action)
{
  this->ctx_.outfile_ << "</output>" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Action_Property_T

void CUTS_BE_OutputAction_Property_T <CUTS_BE_Xml>::
generate (const PICML::OutputAction & action,
          const PICML::Property & property)
{
  CUTS_BE_Action_Property_T <CUTS_BE_Xml> action_property (this->ctx_);
  action_property.generate (property);
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Branches_Begin_T

void CUTS_BE_Branches_Begin_T <CUTS_BE_Xml>::generate (size_t branches)
{
  this->ctx_.outfile_ << "<branches>" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Branch_Condition_Begin_T

void CUTS_BE_Branch_Condition_Begin_T <CUTS_BE_Xml>::generate (void)
{
  this->ctx_.outfile_ << "<branch>" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Branch_End_T
//
void CUTS_BE_Branch_End_T <CUTS_BE_Xml>::generate (void)
{
  this->ctx_.outfile_ << "</branch>" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Branches_End_T

void CUTS_BE_Branches_End_T <CUTS_BE_Xml>::generate (void)
{
  this->ctx_.outfile_ << "</branches>" << std::endl;
};

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Precondition_T

void CUTS_BE_Precondition_T <CUTS_BE_Xml>::
generate (const std::string & precondition)
{

  this->ctx_.outfile_
    << "<condition>" << precondition << "</condition>" << std::endl;
}
