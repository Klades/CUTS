// $Id$

#include "CAPI_Generators.h"
#include "CAPI_Preprocessor.h"
#include "Set_Classpath_Script_Generator.h"
#include "Register_Type_Script_Generator.h"
#include "XML_Mapping_File_Generator.h"
#include "CAPI_Event_Impl_Generator.h"
#include "XSD_File_Generator.h"
#include "../BE_Options.h"
#include "../BE_Scope_Manager.h"
#include "boost/bind.hpp"
#include "Uml.h"

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
  CUTS_BE_PREPROCESSOR (CUTS_BE_Capi)->impls ().
    find (container.name (), CUTS_BE_CAPI ()->impl_node_);

  if (CUTS_BE_CAPI ()->impl_node_ == 0 ||
      CUTS_BE_CAPI ()->impl_node_->is_proxy_)
  {
    return false;
  }

  std::string filename =
    CUTS_BE_OPTIONS ()->output_directory_ + "/"
    + std::string (impl.name ()) + ".java";

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
    << " * @file        " << impl.name () << ".java" << std::endl
    << " *" << std::endl
    << " * $Id$" << std::endl
    << " *" << std::endl
    << " * @author      James H. Hill (hillj@dre.vanderbilt.edu)" << std::endl
    << " *              CUTS Modeling Tools for CoSMIC" << std::endl
    << " *              http://www.dre.vanderbilt.edu/CUTS" << std::endl
    << " */" << std::endl
    << std::endl
    << "import org.infospherics.jbi.client.Connection;"
    << "import org.infospherics.jbi.client.exception.*;"
    << "import CUTS.jbi.client.JbiClient;";

  return true;
}

//
// CUTS_BE_Component_Impl_Begin_T
//
bool CUTS_BE_Component_Impl_Begin_T <CUTS_BE_Capi>::
generate (const PICML::MonolithicImplementation & mono,
          const PICML::Component & component)
{
  typedef std::vector <PICML::InEventPort> InEventPort_Set;
  InEventPort_Set inputs = component.InEventPort_kind_children ();

  typedef std::vector <PICML::OutEventPort> OutEventPort_Set;
  OutEventPort_Set outputs = component.OutEventPort_kind_children ();

  if (!inputs.empty () || !outputs.empty ())
  {
    CUTS_BE_CAPI ()->outfile_
      << std::endl
      << "// imports for handling events" << std::endl
      << "import CUTS.jbi.client.JbiEvent;"
      << "import org.exolab.castor.xml.MarshalException;"
      << "import org.exolab.castor.xml.ValidationException;"
      << "import org.exolab.castor.mapping.MappingException;"
      << "import java.io.IOException;";

    std::set <std::string> event_types;

    if (!inputs.empty ())
    {
      // Generate the import files for receiving MIOs.
      CUTS_BE_CAPI ()->outfile_
        << std::endl
        << "// imports for receiving MIOs" << std::endl
        << "import org.infospherics.jbi.client.ObjectAvailableCallback;"
        << "import org.infospherics.jbi.client.InfoObject;"
        << "import CUTS.jbi.client.JbiSink;";

      // Store the event types for later usage. We also need to
      // generate the import files for the event objects.
      PICML::Event event;
      std::string version, type_name;

      InEventPort_Set::const_iterator
        iter = inputs.begin (), iter_end = inputs.end ();

      for ( ; iter != iter_end; ++ iter)
      {
        // Get the typename of the event.
        event = iter->ref ();
        version = event.VersionTag ();
        type_name = CUTS_BE_Capi::fq_name (event, '.');

        // Save the event to the globally.
        CUTS_BE_CAPI ()->workspace_events_.insert (event);

        // Store it in the event types for later on.
        event_types.insert (type_name);

        // Store the name of the event since we need to tell the ANT file to
        // generate the Java bindings for its schema definition.
        CUTS_BE_CAPI ()->impl_node_->maplist_["events"].insert (type_name);
        CUTS_BE_CAPI ()->sinks_.insert (std::make_pair (iter->name (), event));
      }
    }

    if (!outputs.empty ())
    {
      CUTS_BE_CAPI ()->outfile_
        << std::endl
        << "// imports for sending MIOs" << std::endl
        << "import CUTS.jbi.client.JbiSource;";

      // Store the event types for later usage. We also need to
      // generate the import files for the event objects.
      PICML::Event event;
      std::string type_name, version;

      OutEventPort_Set::const_iterator
        iter = outputs.begin (), iter_end = outputs.end ();

      for ( ; iter != iter_end; ++ iter)
      {
        // Get the typename of the event.
        event = iter->ref ();
        version = event.VersionTag ();
        type_name = CUTS_BE_Capi::fq_name (event, '.');

        // Save the event to the globally.
        CUTS_BE_CAPI ()->workspace_events_.insert (event);

        // Store it in the event types for later on.
        event_types.insert (type_name);

        // Store the name of the event since we need to tell the ANT file to
        // generate the Java bindings for its schema definition.
        CUTS_BE_CAPI ()->impl_node_->maplist_["events"].insert (type_name);

        // Save the event's information in the sources collection.
        if (version.empty ())
          version = "1.0";

        CUTS_BE_CAPI ()->sources_.insert (std::make_pair (iter->name (), event));
      }
    }

    if (!event_types.empty ())
    {
      CUTS_BE_CAPI ()->outfile_
        << std::endl
        << "// imports for used event types" << std::endl;

      // Generate the import files for the event types.
      std::set <std::string>::const_iterator
        iter = event_types.begin (), iter_end = event_types.end ();

      for (; iter != iter_end; ++ iter)
      {
        CUTS_BE_CAPI ()->outfile_
          << "import " << *iter << ".*;";
      }
    }
  }

  typedef std::vector <PICML::PeriodicEvent> PeriodicEvent_Set;
  PeriodicEvent_Set periodics = component.PeriodicEvent_kind_children ();

  if (!periodics.empty ())
  {
    // Generate the import file for periodic events.
    CUTS_BE_CAPI ()->outfile_
      << std::endl
      << "// imports for periodic events" << std::endl
      << "import CUTS.PeriodicTask;";
  }


  // Generate the remaining imports for this implementation.
  const CUTS_String_Set & imports =
    CUTS_BE_CAPI ()->impl_node_->maplist_["imports"];

  CUTS_String_Set::const_iterator
    imports_iter = imports.begin (), imports_iter_end = imports.end ();

  for (; imports_iter != imports_iter_end; ++ imports_iter)
  {
    CUTS_BE_CAPI ()->outfile_
      << "import " << *imports_iter << ";";
  }

  // The name of the class is the name of the monolithic implementation.
  // This is also the name of the file, which is a requirement of Java!!
  std::string class_name = mono.name ();
  CUTS_BE_CAPI ()->impl_classname_ = class_name;

  CUTS_BE_CAPI ()->outfile_
    << std::endl
    << "/**" << std::endl
    << " * @class " << class_name << std::endl
    << " *" << std::endl
    << " * Monolithic implementation of the <" << component.name ()
    << "> component type." << std::endl
    << " */" << std::endl
    << "public class " << class_name << " extends JbiClient";

  // Should we define an interface that this class implements, which
  // would be based on the component type?? This seems like it would
  // be an overkill.

  if (!inputs.empty ())
  {
    CUTS_BE_CAPI ()->outfile_
      << std::endl
      << "  implements ObjectAvailableCallback" << std::endl;
  }

  CUTS_BE_CAPI ()->outfile_
    << "{"
    << "/**" << std::endl
    << " * Default constructor" << std::endl
    << " */" << std::endl
    << "public " << class_name << " ()"
    << "{"
    << "}";

  return true;
}

