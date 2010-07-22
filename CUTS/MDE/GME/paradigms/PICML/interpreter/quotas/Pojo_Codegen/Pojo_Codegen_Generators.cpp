// $Id$

#include "stdafx.h"
#include "Pojo_Codegen_Generators.h"

#if !defined (__CUTS_INLINE__)
#include "Pojo_Codegen_Generators.inl"
#endif

#include "Pojo_Codegen_Preprocessor.h"
#include "be/lang/java/Java_Variable_Type.h"
#include "be/BE_Options.h"
#include "be/BE_Scope_Manager.h"

#include "boost/bind.hpp"
#include "Uml.h"

#include <iomanip>

//
// CUTS_BE_File_Open_T
//
void CUTS_BE_File_Open_T <Quotas::Pojo::Codegen::Context>::
generate (const PICML::ComponentImplementationContainer & container,
          const PICML::MonolithicImplementation & impl)
{
  // Locate the preprocessing of the implementation. If this is a
  // proxy implementation, then we ignore it. It's going to cause
  // more problems than we would like.
  const std::string impl_name (impl.name ());
  QUOTAS_POJO_CODEGEN_PREPROCESSOR->impls ().find (impl_name, this->ctx_.impl_node_);

  if (0 == this->ctx_.impl_node_)
    return;

  std::string filename (CUTS_BE_OPTIONS ()->output_directory_);
  filename += "/" + std::string (impl.name ()) + ".java";

  if (!this->ctx_.source_.good ())
    this->ctx_.source_.clear ();

  // Open the XML file for writing.
  this->ctx_.source_.open (filename.c_str ());

  if (!this->ctx_.source_.is_open ())
    return;

  // Create a formatter for the XML file.
  this->ctx_.source_formatter_.reset (new Quotas::Pojo::Codegen::Context::formatter_type (this->ctx_.source_));
}

//
// CUTS_BE_File_Close_T
//
void CUTS_BE_File_Close_T <Quotas::Pojo::Codegen::Context>::
generate (const PICML::ComponentImplementationContainer & container,
          const PICML::MonolithicImplementation & impl)
{
  this->ctx_.source_formatter_.reset ();
  this->ctx_.source_.close ();
}

//
// CUTS_BE_Prologue_T
//
void CUTS_BE_Prologue_T <Quotas::Pojo::Codegen::Context>::
generate (const PICML::ComponentImplementationContainer & container,
          const PICML::MonolithicImplementation & impl)
{
  this->ctx_.source_
    << "// -*- Java -*-" << std::endl
    << std::endl
    << left << setw (78) << setfill ('=') << "//" << std::endl
    << "/**" << std::endl
    << " * @file        " << impl.name () << ".java" << std::endl
    << " *" << std::endl
    << " * $" << "Id" << "$" << std::endl
    << " *" << std::endl
    << " * @author      James H. Hill (hillj at cs dot iupui dot edu)" << std::endl
    << " *              CUTS Modeling Tools for CoSMIC" << std::endl
    << " *              http://www.cs.iupui.edu/cuts" << std::endl
    << " */" << std::endl
    << left << setw (78) << setfill ('=') << "//" << std::endl
    << std::endl;
}

/**
 * @struct init_periodic_task_t
 *
 * Functor that generates the code for initializing a PeriodicTask
 * element.
 */
struct init_periodic_task_t
{
  init_periodic_task_t (std::ostream & out)
    : out_ (out)
  {

  }

  void operator () (const PICML::PeriodicEvent & p) const
  {
    this->out_
      << "this." << p.name ()
      << "_.setPeriodicTaskStrategy (new cuts."
      << p.Distribution ()
      << "PeriodicTaskStrategy ());";
  }

private:
  /// Target output stream.
  std::ostream & out_;
};

/**
 * @struct generate_import_t
 *
 * Functor that generates a import statement.
 */
struct generate_import_t
{
  generate_import_t (std::ostream & out)
    : out_ (out)
  {

  }

