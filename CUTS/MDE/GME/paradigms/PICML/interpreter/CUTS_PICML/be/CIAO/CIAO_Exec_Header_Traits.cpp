// $Id$

#include "CIAO_Exec_Header_Traits.h"
#include "CIAO_Traits.h"
#include "CIAO_Var_Type.h"
#include "CIAO_Retn_Type.h"
#include "CIAO_In_Type.h"
#include "CIAO_Preprocessor.h"
#include "../BE_Options.h"
#include "Uml.h"

#include <algorithm>
#include <sstream>

//
// env_table_
//
CUTS_CIAO_Exec_Header_Traits::Environment_Table
CUTS_CIAO_Exec_Header_Traits::env_table_;

//
// CUTS_CIAO_Exec_Header_Traits
//
CUTS_CIAO_Exec_Header_Traits::CUTS_CIAO_Exec_Header_Traits (void)
{
  if (this->env_table_.empty ())
  {
    this->env_table_.insert (
      Environment_Table::value_type ("activate",
      &CUTS_CIAO_Exec_Header_Traits::write_ccm_activate));

    this->env_table_.insert (
      Environment_Table::value_type ("passivate",
      &CUTS_CIAO_Exec_Header_Traits::write_ccm_passivate));

    this->env_table_.insert (
      Environment_Table::value_type ("remove",
      &CUTS_CIAO_Exec_Header_Traits::write_ccm_remove));
  }
}

//
// ~CUTS_CIAO_Exec_Header_Traits
//
CUTS_CIAO_Exec_Header_Traits::~CUTS_CIAO_Exec_Header_Traits (void)
{

}

//
// open_fle
//
bool CUTS_CIAO_Exec_Header_Traits::
open_file (const PICML::ComponentImplementationContainer & container)
{
  if (!CUTS_BE_CIAO_PREPROCESSOR->impls ().find (container.name (), this->node_))
    return false;

  if (this->node_->is_proxy_)
    return false;

  return this->_super::open_file (container);
}

//
// write_preamble
//
void CUTS_CIAO_Exec_Header_Traits::
write_prologue (const PICML::ComponentImplementationContainer & container)
{
  if (!this->out_.is_open ())
    return;

  // Generate the hash definition for this file.
  std::string hashdef =
    to_upper ((std::string)container.name () +
    CUTS_BE_OPTIONS ()->exec_suffix_);

  std::replace (hashdef.begin (),
                hashdef.end (),
                '/', '_');

  this->out_
    << "// -*- C++ -*-" << std::endl
    << std::endl
    << "#ifndef _" << hashdef << "_H_" << std::endl
    << "#define _" << hashdef << "_H_" << std::endl
    << std::endl
    << "#if !defined (ACE_LACKS_PRAGMA_ONCE)" << std::endl
    << "#pragma once" << std::endl
    << "#endif /* ACE_LACKS_PRAGMA_ONCE */" << std::endl
    << std::endl
    << "#include /**/ \"ace/pre.h\"" << std::endl
    << "#include \"" << container.name () << "EC.h\"" << std::endl
    << "#include \"cuts/CCM_Component_T.h\"" << std::endl;
}

//
// write_postamble
//
void CUTS_CIAO_Exec_Header_Traits::
write_epilogue (const PICML::ComponentImplementationContainer & container)
{
  if (!this->out_.is_open ())
    return;

  std::string hashdef =
    to_upper ((std::string)container.name () +
    CUTS_BE_OPTIONS ()->exec_suffix_);

  std::replace (hashdef.begin (),
                hashdef.end (),
                '/', '_');

  this->out_
    << "#include /**/ \"ace/post.h\"" << std::endl
    << std::endl
    << "#endif  // !defined _" << hashdef << "_H_" << std::endl;
}