//
// generate_worker_import
//
void CUTS_BE_Component_Impl_Begin_T <CUTS_BE_Capi>::
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
  CUTS_BE_CAPI ()->outfile_
    << "import " << import_path.str ().c_str () << ";";
}

//
// CUTS_BE_Component_Impl_End_T
//
bool CUTS_BE_Component_Impl_End_T <CUTS_BE_Capi>::
generate (const PICML::MonolithicImplementation & mono,
          const PICML::Component & component)
{
  CUTS_BE_Capi::Event_Port_Map::const_iterator
    iter = CUTS_BE_CAPI ()->sources_.begin (),
    iter_end = CUTS_BE_CAPI ()->sources_.end ();

  std::string source_classname, source_variable;
  std::string type_name, version, fq_name;

  for ( ; iter != iter_end; iter ++)
  {
    source_classname = iter->first + "Source";
    source_variable = iter->first + "_";

    type_name = CUTS_BE_CAPI ()->fq_name (iter->second, '.');
    version = iter->second.VersionTag ();

    if (version.empty ())
    {
      version = "1.0";
      iter->second.VersionTag () = version;
    }

    CUTS_BE_CAPI ()->outfile_
      << std::endl
      << "/**" << std::endl
      << " * publisherName    : " << iter->first << std::endl
      << " * publisherType    : " << type_name << std::endl
      << " * publisherVersion : " << version << std::endl
      << " */" << std::endl
      << "private class " << source_classname << " extends JbiSource"
      << "{"
      << "public " << source_classname << " ("
      << CUTS_BE_CAPI ()->impl_classname_ << " parent)" << std::endl
      << "  throws PermissionDeniedException, UnsupportedVersionException," << std::endl
      << "         MappingException, IOException" << std::endl
      << "{"
      << "super (parent.getJbiConnection (), \""
      << type_name << "\", \"" << version << "\");"
      << "}"
      << "}"
      << std::endl
      << "/**" << std::endl
      << " * publisherVariable : " << iter->first << std::endl
      << " */" << std::endl
      << "private " << source_classname << " "
      << source_variable << " = null;"
      << std::endl;
  }

  if (!CUTS_BE_CAPI ()->sinks_.empty ())
  {
    // Generate the entry point for the client application.
    CUTS_BE_CAPI ()->outfile_
      << std::endl
      << "/**" << std::endl
      << " * Dispatcher for received MIOs" << std::endl
      << " *" << std::endl
      << " * @param[in]     result      Collection of info objects" << std::endl
      << " */" << std::endl
      << "public void objectsAvailable (InfoObject [] result)"
      << "{"
      << "try"
      << "{"
      << "// Create a new JbiEvent object for the MIOs. Once the XML " << std::endl
      << "// binding for Java is supported, this will be replaced with" << std::endl
      << "// the Java-based object for the each MIO type." << std::endl
      << "String type, version, metadata;"
      << std::endl
      << "for (InfoObject mio : result) "
      << "{"
      << "// Store the information object in the JbiEvent." << std::endl
      << "type = mio.getTypeName ();"
      << "version = mio.getVersion ();"
      << std::endl
      << "// Locate the correct dispatch method." << std::endl;

    CUTS_BE_Capi::Event_Port_Map::const_iterator
      sink_iter = CUTS_BE_CAPI ()->sinks_.begin (),
      sink_iter_end = CUTS_BE_CAPI ()->sinks_.end ();

    if (sink_iter != sink_iter_end)
    {
      type_name = CUTS_BE_CAPI ()->fq_name (sink_iter->second, '.');
      version = sink_iter->second.VersionTag ();

      if (version.empty ())
      {
        version = "1.0";
        sink_iter->second.VersionTag () = version;
      }

      std::string class_name = sink_iter->second.SpecifyIdTag ();
      class_name[0] = ::toupper (class_name[0]);

      CUTS_BE_CAPI ()->outfile_
        << "if (type.equals (\""
        << type_name << "\") && version.equals(\""
        << version << "\"))" << std::endl
        << "{"
        << class_name << "Impl event =  new " << class_name << "Impl (mio);"
        << "this." << sink_iter->first << " (event);"
        << "}";

      for (++ sink_iter; sink_iter != sink_iter_end; ++ sink_iter)
      {
        type_name = CUTS_BE_CAPI ()->fq_name (sink_iter->second, '.');
        version = sink_iter->second.VersionTag ();

        if (version.empty ())
        {
          version = "1.0";
          sink_iter->second.VersionTag () = version;
        }

        class_name = sink_iter->second.SpecifyIdTag ();
        class_name[0] = ::toupper (class_name[0]);

        CUTS_BE_CAPI ()->outfile_
          << "else if (type.equals (\""
          << type_name << "\" && version.equals (\""
          << version << "\"))" << std::endl
          << "{"
          << class_name << "Impl event = new " << class_name << "Impl (mio);"
          << "this." << sink_iter->first << " (event);"
          << "}";
      }

      CUTS_BE_CAPI ()->outfile_
        << "else"
        << "{"
        << "System.err.println (\"error: callback not found [\""
        << "+ type + \" (\" + version + \")]\");"
        << "}";
    }

    CUTS_BE_CAPI ()->outfile_
      << "}"
      << "}"
      << "catch (Exception e)"
      << "{"
      << "e.printStackTrace ();"
      << "}"
      << "}";
  }

  CUTS_BE_CAPI ()->outfile_
    << "}"
    << std::endl
    << "// end of auto generated file" << std::endl;

  CUTS_BE_CAPI ()->reset ();
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
  // Get the information about the variable.
  PICML::PredefinedType type = variable.ref ();
  std::string type_name = type.type ().name ();
  std::string var_name = variable.name ();

  // Locate variable type in the mapping.
  CUTS_BE_Capi::PredefinedType_Map::const_iterator
    iter = CUTS_BE_Capi::predefined_type_map_.find (type.type ());

  // If we support the type, then we can generate a variable
  // for it. Otherwise, we generate a comment with an nice
  // error message.
  if (iter != CUTS_BE_Capi::predefined_type_map_.end ())
  {
    // Generate the accessor methods for the variable.
    CUTS_BE_CAPI ()->generate_accessor_methods (iter->second, var_name);

    // Generator the variable's definition.
    CUTS_BE_CAPI ()->outfile_
      << std::endl
      << "// variable : " << var_name << std::endl
      << "private " << iter->second << " " << var_name
      << "_";

    // Write the initial value for the variable.
    std::string initial_value = variable.InitialValue ();

    if (!initial_value.empty ())
    {
      CUTS_BE_CAPI ()->outfile_
        << " = " << initial_value;
    }

    CUTS_BE_CAPI ()->outfile_
      << ";";
  }
  else
  {
    CUTS_BE_CAPI ()->outfile_
      << std::endl
      << "// variable type (" << type_name << "not supported : "
      << var_name << std::endl
      << std::endl;
  }

  return true;
}