  void operator () (const std::string & import) const
  {
    this->out_ << "import" << import << ";";
  }

private:
  /// Target output stream.
  std::ostream & out_;
};

//
// CUTS_BE_Component_Impl_Begin_T
//
void CUTS_BE_Component_Impl_Begin_T <Quotas::Pojo::Codegen::Context>::
generate (const PICML::MonolithicImplementation & mono, const PICML::Component & component)
{
  std::vector <PICML::PeriodicEvent> periodics = component.PeriodicEvent_kind_children ();

  // Generate the import file for periodic events.
  if (!periodics.empty ())
    this->ctx_.source_
      << "// imports for using PeriodicEvent element(s)" << std::endl
      << "import java.util.TimerTask;"
      << "import cuts.PeriodicTask;";

  // Generate the remaining imports for this implementation.
  const CUTS_String_Set & imports = this->ctx_.impl_node_->maplist_["imports"];
  std::for_each (imports.begin (),
                 imports.end (),
                 generate_import_t (this->ctx_.source_));

  // The name of the class is the name of the monolithic implementation.
  // This is also the name of the file, which is a requirement of Java!!
  std::string class_name = mono.name ();
  this->ctx_.impl_classname_ = class_name;

  this->ctx_.source_
    << std::endl
    << "/**" << std::endl
    << " *  @class " << class_name << std::endl
    << " */" << std::endl
    << "public class " << class_name << std::endl
    << "  extends cuts.quotas.pojo.ComponentBase {"
    << "/**" << std::endl
    << " * Default constructor" << std::endl
    << " */" << std::endl
    << "public " << class_name << " ()"
    << "{";

  // Initialize the periodic tasks for the component.
  std::for_each (periodics.begin (),
                 periodics.end (),
                 init_periodic_task_t (this->ctx_.source_));

  this->ctx_.source_
    << "}";
}

//
// generate_worker_import
//
void CUTS_BE_Component_Impl_Begin_T <Quotas::Pojo::Codegen::Context>::
generate_worker_import (const PICML::Worker & worker)
{
  // Get the parent of the worker.
  std::stack <std::string> scope;
  PICML::MgaObject parent (worker.parent ());

  while (parent.type () == PICML::WorkerPackage::meta)
  {
    // Save the name of the package and its parent.
    scope.push (parent.name ());
    parent = PICML::MgaObject::Cast (parent.parent ());
  }

  // Generate the import path for the worker.
  std::ostringstream import_path;

  while (!scope.empty ())
  {
    import_path << scope.top () << ".";
    scope.pop ();
  }

  // Append the worker's name to the import path.
  import_path << worker.name ();

  // Write the import statement to the file.
  this->ctx_.source_ << "import " << import_path.str ().c_str () << ";";
}

//
// CUTS_BE_Component_Impl_End_T
//
void CUTS_BE_Component_Impl_End_T <Quotas::Pojo::Codegen::Context>::
generate (const PICML::MonolithicImplementation & mono, const PICML::Component & component)
{
  // End of the component implementation.
  this->ctx_.source_
    << "}"
    << std::endl
    << "// end of auto generated file" << std::endl;

  // Reset the context for the next implementation.
  this->ctx_.reset ();
}

//
// CUTS_BE_Environment_Method_Begin_T
//
void CUTS_BE_Environment_Method_Begin_T <Quotas::Pojo::Codegen::Context>::
generate (const PICML::MultiInputAction & action)
{
  std::string name = action.name ();

  Quotas::Pojo::Codegen::Context::Env_Seen_Map::iterator iter =
    this->ctx_.env_seen_.find (name);

  if (iter == this->ctx_.env_seen_.end ())
    return;

  if (iter->second)
    return;

  iter->second = true;

  this->ctx_.source_
    << std::endl
    << "/**" << std::endl
    << " * environmentAction : " << name << std::endl
    << " */" << std::endl
    << "protected void " << name << " ()"
    << "{"
    << "try"
    << "{";

  this->ctx_.generate_required_method_impl (name);
}

