// $Id$

#include "CAPI_Generators.h"

#if !defined (__CUTS_INLINE__)
#include "CAPI_Generators.inl"
#endif

#include "CAPI_Preprocessor.h"
#include "Set_Classpath_Script_Generator.h"
#include "Register_Type_Script_Generator.h"
#include "XML_Mapping_File_Generator.h"
#include "CAPI_Event_Impl_Generator.h"
#include "XSD_File_Generator.h"

#include "../../lang/java/Java_Variable_Type.h"
#include "../../BE_Options.h"
#include "../../BE_Scope_Manager.h"

#include "boost/bind.hpp"
#include "Uml.h"

//
// CUTS_BE_File_Open_T
//
void CUTS_BE_File_Open_T <CUTS_BE_Capi::Context>::
generate (const PICML::ComponentImplementationContainer & container,
          const PICML::MonolithicImplementation & impl)
{
  // Locate the preprocessing of the implementation. If this is a
  // proxy implementation, then we ignore it. It's going to cause
  // more problems than we would like.
  CUTS_BE_PREPROCESSOR (CUTS_BE_Capi::Context)->impls ().find (container.name (), this->ctx_.impl_node_);

  if (0 == this->ctx_.impl_node_)
    return;

  std::string filename =
    CUTS_BE_OPTIONS ()->output_directory_ + "/"
    + std::string (impl.name ()) + ".java";

  if (!this->ctx_.source_.good ())
    this->ctx_.source_.clear ();

  // Open the XML file for writing.
  this->ctx_.source_.open (filename.c_str ());

  if (!this->ctx_.source_.is_open ())
    return;

  // Create a formatter for the XML file.
  this->ctx_.source_formatter_.reset (new CUTS_BE_Capi::Context::formatter_type (this->ctx_.source_));
}

//
// CUTS_BE_File_Close_T
//
void CUTS_BE_File_Close_T <CUTS_BE_Capi::Context>::
generate (const PICML::ComponentImplementationContainer & container,
          const PICML::MonolithicImplementation & impl)
{
  this->ctx_.source_formatter_.reset ();
  this->ctx_.source_.close ();
}

//
// CUTS_BE_Prologue_T
//
void CUTS_BE_Prologue_T <CUTS_BE_Capi::Context>::
generate (const PICML::ComponentImplementationContainer & container,
          const PICML::MonolithicImplementation & impl)
{
  this->ctx_.source_
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
    << "import cuts.jbi.client.*;";
}