//
// CUTS_BE_Worker_Variable_T
//
bool CUTS_BE_Worker_Variable_T <CUTS_BE_Capi>::
generate (const PICML::WorkerType & type, const PICML::Worker & worker)
{
  std::string name = worker.name ();
  std::string var_name = type.name ();

  CUTS_BE_CAPI ()->outfile_
    << std::endl
    << "// workerVariable : " << var_name << std::endl
    << "private " << name
    << " " << var_name << "_ = new " << name
    << " ();";

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
  PICML::Action action_type = PICML::Action (action).Archetype ();

  CUTS_BE_CAPI ()->outfile_
    << "this." << action.name () << "_."
    << action_type.name () << " (";

  return true;
}

//
// CUTS_BE_Action_Property_T
//
bool CUTS_BE_Action_Property_T <CUTS_BE_Capi>::
generate (const PICML::Property & property)
{
  CUTS_BE_CAPI ()->outfile_ << property.DataValue ();

  if (-- CUTS_BE_CAPI ()->param_count_ > 0)
    CUTS_BE_CAPI ()->outfile_ << ", ";

  return true;
}

//
// CUTS_BE_Action_End_T
//
bool CUTS_BE_Action_End_T <CUTS_BE_Capi>::generate (void)
{
  CUTS_BE_CAPI ()->outfile_ << ");";
  return true;
}