//
// CUTS_BE_Environment_Method_Begin_T
//
void CUTS_BE_Environment_Method_End_T <Quotas::Pojo::Codegen::Context>::
generate (const PICML::MultiInputAction & action)
{
  this->ctx_.source_
    << "}"
    << "catch (Exception e)"
    << "{"
    << "e.printStackTrace ();"
    << "}"
    << "}";
}

//
// CUTS_BE_Environment_End_T
//
void CUTS_BE_Environment_End_T <Quotas::Pojo::Codegen::Context>::
generate (const PICML::Component & component)
{
  Quotas::Pojo::Codegen::Context::Env_Seen_Map::const_iterator
    iter = this->ctx_.env_seen_.begin (),
    iter_end = this->ctx_.env_seen_.end ();

  for (; iter != iter_end; ++ iter)
  {
    if (!iter->second)
    {
      this->ctx_.source_
        << std::endl
        << "/**" << std::endl
        << " * environmentAction : " << iter->first << std::endl
        << " */" << std::endl
        << "protected void " << iter->first << " ()";
      this->ctx_.generate_throws_signature (iter->first);
      this->ctx_.source_
        << "{"
        << "try"
        << "{";

      this->ctx_.generate_required_method_impl (iter->first);

      this->ctx_.source_
        << "}"
        << "catch (Exception e)"
        << "{"
        << "e.printStackTrace ();"
        << "}"
        << "}";
    }
  }
}

//
// CUTS_BE_PeriodicEvent_Begin_T
//
void CUTS_BE_PeriodicEvent_Begin_T <Quotas::Pojo::Codegen::Context>::
generate (const PICML::PeriodicEvent & periodic)
{
  // Get the parent of the periodic ev.
  PICML::Component parent = PICML::Component::Cast (periodic.parent ());
  PICML::Input input = periodic.dstInput ();

  if (input != Udm::null)
  {
    PICML::InputAction input_action = input.dstInput_end ();
    std::string periodic_name = periodic.name ();

    this->ctx_.source_
      << std::endl
      << "/**" << std::endl
      << " * periodicEventHandler : " << periodic_name << std::endl
      << " *" << std::endl
      << " * Implementation for the specified periodic ev." << std::endl
      << " */" << std::endl
      << "public void " << periodic_name << " ()"
      << "{"
      << "try"
      << "{";

    // Save the periodic ev's name.
    this->ctx_.periodics_.insert (std::make_pair (periodic_name, periodic));
  }
}

//
// CUTS_BE_PeriodicEvent_End_T
//
void CUTS_BE_PeriodicEvent_End_T <Quotas::Pojo::Codegen::Context>::
generate (const PICML::PeriodicEvent & periodic)
{
  // Get the parent of the periodic ev.
  std::string parent_name = this->ctx_.impl_classname_;
  PICML::Input input = periodic.dstInput ();

  if (input != Udm::null)
  {
    PICML::InputAction input_action = input.dstInput_end ();

    std::string periodic_name = periodic.name ();
    std::string periodic_task = CUTS_BE_Java::classname (periodic_name + "PeriodicTask");

    this->ctx_.source_
      << "}"
      << "catch (Exception e)"
      << "{"
      << "e.printStackTrace ();"
      << "}"
      << "}"
      << std::endl
      << "/**" << std::endl
      << " * @class " << periodic_task << std::endl
      << " *" << std::endl
      << " * Defines the handler/task for the " << periodic_name << " PeriodicEvent element" << std::endl
      << " * specified in the component behavior model." << std::endl
      << " */" << std::endl
      << "private class " << periodic_task << std::endl
      << "  extends cuts.PeriodicTaskHandler < " << parent_name << " > {"
      << "public " << periodic_task << " (cuts.PeriodicTask < " << parent_name << " > task)"
      << "{"
      << "super (task);"
      << "}"
      << std::endl
      << "public void handleTimeout ()"
      << "{"
      << "this.task_.getOwner ()." << periodic_name << " ();"
      << "}"
      << "}"
      << std::endl
      << "private class " << periodic_task << "Factory" << std::endl
      << "  implements cuts.PeriodicTaskHandlerFactory < " << parent_name << " > {"
      << "public " << periodic_task << "Factory () { }"
      << "public TimerTask createTimerTask (cuts.PeriodicTask < " << parent_name << " > task)"
      << "{"
      << "return new " << periodic_task << " (task);"
      << "}"
      << "}"
      << std::endl
      << "/**" << std::endl
      << " * PeriodicTask : " << periodic_name << std::endl
      << " */" << std::endl
      << "private cuts.PeriodicTask <" << parent_name << "> "
      << periodic_name << "_ = " << std::endl
      << "  new cuts.PeriodicTask <" << parent_name << " > (this, new " << periodic_task << "Factory ());";
  }
}