//
// write_impl_begin
//
void CUTS_CIAO_Exec_Header_Traits::
write_impl_begin (const PICML::MonolithicImplementation & monoimpl,
                  const PICML::Component & component)
{
  if (!this->out_.is_open ())
    return;

  typedef std::vector <PICML::PeriodicEvent> PeriodicEvent_Set;
  PeriodicEvent_Set periodics = component.PeriodicEvent_kind_children ();

  if (!periodics.empty ())
  {
    this->out_ << include ("cuts/Trigger_T");
  }

  // We need to determine if any of the events sources has a
  // CUTS::Payload_Event type. This is necessary because we will
  // have to include a special header.
  //
  // @note Checking for a CUTS::Payload_Event should be done by
  //       the preprocessor.

  typedef std::vector <PICML::OutEventPort> OutEventPort_Set;
  OutEventPort_Set outevents = component.OutEventPort_kind_children ();

  for (OutEventPort_Set::iterator iter = outevents.begin ();
       iter != outevents.end ();
       iter ++)
  {
    PICML::Event event = iter->ref ();
    std::string eventtype =
      this->scope (event, "::") + (std::string) event.name ();

    if (eventtype == "CUTS::Payload_Event")
    {
      this->out_ << include ("cuts/events_i");
      break;
    }
  }

  // Write the class declaration for the component.
  _super::write_impl_begin (monoimpl, component);

  std::string name = component.name ();

  // Construct the name of the destructor.
  std::string destructor ("~");
  destructor += name;

  // Construct the name of the executor.
  std::string exec (name);
  exec.append ("_Exec");

  // Construct the name of the context.
  std::ostringstream context;
  context << scope (component, "::") << "CCM_"
          << component.name () << "_Context";

  std::ostringstream basetype;
  basetype << "CUTS_CCM_Component_T < "
           << exec << ", " << context.str () << " >";

  this->out_
    << "/**" << std::endl
    << " * @class " << name << std::endl
    << " *" << std::endl
    << " * Implementation of the " << exec << " component executor" << std::endl
    << " */" << std::endl
    << "class " << name << " :" << std::endl
    << "  public " << basetype.str () << " {"
    << "public:" << std::endl
    << single_line_comment ("Type definition for this component")
    << "typedef " << name << " type;"
    << std::endl
    << single_line_comment ("Type definition of the base component type")
    << "typedef " << basetype.str () << " base_type;"
    << std::endl

    // Write the default constructor.
    << single_line_comment ("Default constructor")
    << name << " (void);"
    << std::endl

    // Write the destructor.
    << single_line_comment ("Destructor")
    << "virtual ~" << name << " (void);"
    << std::endl;
}

//
// write_impl_end
//
void CUTS_CIAO_Exec_Header_Traits::
write_impl_end (const PICML::MonolithicImplementation & monoimpl,
                const PICML::Component & component)
{
  if (!this->out_.is_open ())
    return;

  std::vector <PICML::PeriodicEvent>
    periodics = component.PeriodicEvent_kind_children ();

  if (!periodics.empty ())
  {
    this->out_ << "private:" << std::endl
               << single_line_comment ("helper method to configure necessary objects")
               << "void cuts_configure_objects (void);";
  }

  this->out_ << "};";

  // Clear the list of asynchronous events.
  this->asynch_events_.clear ();
}

//
// write_variables_begin
//
void CUTS_CIAO_Exec_Header_Traits::
write_variables_begin (const PICML::Component & component)
{
  if (!this->out_.is_open ())
    return;

  this->_super::write_variables_begin (component);

  std::for_each (this->asynch_events_.begin (),
                 this->asynch_events_.end (),
                 boost::bind (&CUTS_CIAO_Exec_Header_Traits::write_event_handler_variable,
                              this,
                              _1));
}

//
// write_event_handler_variable
//
void CUTS_CIAO_Exec_Header_Traits::
write_event_handler_variable (
  const std::map <std::string, std::string>::value_type & val)
{
  this->out_ << single_line_comment (std::string ("event handler for ") + val.first)
             << "CUTS_CCM_Event_Handler_T < type, "
             << val.second << " > push_" << val.first << "_;";
}