//
// CUTS_BE_Component_Impl_Begin_T
//
void CUTS_BE_Component_Impl_Begin_T <CUTS_BE_Capi::Context>::
generate (const PICML::MonolithicImplementation & mono, const PICML::Component & component)
{
  typedef std::vector <PICML::InEventPort> InEventPort_Set;
  InEventPort_Set inputs = component.InEventPort_kind_children ();

  typedef std::vector <PICML::OutEventPort> OutEventPort_Set;
  OutEventPort_Set outputs = component.OutEventPort_kind_children ();

  if (!inputs.empty () || !outputs.empty ())
  {
    this->ctx_.source_
      << std::endl
      << "// imports for handling events" << std::endl
      << "import cuts.jbi.client.JbiEvent;"
      << "import org.exolab.castor.xml.MarshalException;"
      << "import org.exolab.castor.xml.ValidationException;"
      << "import org.exolab.castor.mapping.MappingException;"
      << "import java.io.IOException;";

    std::set <std::string> event_types;

    if (!inputs.empty ())
    {
      // Generate the import files for receiving MIOs.
      this->ctx_.source_
        << std::endl
        << "// imports for receiving MIOs" << std::endl
        << "import org.infospherics.jbi.client.ObjectAvailableCallback;"
        << "import org.infospherics.jbi.client.InfoObject;";

      // Store the ev types for later usage. We also need to
      // generate the import files for the ev objects.
      PICML::Event ev;
      std::string version, type_name;

      InEventPort_Set::const_iterator
        iter = inputs.begin (), iter_end = inputs.end ();

      for ( ; iter != iter_end; ++ iter)
      {
        // Get the typename of the ev.
        PICML::EventType et = iter->ref ();
        if (et.type () != PICML::Event::meta)
          continue;

        ev = PICML::Event::Cast (et);
        version = ev.VersionTag ();

        type_name = CUTS_BE_Java::fq_type (ev, ".", false);

        if (type_name != this->ctx_.jbi_anyevent_.first)
        {
          // Store it in the ev type for later on.
          this->ctx_.workspace_events_.insert (ev);
          event_types.insert (type_name);

          // Store the name of the ev since we need to tell the ANT file to
          // generate the Java bindings for its schema definition.
          this->ctx_.impl_node_->maplist_["events"].insert (type_name);
        }

        this->ctx_.sinks_.insert (std::make_pair (iter->name (), ev));
      }
    }

    if (!outputs.empty ())
    {
      // Store the ev types for later usage. We also need to
      // generate the import files for the ev objects.
      PICML::Event ev;
      std::string type_name, version;

      OutEventPort_Set::const_iterator
        iter = outputs.begin (), iter_end = outputs.end ();

      for ( ; iter != iter_end; ++ iter)
      {
        // Get the typename of the ev.
        PICML::EventType et = iter->ref ();

        if (et.type () != PICML::Event::meta)
          continue;

        PICML::Event ev = PICML::Event::Cast (et);
        version = ev.VersionTag ();

        type_name = CUTS_BE_Java::fq_type (ev, ".", false);

        if (type_name != this->ctx_.jbi_anyevent_.first)
        {
          // Store it in the ev type for later on.
          this->ctx_.workspace_events_.insert (ev);
          event_types.insert (type_name);

          // Store the name of the ev since we need to tell the ANT file to
          // generate the Java bindings for its schema definition.
          this->ctx_.impl_node_->maplist_["events"].insert (type_name);

          // Save the ev's information in the sources collection.
          if (version.empty ())
            version = "1.0";
        }

        // Regardless of the ev, we need to store it for later.
        this->ctx_.sources_.insert (std::make_pair (iter->name (), ev));
      }
    }

    if (!event_types.empty ())
    {
      this->ctx_.source_
        << std::endl
        << "// imports for used ev types" << std::endl;

      // Generate the import files for the ev types.
      std::set <std::string>::const_iterator
        iter = event_types.begin (), iter_end = event_types.end ();

      for (; iter != iter_end; ++ iter)
      {
        this->ctx_.source_
          << "import " << *iter << ".*;";
      }
    }
  }

  typedef std::vector <PICML::PeriodicEvent> PeriodicEvent_Set;
  PeriodicEvent_Set periodics = component.PeriodicEvent_kind_children ();

  if (!periodics.empty ())
  {
    // Generate the import file for periodic events.
    this->ctx_.source_
      << std::endl
      << "// imports for periodic events" << std::endl
      << "import CUTS.PeriodicTask;"
      << "import java.util.TimerTask;";
  }


  // Generate the remaining imports for this implementation.
  const CUTS_String_Set & imports =
    this->ctx_.impl_node_->maplist_["imports"];

  CUTS_String_Set::const_iterator
    imports_iter = imports.begin (), imports_iter_end = imports.end ();

  for (; imports_iter != imports_iter_end; ++ imports_iter)
  {
    this->ctx_.source_
      << "import " << *imports_iter << ";";
  }

  // The name of the class is the name of the monolithic implementation.
  // This is also the name of the file, which is a requirement of Java!!
  std::string class_name = mono.name ();
  this->ctx_.impl_classname_ = class_name;

  this->ctx_.source_
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
    this->ctx_.source_
      << std::endl
      << "  implements ObjectAvailableCallback" << std::endl;
  }

  this->ctx_.source_
    << "{"
    << "/**" << std::endl
    << " * Default constructor" << std::endl
    << " */" << std::endl
    << "public " << class_name << " ()"
    << "{";

  if (!periodics.empty ())
  {
    // Set the strategy type for the periodic ev
    std::string distribution;

    PeriodicEvent_Set::iterator
      periodic_iter = periodics.begin (),
      periodic_iter_end = periodics.end ();

    for ( ; periodic_iter != periodic_iter_end; ++ periodic_iter)
    {
      this->ctx_.source_ << "this."
                                << periodic_iter->name ()
                                << "_.setPeriodicTaskStrategy (new CUTS."
                                << periodic_iter->Distribution ()
                                << "PeriodicTaskStrategy ());";
    }
  }

  this->ctx_.source_
    << "}";
}