//
// CUTS_BE_ReadonlyAttribute_Begin_T
//
void CUTS_BE_ReadonlyAttribute_Begin_T <Quotas::Pojo::Codegen::Context>::
generate (const PICML::ReadonlyAttribute & readonly)
{
  std::string name = readonly.name ();
  PICML::AttributeMember member = readonly.AttributeMember_child ();
  PICML::MemberType type = member.ref ();

  this->ctx_.source_
    << std::endl
    << "/**" << std::endl
    << " * attribute getter : " << name << std::endl
    << " */" << std::endl
    << "public ";

  CUTS_BE_Java::Variable_Type vtype (this->ctx_.source_);
  vtype.generate (type);

  this->ctx_.source_
    << " "
    << CUTS_BE_Java::getter_method (name) << " ()"
    << "{";
}

//
// CUTS_BE_ReadonlyAttribute_End_T
//
void CUTS_BE_ReadonlyAttribute_End_T <Quotas::Pojo::Codegen::Context>::
generate (const PICML::ReadonlyAttribute & readonly)
{
  this->ctx_.source_
    << "return this." << readonly.name () << "_;"
    << "}";
}

//
// CUTS_BE_Attribute_Begin_T
//
void CUTS_BE_Attribute_Begin_T <Quotas::Pojo::Codegen::Context>::
generate (const PICML::Attribute & attr)
{
  std::string name = attr.name ();
  PICML::AttributeMember member = attr.AttributeMember_child ();
  PICML::MemberType type = member.ref ();

  this->ctx_.source_
    << std::endl
    << "/**" << std::endl
    << " * attribute setter : " << name << std::endl
    << " */" << std::endl
    << "public void "
    << CUTS_BE_Java::setter_method (name)
    << " (";

  CUTS_BE_Java::Variable_Type vtype (this->ctx_.source_);
  vtype.generate (type);

  this->ctx_.source_
    << " " << name << ")"
    << "{";
}

//
// CUTS_BE_Attribute_End_T
//
void CUTS_BE_Attribute_End_T <Quotas::Pojo::Codegen::Context>::
generate (const PICML::Attribute & attr)
{
  std::string name = attr.name ();

  this->ctx_.source_
    << "this." << name << "_ = " << name << ";"
    << "}";

  CUTS_BE_ReadonlyAttribute_Begin_T <Quotas::Pojo::Codegen::Context> readonly_begin (this->ctx_);
  readonly_begin.generate (attr);

  CUTS_BE_ReadonlyAttribute_End_T <Quotas::Pojo::Codegen::Context> readonly_end (this->ctx_);
  readonly_end.generate (attr);
}

//
// CUTS_BE_Finalize_T
//
void CUTS_BE_Finalize_T <Quotas::Pojo::Codegen::Context>::
generate (const PICML::RootFolder & root)
{

}

//
// CUTS_BE_Postcondition_T
//
void CUTS_BE_Postcondition_T <Quotas::Pojo::Codegen::Context>::
generate (const std::string & postcondition)
{
  this->ctx_.source_ << postcondition;
}