//
// write_variable
//
void CUTS_CIAO_Exec_Header_Traits::
write_variable (const PICML::Variable & variable)
{
  if (!this->out_.is_open ())
    return;

  PICML::PredefinedType ptype = variable.ref ();

  if (ptype != Udm::null)
  {
    std::string name = variable.name ();

    this->out_
      << single_line_comment ("variable: " + name)
      << CIAO_VAR_TYPE (ptype) << " " << name << "_;"
      << std::endl;
  }
}

//
// write_variable
//
void CUTS_CIAO_Exec_Header_Traits::
write_ReadonlyAttribute_variable (const PICML::ReadonlyAttribute & readonly)
{
  if (!this->out_.is_open ())
    return;

  // Get the contained attribute member.
  PICML::AttributeMember member = readonly.AttributeMember_child ();

  if (member != Udm::null)
  {
    // Now, let's get the member type.
    PICML::MemberType mtype = member.ref ();

    if (mtype != Udm::null)
    {
      // We made it this far, so we can at least try to generate
      // the variable for this attribute.
      std::string name = readonly.name ();

      this->out_
        << single_line_comment ("variable: " + name)
        << CIAO_VAR_TYPE (mtype) << " " << name << "_;"
        << std::endl;
    }
  }
}

//
// write_PeriodicEvent_variable
//
void CUTS_CIAO_Exec_Header_Traits::
write_PeriodicEvent_variable (const PICML::PeriodicEvent & periodic)
{
  if (!this->out_.is_open ())
    return;

  PICML::Component parent = PICML::Component::Cast (periodic.parent ());

  this->out_
    << single_line_comment ("periodic: " + (std::string)periodic.name ())
    << "CUTS_Periodic_Trigger_T <" << parent.name ()
    << "> periodic_" << periodic.name () << "_;" << std::endl;
}


//
// write_worker_variable
//
void CUTS_CIAO_Exec_Header_Traits::
write_worker_variable (const PICML::WorkerType & var,
                const PICML::Worker & worker)
{
  if (!this->out_.is_open ())
    return;

  this->out_
    << single_line_comment ("worker variable: " + (std::string)var.name ())
    << worker.name () << " " << var.name () << "_;" << std::endl;
}

//
// write_environment_method_begin
//
void CUTS_CIAO_Exec_Header_Traits::
write_environment_method_begin (const PICML::MultiInputAction & action)
{
  if (!this->out_.is_open ())
    return;

  // Extract the necessary information.
  PICML::Component component = PICML::Component::Cast (action.parent ());
  std::string name = action.name ();

  // Locate the method inside the table.
  Environment_Table::const_iterator iter = this->env_table_.find (name);

  if (iter != this->env_table_.end ())
    (this->*(iter->second)) (component);
  else
    this->out_ << single_line_comment ("ignoring environment method: " + name);
}

//
// write_InEventPort_begin
//
void CUTS_CIAO_Exec_Header_Traits::
write_InEventPort_begin (const PICML::InEventPort & sink,
                         const std::vector <PICML::Property> & properties)
{
  this->_super::write_InEventPort_begin (sink);

  std::vector <PICML::Property>::const_iterator iter =
    std::find_if (properties.begin (),
                  properties.end (),
                  boost::bind (std::equal_to <std::string> (),
                               "asynchronous",
                               boost::bind (&PICML::Property::name, _1)));

  if (iter != properties.end ())
  {
    PICML::Event event = sink.ref ();
    std::ostringstream etype;
    etype << scope (event, "::") << event.name ();

    this->out_
      // End the current function declaration.
      << ";"
      << std::endl
      // Begin a new function declaration.
      << "void push_" << sink.name () << "_i ("
      << etype.str () << " * ev)";

    this->asynch_events_[sink.name ()] = etype.str ();
  }
}

//
// write_InEventPort_end
//
void CUTS_CIAO_Exec_Header_Traits::
write_InEventPort_end (const PICML::InEventPort & sink,
                       const std::vector <PICML::Property> & properties)
{
  this->_super::write_InEventPort_end (sink);
}