//
// CUTS_BE_InEventPort_Begin_T
//
bool CUTS_BE_InEventPort_Begin_T <CUTS_BE_Capi>::
generate (const PICML::InEventPort & sink,
          const std::vector <PICML::Property> & properties)
{
  // Save the sink's information for later usage.
  std::string name = sink.name ();
  PICML::Event event = PICML::Event::Cast (sink.ref ());

  // Gather information about the event.
  std::string type_name = CUTS_BE_Capi::fq_name (event, '.');
  std::string version = event.VersionTag ();

  if (version.empty ())
    version = "1.0";

  // Commonly used strings based on the event's name.
  std::string sink_classname = name + "Sink";
  std::string sink_variable = name + "_";

  CUTS_BE_CAPI ()->outfile_
    << std::endl
    << "/**" << std::endl
    << " * subscriberName    : " << name << std::endl
    << " * subscriberType    : " << type_name << std::endl
    << " * subscriberVersion : " << version << std::endl
    << " */" << std::endl
    << "private class " << sink_classname << " extends JbiSink"
    << "{"
    << "public " << sink_classname << " ("
    << CUTS_BE_CAPI ()->impl_classname_ << " parent)" << std::endl
    << "  throws PermissionDeniedException, UnsupportedVersionException," << std::endl
    << "         InvalidPredicateException, PredicateLanguageException," << std::endl
    << "         PermissionDeniedException, SequenceStateException," << std::endl
    << "         UnrecognizedObjectTypeException, MappingException," << std::endl
    << "         IOException" << std::endl
    << "{"
    << "super (parent.getJbiConnection (), \""
    << type_name << "\", \""  << version << "\");";

  // Configure the port based on the provided properties.
  std::for_each (properties.begin (),
                 properties.end (),
                 boost::bind  (&CUTS_BE_InEventPort_Begin_T <CUTS_BE_Capi>::configure,
                               sink, _1));

  // Register the callback with the sequence.
  CUTS_BE_CAPI ()->outfile_
    << "this.setCallback (parent);"
    << "}"
    << "}"
    << std::endl
    << "/**" << std::endl
    << " * subscriber : " << name << std::endl
    << " */" << std::endl
    << "private " << sink_classname << " "
    << sink_variable << " = null;"
    << std::endl;

  std::string tag_name = event.SpecifyIdTag ();
  tag_name[0] = ::toupper (tag_name[0]);

  // Generate the start of the method's implementation.
  CUTS_BE_CAPI ()->outfile_
    << "void " << sink.name ()
    << " (JbiEvent <" << tag_name << "> ev)"
    << "{"
    << "try"
    << "{";

  return true;
};

//
// CUTS_BE_InEventPort_Begin_T::configure
//
void CUTS_BE_InEventPort_Begin_T <CUTS_BE_Capi>::
configure (const PICML::InEventPort & sink,
           const PICML::Property & property)
{
  std::string propname = property.name ();

  if (propname == "predicate")
  {
    PICML::Component parent = PICML::Component::Cast (sink.parent ());

    // Construct the name of the predicate.
    std::ostringstream predicate_name;
    predicate_name
      << "parent.getInstanceName () + \"." << sink.name () << ".predicate";

    // Write the code to set the predicate.
    CUTS_BE_CAPI ()->outfile_
      << "this.setPredicate (" << predicate_name.str () << "\", "
      << property.DataValue () << ");";
  }
}