//
// generate_worker_import
//
void CUTS_BE_Component_Impl_Begin_T <CUTS_BE_Capi::Context>::
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
  this->ctx_.source_
    << "import " << import_path.str ().c_str () << ";";
}

//
// CUTS_BE_Component_Impl_End_T
//
void CUTS_BE_Component_Impl_End_T <CUTS_BE_Capi::Context>::
generate (const PICML::MonolithicImplementation & mono, const PICML::Component & component)
{
  CUTS_BE_Capi::Context::Event_Port_Map::const_iterator
    iter = this->ctx_.sources_.begin (),
    iter_end = this->ctx_.sources_.end ();

  std::string source_classname, source_variable;
  std::string type_name, version, fq_name;

  for ( ; iter != iter_end; iter ++)
  {
    source_classname = iter->first + "Source";
    source_variable = iter->first + "_";

    type_name = CUTS_BE_Java::fq_type (iter->second, ".", false);

    if (type_name != this->ctx_.jbi_anyevent_.first)
    {
      version = iter->second.VersionTag ();

      if (version.empty ())
      {
        version = "1.0";
        iter->second.VersionTag () = version;
      }

      this->ctx_.source_
        << std::endl
        << "/**" << std::endl
        << " * publisherName    : " << iter->first << std::endl
        << " * publisherType    : " << type_name << std::endl
        << " * publisherVersion : " << version << std::endl
        << " */" << std::endl
        << "private class " << source_classname << " extends JbiSource"
        << "{"
        << "public " << source_classname << " ("
        << this->ctx_.impl_classname_ << " parent)" << std::endl
        << "  throws PermissionDeniedException, UnsupportedVersionException," << std::endl
        << "         MappingException, SequenceStateException, IOException" << std::endl
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
    else
    {
      this->ctx_.source_
        << std::endl
        << "/**" << std::endl
        << " * publisherName    : " << iter->first << std::endl
        << " * publisherType    : cuts.jbi.client.JbiAnyEvent" << std::endl
        << " */" << std::endl
        << "private class " << source_classname << " extends JbiSource"
        << "{"
        << "public " << source_classname << " ("
        << this->ctx_.impl_classname_ << " parent)" << std::endl
        << "  throws PermissionDeniedException, UnsupportedVersionException," << std::endl
        << "         MappingException, IOException" << std::endl
        << "{"
        << "super (parent.getJbiConnection ());"
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
  }

  if (!this->ctx_.sinks_.empty ())
  {
    // Generate the entry point for the client application.
    this->ctx_.source_
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

    CUTS_BE_Capi::Context::Event_Port_Map::const_iterator
      sink_iter = this->ctx_.sinks_.begin (),
      sink_iter_end = this->ctx_.sinks_.end ();

    std::string anyevent_sink;

    if (sink_iter != sink_iter_end)
    {
      std::string class_name;
      std::string type_name = CUTS_BE_Java::fq_type (sink_iter->second, ".", false);

      if (type_name != this->ctx_.jbi_anyevent_.first)
      {
        // We are working with a *regular* ev.
        version = sink_iter->second.VersionTag ();

        if (version.empty ())
        {
          version = "1.0";
          sink_iter->second.VersionTag () = version;
        }

        class_name = sink_iter->second.SpecifyIdTag ();
        class_name[0] = ::toupper (class_name[0]);

        this->ctx_.source_
          << "if (type.equals (\""
          << type_name << "\") && version.equals(\""
          << version << "\"))" << std::endl
          << "{"
          << class_name << "Impl ev =  new " << class_name << "Impl (mio);"
          << "this." << sink_iter->first << " (ev);"
          << "}";
      }
      else
      {
        // Save the name of the any ev sink.
        anyevent_sink = sink_iter->first;
      }

      // Let's interpret the remainder of the ev sinks.
      for (++ sink_iter; sink_iter != sink_iter_end; ++ sink_iter)
      {
        type_name = CUTS_BE_Java::fq_type (sink_iter->second, ".", false);

        if (type_name != this->ctx_.jbi_anyevent_.first)
        {
          version = sink_iter->second.VersionTag ();

          if (version.empty ())
          {
            version = "1.0";
            sink_iter->second.VersionTag () = version;
          }

          class_name = sink_iter->second.SpecifyIdTag ();
          class_name[0] = ::toupper (class_name[0]);

          this->ctx_.source_
            << "else if (type.equals (\""
            << type_name << "\" && version.equals (\""
            << version << "\"))" << std::endl
            << "{"
            << class_name << "Impl ev = new " << class_name << "Impl (mio);"
            << "this." << sink_iter->first << " (ev);"
            << "}";
        }
        else
        {
          // Save the name of the any ev sink.
          anyevent_sink = sink_iter->first;
        }
      }

      // Finally, we can generate the final part of the multiplex operation.
      // This will either be an JbiAnyEvent, or an error message.
      if (!anyevent_sink.empty ())
      {
        if (this->ctx_.sinks_.size () > 1)
        {
          // This is one of many sinks of the component.
          this->ctx_.source_
            << "else"
            << "{"
            << "JbiAnyEvent ev = new JbiAnyEvent (mio);"
            << "this." << anyevent_sink << " (ev);"
            << "}";
        }
        else
        {
          // This is the one and only sink of the component.
          this->ctx_.source_
            << "JbiAnyEvent ev = new JbiAnyEvent (mio);"
            << "this." << anyevent_sink << " (ev);";
        }
      }
      else
      {
        // This is the error message for an invalid ev. If this part
        // is ever reached, then there has to something wrong with the
        // generated code.
        this->ctx_.source_
          << "else"
          << "{"
          << "System.err.println (\"error: callback not found [\""
          << "+ type + \" (\" + version + \")]\");"
          << "}";
      }
    }

    // Close off the method and the implementation.
    this->ctx_.source_
      << "}"
      << "}"
      << "catch (Exception e)"
      << "{"
      << "e.printStackTrace ();"
      << "}"
      << "}";
  }

  this->ctx_.source_
    << "}"
    << std::endl
    << "// end of auto generated file" << std::endl;

  this->ctx_.reset ();
}

//
// CUTS_BE_InEventPort_Begin_T
//
void CUTS_BE_InEventPort_Begin_T <CUTS_BE_Capi::Context>::
generate (const PICML::InEventPort & sink,
          const std::vector <PICML::Property> & properties)
{
  // Save the sink's information for later usage.
  std::string name = sink.name ();
  PICML::Event ev = PICML::Event::Cast (sink.ref ());

  // Gather information about the ev.
  std::string type_name = CUTS_BE_Java::fq_type (ev, ".", false);

  // Commonly used strings based on the ev's name.
  std::string sink_classname = name + "Sink";
  std::string sink_variable = name + "_";
  bool anyevent = false;

  if (type_name != this->ctx_.jbi_anyevent_.first)
  {
    std::string version = ev.VersionTag ();

    if (version.empty ())
    {
      version = "1.0";
      ev.VersionTag () = version;
    }

    this->ctx_.source_
      << std::endl
      << "/**" << std::endl
      << " * subscriberName    : " << name << std::endl
      << " * subscriberType    : " << type_name << std::endl
      << " * subscriberVersion : " << version << std::endl
      << " */" << std::endl
      << "private class " << sink_classname << " extends JbiSink"
      << "{"
      << "public " << sink_classname << " ("
      << this->ctx_.impl_classname_ << " parent)" << std::endl
      << "  throws PermissionDeniedException, UnsupportedVersionException," << std::endl
      << "         InvalidPredicateException, PredicateLanguageException," << std::endl
      << "         PermissionDeniedException, SequenceStateException," << std::endl
      << "         UnrecognizedObjectTypeException, MappingException," << std::endl
      << "         IOException" << std::endl
      << "{"
      << "super (parent.getJbiConnection (), \""
      << type_name << "\", \""  << version << "\");";
  }
  else
  {
    anyevent = true;

    this->ctx_.source_
      << std::endl
      << "/**" << std::endl
      << " * subscriberName    : " << name << std::endl
      << " * subscriberType    : cuts.jbi.client.JbiAnyType" << std::endl
      << " */" << std::endl
      << "private class " << sink_classname << " extends JbiSink"
      << "{"
      << "public " << sink_classname << " ("
      << this->ctx_.impl_classname_ << " parent)" << std::endl
      << "  throws PermissionDeniedException, UnsupportedVersionException," << std::endl
      << "         InvalidPredicateException, PredicateLanguageException," << std::endl
      << "         PermissionDeniedException, SequenceStateException," << std::endl
      << "         UnrecognizedObjectTypeException, MappingException," << std::endl
      << "         IOException" << std::endl
      << "{"
      << "super (parent.getJbiConnection ());";
  }

  // Configure the port based on the provided properties.
  std::for_each (properties.begin (),
                 properties.end (),
                 boost::bind  (&CUTS_BE_InEventPort_Begin_T <CUTS_BE_Capi::Context>::configure,
                               this,
                               sink,
                               _1));

  // Register the callback with the sequence.
  this->ctx_.source_
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

  std::string event_type;

  if (!anyevent)
  {
    event_type = "JbiEvent <";

    std::string tag_name = ev.SpecifyIdTag ();
    tag_name[0] = ::toupper (tag_name[0]);

    event_type += tag_name + ">";
  }
  else
    event_type = "JbiAnyEvent";

  // Generate the start of the method's implementation.

  this->ctx_.source_
    << "void " << sink.name () << " (" << event_type << " ev)"
    << "{"
    << "try"
    << "{";
};

//
// CUTS_BE_InEventPort_Begin_T::configure
//
void CUTS_BE_InEventPort_Begin_T <CUTS_BE_Capi::Context>::
configure (const PICML::InEventPort & sink, const PICML::Property & prop)
{
  std::string propname = prop.name ();

  if (propname == "predicate")
  {
    PICML::Component parent = PICML::Component::Cast (sink.parent ());

    // Construct the name of the predicate.
    std::ostringstream predicate_name;
    predicate_name << "parent.getInstanceName () + \"."
                   << sink.name () << ".predicate";

    // Write the code to set the predicate.
    std::string predicate = prop.DataValue ();

    this->ctx_.source_
      << "this.setPredicate (" << predicate_name.str () << "\", "
      << prop.DataValue () << ");";
  }
  else
  {
    // We assume the property is an attribute of the sink.
    this->ctx_.source_ << "this.setAttribute ("
                              << "\"" << prop.name () << "\", "
                              << prop.DataValue () << ");";
  }
}

//
// CUTS_BE_InEventPort_End_T
//
void CUTS_BE_InEventPort_End_T <CUTS_BE_Capi::Context>::
generate (const PICML::InEventPort & sink,
          const std::vector <PICML::Property> & properties)
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
// CUTS_BE_Environment_Method_Begin_T
//
void CUTS_BE_Environment_Method_Begin_T <CUTS_BE_Capi::Context>::
generate (const PICML::MultiInputAction & action)
{
  std::string name = action.name ();

  CUTS_BE_Capi::Context::Env_Seen_Map::iterator iter =
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
    << "protected void jbi_" << name << " ()"
    << "{"
    << "try"
    << "{";

  this->ctx_.generate_required_method_impl (name);
}

//
// CUTS_BE_Environment_Method_Begin_T
//
void CUTS_BE_Environment_Method_End_T <CUTS_BE_Capi::Context>::
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
void CUTS_BE_Environment_End_T <CUTS_BE_Capi::Context>::
generate (const PICML::Component & component)
{
  CUTS_BE_Capi::Context::Env_Seen_Map::const_iterator
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
        << "protected void jbi_" << iter->first << " ()";
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
void CUTS_BE_PeriodicEvent_Begin_T <CUTS_BE_Capi::Context>::
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
void CUTS_BE_PeriodicEvent_End_T <CUTS_BE_Capi::Context>::
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
      << "  extends CUTS.PeriodicTaskHandler < " << parent_name << " > {"
      << "public " << periodic_task << " (CUTS.PeriodicTask < " << parent_name << " > task)"
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
      << "  implements CUTS.PeriodicTaskHandlerFactory < " << parent_name << " > {"
      << "public " << periodic_task << "Factory () { }"
      << "public TimerTask createTimerTask (CUTS.PeriodicTask < " << parent_name << " > task)"
      << "{"
      << "return new " << periodic_task << " (task);"
      << "}"
      << "}"
      << std::endl
      << "/**" << std::endl
      << " * PeriodicTask : " << periodic_name << std::endl
      << " */" << std::endl
      << "private CUTS.PeriodicTask <" << parent_name << "> "
      << periodic_name << "_ = " << std::endl
      << "  new CUTS.PeriodicTask <" << parent_name << " > (this, new " << periodic_task << "Factory ());";
  }
}

//
// CUTS_BE_ReadonlyAttribute_Begin_T
//
void CUTS_BE_ReadonlyAttribute_Begin_T <CUTS_BE_Capi::Context>::
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
void CUTS_BE_ReadonlyAttribute_End_T <CUTS_BE_Capi::Context>::
generate (const PICML::ReadonlyAttribute & readonly)
{
  this->ctx_.source_
    << "return this." << readonly.name () << "_;"
    << "}";
}

//
// CUTS_BE_Attribute_Begin_T
//
void CUTS_BE_Attribute_Begin_T <CUTS_BE_Capi::Context>::
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
void CUTS_BE_Attribute_End_T <CUTS_BE_Capi::Context>::
generate (const PICML::Attribute & attr)
{
  std::string name = attr.name ();

  this->ctx_.source_
    << "this." << name << "_ = " << name << ";"
    << "}";

  CUTS_BE_ReadonlyAttribute_Begin_T <CUTS_BE_Capi::Context> readonly_begin (this->ctx_);
  readonly_begin.generate (attr);

  CUTS_BE_ReadonlyAttribute_End_T <CUTS_BE_Capi::Context> readonly_end (this->ctx_);
  readonly_end.generate (attr);
}

//
// CUTS_BE_Finalize_T
//
void CUTS_BE_Finalize_T <CUTS_BE_Capi::Context>::
generate (const PICML::RootFolder & root)
{
  std::string outdir = CUTS_BE_OPTIONS ()->output_directory_;

  // We need to generate the XML mappings for all the ev types. This
  // is necessary so Castor can map the Java -> XML correctly. ;-)
  std::for_each (this->ctx_.workspace_events_.begin (),
                 this->ctx_.workspace_events_.end (),
                 boost::bind (&CUTS_BE_Finalize_T <CUTS_BE_Capi::Context>::generate_mapping_file,
                              this,
                              _1,
                              outdir));

  PICML::RootFolder rf (root);

  // Generate the script that sets the classpath.
  Set_Classpath_Script_Generator classpath (outdir);
  rf.Accept (classpath);

  // Generate the script that registers the MIO types.
  Register_Type_Script_Generator register_types (outdir);
  register_types.generate (this->ctx_.workspace_events_);
}

//
// generate_mapping_file
//
void CUTS_BE_Finalize_T <CUTS_BE_Capi::Context>::
generate_mapping_file (const PICML::Event & ev, const std::string & outdir)
{
  PICML::Event e (ev);

  // Generate the XML mapping file.
  XML_Mapping_File_Generator mapping (outdir);
  e.Accept (mapping);

  // Generate the XSD file.
  XSD_File_Generator xsd (outdir);
  e.Accept (xsd);

  CUTS_BE_CAPI_Event_Impl_Generator eventimpl (outdir);
  e.Accept (eventimpl);
}

//
// CUTS_BE_Postcondition_T
//
void CUTS_BE_Postcondition_T <CUTS_BE_Capi::Context>::
generate (const std::string & postcondition)
{
  this->ctx_.source_ << postcondition;
}

