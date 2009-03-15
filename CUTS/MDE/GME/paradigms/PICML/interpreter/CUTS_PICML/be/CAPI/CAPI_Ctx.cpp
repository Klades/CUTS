// $Id$

#include "CAPI_Ctx.h"

//
// predefined_type_map_
//
CUTS_BE_Capi::PredefinedType_Map CUTS_BE_Capi::predefined_type_map_;

//
// CUTS_BE_Capi
//
CUTS_BE_Capi::CUTS_BE_Capi (void)
{
  this->env_seen_.insert (std::make_pair ("init", false));
  this->env_seen_.insert (std::make_pair ("activate", false));
  this->env_seen_.insert (std::make_pair ("deactivate", false));
  this->env_seen_.insert (std::make_pair ("fini", false));

  // Initialize the predefined map for the CAPI context.
  if (CUTS_BE_Capi::predefined_type_map_.empty ())
  {
    CUTS_BE_Capi::predefined_type_map_.insert (
      std::make_pair (PICML::String::meta, "java.lang.String"));

    CUTS_BE_Capi::predefined_type_map_.insert (
      std::make_pair (PICML::LongInteger::meta, "long"));

    CUTS_BE_Capi::predefined_type_map_.insert (
      std::make_pair (PICML::ShortInteger::meta, "short"));

    CUTS_BE_Capi::predefined_type_map_.insert (
      std::make_pair (PICML::Byte::meta, "byte"));

    CUTS_BE_Capi::predefined_type_map_.insert (
      std::make_pair (PICML::Boolean::meta, "boolean"));

    CUTS_BE_Capi::predefined_type_map_.insert (
      std::make_pair (PICML::RealNumber::meta, "double"));

    CUTS_BE_Capi::predefined_type_map_.insert (
      std::make_pair (PICML::GenericObject::meta, "Object"));
  }
}

//
// setter_method
//
std::string CUTS_BE_Capi::
setter_method (const std::string & name)
{
  std::string temp (name);
  temp[0] = ::toupper (temp[0]);

  std::string setter ("set");
  setter.append (temp);

  return setter;
}

//
// getter_method
//
std::string CUTS_BE_Capi::
getter_method (const std::string & name)
{
  std::string temp (name);
  temp[0] = ::toupper (temp[0]);

  std::string getter ("get");
  getter.append (temp);

  return getter;
}

//
// fq_name
//
std::string CUTS_BE_Capi::
fq_name (const PICML::NamedType & type, char separator)
{
  std::string scope = CUTS_BE_Capi::scope (type, separator);
  scope += separator + std::string (type.name ());

  return scope;
}

//
// classname
//
std::string CUTS_BE_Capi::classname (const std::string & str)
{
  std::string name = str;
  name[0] = ::toupper (name[0]);

  return name;
}

//
// generate_accessor_methods
//
void CUTS_BE_Capi::
generate_accessor_methods (std::string type, std::string varname)
{
  std::string tmp_varname (varname);
  tmp_varname[0] = ::toupper (tmp_varname[0]);

  CUTS_BE_CAPI ()->outfile_
    << std::endl
    << "public " << type << " get" << tmp_varname << " ()"
    << "{"
    << "return this." << varname << "_;"
    << "}"
    << std::endl
    << "public void set" << tmp_varname
    << " (" << type << " " << varname << ")"
    << "{"
    << "this." << varname << "_ = " << varname << ";"
    << "}";
}

//
// scope
//
std::string CUTS_BE_Capi::
scope (const PICML::NamedType & type, char separator)
{
  std::stack <std::string> scope;
  ::PICML::MgaObject parent = type.parent ();

  // Move up the tree until we reach a File (i.e., while we
  // are still working with Package elements).
  while (parent.type () == ::PICML::Package::meta)
  {
    scope.push (parent.name ());
    parent = ::PICML::MgaObject::Cast (parent.parent ());
  }

  std::ostringstream ostr;

  // Convert the stack into a scope. This is done by popping the stack
  // one element at a time and appending it and the separator to the
  // stream.
  if (!scope.empty ())
  {
    // Write the top value since the remaining items in the scope
    // will have the separator prepended.
    ostr << scope.top ();
    scope.pop ();

    // Construct the remainder of the name.
    while (!scope.empty ())
    {
      ostr << separator << scope.top ();
      scope.pop ();
    }
  }

  return ostr.str ();
}

//
// reset
//
void CUTS_BE_Capi::reset (void)
{
  // Reset the environment flags.
  CUTS_BE_Capi::Env_Seen_Map::iterator
    iter = this->env_seen_.begin (), iter_end = this->env_seen_.end ();

  for ( ; iter != iter_end; iter ++)
    iter->second = false;

  // Reset the event ports.
  this->sinks_.clear ();
  this->sources_.clear ();

  // Reset the periodic event collection.
  this->periodics_.clear ();
}

//
// generate_required_method_impl
//
void CUTS_BE_Capi::
generate_required_method_impl (const std::string & method)
{
  if (method == "init")
  {
    CUTS_BE_Capi::Event_Port_Map::const_iterator
      iter = this->sources_.begin (), iter_end = this->sources_.end ();

    for ( ; iter != iter_end; ++ iter)
    {
      this->outfile_
        << "// creation of source: " << iter->first << std::endl
        << "this." << iter->first << "_ = new "
        << iter->first << "Source (this);"
        << "this.registerInfoSequence (this." << iter->first << "_);"
        << std::endl;
    }

    iter = this->sinks_.begin ();
    iter_end = this->sinks_.end ();

    for ( ; iter != iter_end; ++ iter)
    {
      this->outfile_
        << "// creation of sink: " << iter->first << std::endl
        << "this." << iter->first << "_ = new "
        << iter->first << "Sink (this);"
        << "this.registerInfoSequence (this." << iter->first << "_);"
        << std::endl;
    }
  }
  else if (method == "activate")
  {
    CUTS_BE_Capi::Periodic_Map::const_iterator
      iter = this->periodics_.begin (), iter_end = this->periodics_.end ();
    std::string name;

    for ( ; iter != iter_end; ++ iter)
    {
      name = iter->second.name ();

      this->outfile_  << "this." << name << "_.setHertz ("
                      << iter->second.Hertz () << ");"
                      << "this." << name << "_.scheduleNextTimeout ();";
    }
  }
  else if (method == "deactivate")
  {
    CUTS_BE_Capi::Periodic_Map::const_iterator
      iter = this->periodics_.begin (), iter_end = this->periodics_.end ();

    for ( ; iter != iter_end; ++ iter)
      this->outfile_ << "this." << iter->first << "_.cancel ();";
  }
}

//
// generate_throws_signature
//
void CUTS_BE_Capi::generate_throws_signature (const std::string & method)
{

}

//
// import
//
std::string CUTS_BE_Capi::import (const PICML::Worker & worker)
{
  // Initialize the import scope.
  std::stack <std::string> scope;
  scope.push (worker.name ());

  // Move up the tree until we reach a File (i.e., while we
  // are still working with Package elements).
  PICML::MgaObject parent = worker.parent ();

  while (parent.type () != PICML::WorkerFile::meta)
  {
    scope.push (parent.name ());
    parent = ::PICML::MgaObject::Cast (parent.parent ());
  }

  std::ostringstream ostr;

  // Write the top value since the remaining items in the scope
  // will have the '.' prepended.
  ostr << scope.top ();
  scope.pop ();

  // Construct the remainder of the name.
  while (!scope.empty ())
  {
    ostr << '.' << scope.top ();
    scope.pop ();
  }

  return ostr.str ();
}