//
// CUTS_BE_InEventPort_End_T
//
bool CUTS_BE_InEventPort_End_T <CUTS_BE_Capi>::
generate (const PICML::InEventPort & sink,
          const std::vector <PICML::Property> & properties)
{
  CUTS_BE_CAPI ()->outfile_
    << "}"
    << "catch (Exception e)"
    << "{"
    << "e.printStackTrace ();"
    << "}"
    << "}";

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
generate (const PICML::MultiInputAction & action)
{
  std::string name = action.name ();

  CUTS_BE_Capi::Env_Seen_Map::iterator iter =
    CUTS_BE_CAPI ()->env_seen_.find (name);

  if (iter == CUTS_BE_CAPI ()->env_seen_.end ())
    return false;

  if (iter->second)
    return false;

  iter->second = true;

  CUTS_BE_CAPI ()->outfile_
    << std::endl
    << "/**" << std::endl
    << " * environmentAction : " << name << std::endl
    << " */" << std::endl
    << "protected void jbi_" << name << " ()"
    << "{"
    << "try"
    << "{";

  CUTS_BE_CAPI ()->generate_required_method_impl (name);

  return true;
}

//
// CUTS_BE_Environment_Method_Begin_T
//
bool CUTS_BE_Environment_Method_End_T <CUTS_BE_Capi>::
generate (const PICML::MultiInputAction & action)
{
  CUTS_BE_CAPI ()->outfile_
    << "}"
    << "catch (Exception e)"
    << "{"
    << "e.printStackTrace ();"
    << "}"
    << "}";

  return true;
}

//
// CUTS_BE_Environment_End_T
//
bool CUTS_BE_Environment_End_T <CUTS_BE_Capi>::
generate (const PICML::Component & component)
{
  CUTS_BE_Capi::Env_Seen_Map::const_iterator
    iter = CUTS_BE_CAPI ()->env_seen_.begin (),
    iter_end = CUTS_BE_CAPI ()->env_seen_.end ();

  for (; iter != iter_end; ++ iter)
  {
    if (!iter->second)
    {
      CUTS_BE_CAPI ()->outfile_
        << std::endl
        << "/**" << std::endl
        << " * environmentAction : " << iter->first << std::endl
        << " */" << std::endl
        << "protected void jbi_" << iter->first << " ()";
      CUTS_BE_CAPI ()->generate_throws_signature (iter->first);
      CUTS_BE_CAPI ()->outfile_
        << "{"
        << "try"
        << "{";

      CUTS_BE_CAPI ()->generate_required_method_impl (iter->first);

      CUTS_BE_CAPI ()->outfile_
        << "}"
        << "catch (Exception e)"
        << "{"
        << "e.printStackTrace ();"
        << "}"
        << "}";
    }
  }

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
      << std::endl
      << "/**" << std::endl
      << " * periodicEventHandler : " << periodic_name << std::endl
      << " *" << std::endl
      << " * Implementation for the specified periodic event." << std::endl
      << " */" << std::endl
      << "public void " << periodic_name << " ()"
      << "{"
      << "try"
      << "{";

    // Save the periodic event's name.
    CUTS_BE_CAPI ()->periodics_.insert (
      std::make_pair (periodic_name, periodic.Hertz ()));
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
  std::string parent_name = CUTS_BE_CAPI ()->impl_classname_;
  PICML::Input input = periodic.dstInput ();

  if (input != Udm::null)
  {
    PICML::InputAction input_action = input.dstInput_end ();

    std::string periodic_name = input_action.name ();
    std::string periodic_task = periodic_name + "PeriodicTask";

    CUTS_BE_CAPI ()->outfile_
      << "}"
      << "catch (Exception e)"
      << "{"
      << "e.printStackTrace ();"
      << "}"
      << "}"
      << std::endl
      << "/**" << std::endl
      << " * @class " << periodic_name << std::endl
      << " *" << std::endl
      << " * Defines the handler for the periodicSend PeriodicEvent element" << std::endl
      << " * specified in the component behavior model." << std::endl
      << " */" << std::endl
      << "private class " << periodic_task << " extends PeriodicTask"
      << "{"
      << "/**" << std::endl
      << " * The owner of the task" << std::endl
      << " */" << std::endl
      << "private " << parent_name << " component_ = null;"
      << std::endl
      << "public " << periodic_task << " ("
      << parent_name << " component)"
      << "{"
      // Need to update architecture to handle different distributions.
      << "super (1.0);"
      << "this.component_ = component;"
      << "}"
      << std::endl
      << "public void handleTimeout ()"
      << "{"
      << "this.component_." << periodic_name << "();"
      << "}"
      << "}"
      << std::endl
      << "/**" << std::endl
      << " * periodicTask : " << periodic_name << std::endl
      << " */" << std::endl
      << "private " << periodic_task << " "
      << periodic_task << "_ = " << std::endl
      << "  new " << periodic_task << " (this);";
  }

  return true;
}

//
// CUTS_BE_OutputAction_Begin_T
//
bool CUTS_BE_OutputAction_Begin_T <CUTS_BE_Capi>::
generate (const PICML::OutputAction & action)
{
  // Locate the event for the output action.
  std::string name = action.name ();
  PICML::Event event = CUTS_BE_CAPI ()->sources_[name];

  // Construct the fully qualified name for the event.
  std::string fq_name = CUTS_BE_CAPI ()->fq_name (event, '.');
  std::string tagname = event.SpecifyIdTag ();

  tagname[0] = ::toupper (tagname[0]);

  CUTS_BE_CAPI ()->outfile_ << "// Create a new event for publishing" << std::endl
                            << tagname << "Impl ev_" << action.uniqueId ()
                            << "_ = new " << tagname << "Impl ();"
                            << std::endl;

  return true;
}

//
// CUTS_BE_OutputAction_Property_T
//
bool CUTS_BE_OutputAction_Property_T <CUTS_BE_Capi>::
generate (const PICML::OutputAction & action,
          const PICML::Property & property)
{
  std::string name = property.name ();

  if (name == "metadata")
  {
    // We handle the metadata property specially.
    PICML::DataType datatype = property.DataType_child ();
    PICML::MemberType mt = datatype.ref ();
    Uml::Class meta = mt.type ();

    if (meta == PICML::String::meta)
    {
      CUTS_BE_CAPI ()->outfile_
        << "ev_" << action.uniqueId () << "_." <<
        CUTS_BE_CAPI ()->setter_method (property.name ())
        << " (" << property.DataValue () << ");";
    }
    else if (meta == PICML::Event::meta)
    {

    }
  }
  else if (name == "payload")
  {
    CUTS_BE_CAPI ()->outfile_ << "ev_" << action.uniqueId ()
                              << "_.setPayload (" << property.DataValue ()
                              << ");";
  }
  else
  {
    CUTS_BE_CAPI ()->outfile_
      << "ev_" << action.uniqueId () << "_.getMetadata ()." <<
      CUTS_BE_CAPI ()->setter_method (property.name ())
      << " (" << property.DataValue () << ");";
  }

  return true;
}

//
// CUTS_BE_OutputAction_End_T
//
bool CUTS_BE_OutputAction_End_T <CUTS_BE_Capi>::
generate (const PICML::OutputAction & action)
{
  CUTS_BE_CAPI ()->outfile_
    << std::endl
    << "// Publishing the event (ev_"
    << action.uniqueId () << ")." << std::endl
    << "this." << action.name () << "_.publishData (ev_"
    << action.uniqueId () << "_);";

  return true;
}

//
// CUTS_BE_Branches_Begin_T
//
bool CUTS_BE_Branches_Begin_T <CUTS_BE_Capi>::generate (size_t branches)
{
  CUTS_BE_CAPI ()->branches_.push (1);
  return true;
}

//
// CUTS_BE_Branch_Condition_Begin_T
//
bool CUTS_BE_Branch_Condition_Begin_T <CUTS_BE_Capi>::generate (void)
{
  // We need to generate an "else if" statement if this is not
  // the first transition.
  if (!CUTS_BE_CAPI ()->branches_.empty () &&
       CUTS_BE_CAPI ()->branches_.top () ++ > 1)
  {
    CUTS_BE_CAPI ()->outfile_
      << "else ";
  }

  // Generate the if condition for the branch.
  CUTS_BE_CAPI ()->outfile_
    << "if (";

  return true;
}

//
// CUTS_BE_Branch_Condition_End_T
//
bool CUTS_BE_Branch_Condition_End_T <CUTS_BE_Capi>::generate (void)
{
  // Generate the end of the if condition for the branch.
  CUTS_BE_CAPI ()->outfile_
    << ")";

  return true;
}

//
// CUTS_BE_Branch_No_Condition_T
//
bool CUTS_BE_Branch_No_Condition_T <CUTS_BE_Capi>::generate (void)
{
  CUTS_BE_CAPI ()->outfile_
    << "else";

  return true;
}

//
// CUTS_BE_Branch_End_T
//
bool CUTS_BE_Branch_Begin_T <CUTS_BE_Capi>::generate (void)
{
  CUTS_BE_CAPI ()->outfile_
    << "{";

  return true;
}

//
// CUTS_BE_Branch_End_T
//
bool CUTS_BE_Branch_End_T <CUTS_BE_Capi>::generate (void)
{
  CUTS_BE_CAPI ()->outfile_
    << "}";

  return true;
}

//
// CUTS_BE_Branches_End_T
//
bool CUTS_BE_Branches_End_T <CUTS_BE_Capi>::generate (void)
{
  CUTS_BE_CAPI ()->branches_.pop ();
  return true;
};

//
// CUTS_BE_Do_While_Begin_T
//
bool CUTS_BE_Do_While_Begin_T <CUTS_BE_Capi>::generate (void)
{
  CUTS_BE_CAPI ()->outfile_
    << "do"
    << "{";

  return true;
}

//
// CUTS_BE_Do_While_Begin_T
//
bool CUTS_BE_Do_While_End_T <CUTS_BE_Capi>::generate (void)
{
  CUTS_BE_CAPI ()->outfile_
    << "}"
    << "while ";

  return true;
}


//
// CUTS_BE_Do_While_Condition_Begin_T
//
bool CUTS_BE_Do_While_Condition_Begin_T <CUTS_BE_Capi>::generate (void)
{
  CUTS_BE_CAPI ()->outfile_
    << "(";

  return true;
}

//
// CUTS_BE_Do_While_Condition_End_T
//
bool CUTS_BE_Do_While_Condition_End_T <CUTS_BE_Capi>::generate (void)
{
  CUTS_BE_CAPI ()->outfile_
    << ");";

  return true;
}

//
// CUTS_BE_Equal_To_T
//
bool CUTS_BE_Equal_To_T <CUTS_BE_Capi>::
generate (const char * first, const char * last)
{
  CUTS_BE_CAPI ()->outfile_
    << " == ";

  return true;
}

//
// CUTS_BE_Not_Equal_To_T
//
bool CUTS_BE_Not_Equal_To_T <CUTS_BE_Capi>::
generate (const char * first, const char * last)
{
  CUTS_BE_CAPI ()->outfile_
    << " != ";

  return true;
}

//
// CUTS_BE_Greater_Than_T
//
bool CUTS_BE_Greater_Than_T <CUTS_BE_Capi>::
generate (const char * first, const char * last)
{
  CUTS_BE_CAPI ()->outfile_
    << " > ";

  return true;
}

//
// CUTS_BE_Greater_Than_Equal_To_T
//
bool CUTS_BE_Greater_Than_Equal_To_T <CUTS_BE_Capi>::
generate (const char * first, const char * last)
{
  CUTS_BE_CAPI ()->outfile_
    << " >= ";

  return true;
}

//
// CUTS_BE_Less_Than_T
//
bool CUTS_BE_Less_Than_T <CUTS_BE_Capi>::
generate (const char * first, const char * last)
{
  CUTS_BE_CAPI ()->outfile_
    << " < ";

  return true;
}

//
// CUTS_BE_Less_Than_Equal_To_T
//
bool CUTS_BE_Less_Than_Equal_To_T <CUTS_BE_Capi>::
generate (const char * first, const char * last)
{
  CUTS_BE_CAPI ()->outfile_
    << " <= ";

  return true;
}

//
// CUTS_BE_Identifier_T
//
bool CUTS_BE_Identifier_T <CUTS_BE_Capi>::
generate (const char * begin, const char * end)
{
  std::string str (begin, end);

  CUTS_BE_CAPI ()->outfile_
    << "this." << str << "_";

  return true;
}

//
// CUTS_BE_Transcribe_Text_T
//
bool CUTS_BE_Transcribe_Text_T <CUTS_BE_Capi>::
generate (const char * begin, const char * end)
{
  std::string str (begin, end);

  CUTS_BE_CAPI ()->outfile_
    << str;

  return true;
}

//
// CUTS_BE_Transcribe_Char_T
//
bool CUTS_BE_Transcribe_Char_T <CUTS_BE_Capi>::generate (char ch)
{
  CUTS_BE_CAPI ()->outfile_
    << ch;

  return true;
}

//
// CUTS_BE_While_Condition_Begin_T
//
bool CUTS_BE_While_Condition_Begin_T <CUTS_BE_Capi>::generate (void)
{
  CUTS_BE_CAPI ()->outfile_
    << "while (";

  return true;
}

//
// CUTS_BE_While_Condition_End_T
//
bool CUTS_BE_While_Condition_End_T <CUTS_BE_Capi>::generate (void)
{
  CUTS_BE_CAPI ()->outfile_
    << ")";

  return true;
}

//
// CUTS_BE_While_Begin_T
//
bool CUTS_BE_While_Begin_T <CUTS_BE_Capi>::generate (void)
{
  CUTS_BE_CAPI ()->outfile_
    << "{";

  return true;
}

//
// CUTS_BE_While_End_T
//
bool CUTS_BE_While_End_T <CUTS_BE_Capi>::generate (void)
{
  CUTS_BE_CAPI ()->outfile_
    << "}";

  return true;
}

//
// CUTS_BE_Postcondition_T
//
bool CUTS_BE_Postcondition_T <CUTS_BE_Capi>::
generate (const std::string & postcondition)
{
  CUTS_BE_CAPI ()->outfile_
    << postcondition
    << std::endl;

  return true;
}

//
// CUTS_BE_Attribute_Variable_T
//
bool CUTS_BE_Attribute_Variable_T <CUTS_BE_Capi>::
generate (const PICML::ReadonlyAttribute & attr)
{
  std::string name = attr.name ();
  PICML::AttributeMember member = attr.AttributeMember_child ();

  try
  {
    PICML::PredefinedType type = PICML::PredefinedType::Cast (member.ref ());

    CUTS_BE_CAPI ()->outfile_
      << std::endl
      << "/**" << std::endl
      << " * attribute variable : " << name << std::endl
      << " */" << std::endl
      << "private "
      << CUTS_BE_CAPI ()->predefined_type_map_[type.type ()]
      << " " << name << "_;";
  }
  catch (...)
  {

  }

  return true;
}

//
// CUTS_BE_ReadonlyAttribute_Begin_T
//
bool CUTS_BE_ReadonlyAttribute_Begin_T <CUTS_BE_Capi>::
generate (const PICML::ReadonlyAttribute & readonly)
{
  std::string return_type;

  try
  {
    PICML::AttributeMember member = readonly.AttributeMember_child ();
    PICML::PredefinedType type = PICML::PredefinedType::Cast (member.ref ());

    return_type = CUTS_BE_CAPI ()->predefined_type_map_[type.type ()];
  }
  catch (...)
  {

  }

  std::string name = readonly.name ();

  if (!return_type.empty ())
  {
    CUTS_BE_CAPI ()->outfile_
      << std::endl
      << "/**" << std::endl
      << " * attribute getter : " << name << std::endl
      << " */" << std::endl
      << "public " << return_type << " "
      << CUTS_BE_CAPI ()->getter_method (name) << " ()"
      << "{";
  }
  else
  {
    CUTS_BE_CAPI ()->outfile_
      << "// unrecognized variable type for attribute [" << name
      << "]; not generating getter method" << std::endl;
  }

  return true;
}

//
// CUTS_BE_ReadonlyAttribute_End_T
//
bool CUTS_BE_ReadonlyAttribute_End_T <CUTS_BE_Capi>::
generate (const PICML::ReadonlyAttribute & readonly)
{
  CUTS_BE_CAPI ()->outfile_
    << "return this." << readonly.name () << "_;"
    << "}";

  return true;
}

//
// CUTS_BE_Attribute_Begin_T
//
bool CUTS_BE_Attribute_Begin_T <CUTS_BE_Capi>::
generate (const PICML::Attribute & attr)
{
  std::string var_type;

  try
  {
    PICML::AttributeMember member = attr.AttributeMember_child ();
    PICML::PredefinedType type = PICML::PredefinedType::Cast (member.ref ());

    var_type = CUTS_BE_CAPI ()->predefined_type_map_[type.type ()];
  }
  catch (...)
  {

  }

  std::string name = attr.name ();

  if (!var_type.empty ())
  {
    CUTS_BE_CAPI ()->outfile_
      << std::endl
      << "/**" << std::endl
      << " * attribute setter : " << name << std::endl
      << " */" << std::endl
      << "public void "
      << CUTS_BE_CAPI ()->setter_method (name)
      << " (" << var_type << " " << name << ")"
      << "{";
  }
  else
  {
    CUTS_BE_CAPI ()->outfile_
      << "// unrecognized variable type for attribute [" << name
      << "]; not generating setter method" << std::endl;
  }

  return true;;
}

//
// CUTS_BE_Attribute_End_T
//
bool CUTS_BE_Attribute_End_T <CUTS_BE_Capi>::
generate (const PICML::Attribute & attr)
{
  std::string name = attr.name ();

  CUTS_BE_CAPI ()->outfile_
    << "this." << name << "_ = " << name << ";"
    << "}";

  CUTS_BE_ReadonlyAttribute_Begin_T <CUTS_BE_Capi>::generate (attr);
  CUTS_BE_ReadonlyAttribute_End_T <CUTS_BE_Capi>::generate (attr);

  return true;
}

//
// CUTS_BE_Action_Properties_Begin_T
//
bool CUTS_BE_Action_Properties_Begin_T <CUTS_BE_Capi>::
generate (size_t count)
{
  CUTS_BE_CAPI ()->param_count_ = count;
  return true;
}

//
// CUTS_BE_False_T
//
bool CUTS_BE_False_T <CUTS_BE_Capi>::
generate (const char * first, const char * last)
{
  CUTS_BE_CAPI ()->outfile_
    << "false";

  return true;
}

//
// CUTS_BE_False_T
//
bool CUTS_BE_True_T <CUTS_BE_Capi>::
generate (const char * first, const char * last)
{
  CUTS_BE_CAPI ()->outfile_
    << "true";

  return true;
}

//
// CUTS_BE_Precondition_T
//
bool CUTS_BE_Precondition_T <CUTS_BE_Capi>::
generate (const std::string & precondition)
{
  CUTS_BE_CAPI ()->outfile_ << precondition;
  return true;
}

//
// CUTS_BE_Finalize_T
//
void CUTS_BE_Finalize_T <CUTS_BE_Capi>::
generate (const PICML::RootFolder & root)
{
  std::string outdir = CUTS_BE_OPTIONS ()->output_directory_;

  // We need to generate the XML mappings for all the event types. This
  // is necessary so Castor can map the Java -> XML correctly. ;-)
  std::for_each (CUTS_BE_CAPI ()->workspace_events_.begin (),
                 CUTS_BE_CAPI ()->workspace_events_.end (),
                 boost::bind (&CUTS_BE_Finalize_T <CUTS_BE_Capi>::generate_mapping_file,
                              _1,
                              outdir));

  PICML::RootFolder rf (root);

  // Generate the script that sets the classpath.
  Set_Classpath_Script_Generator classpath (outdir);
  rf.Accept (classpath);

  // Generate the script that registers the MIO types.
  Register_Type_Script_Generator register_types (outdir);
  register_types.generate (CUTS_BE_CAPI ()->workspace_events_);
}

//
// generate_mapping_file
//
void CUTS_BE_Finalize_T <CUTS_BE_Capi>::
generate_mapping_file (const PICML::Event & event, const std::string & outdir)
{
  PICML::Event e (event);

  // Generate the XML mapping file.
  XML_Mapping_File_Generator mapping (outdir);
  e.Accept (mapping);

  // Generate the XSD file.
  XSD_File_Generator xsd (outdir);
  e.Accept (xsd);

  CUTS_BE_CAPI_Event_Impl_Generator eventimpl (outdir);
  e.Accept (eventimpl);
}
