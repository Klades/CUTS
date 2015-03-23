// $Id$

#include "BE_algorithm.h"
#include "BE_IDL_Node.h"
#include "boost/bind.hpp"

#include "PICML/PICML.h"
#include "PICML/Visitor.h"

namespace CUTS_BE
{
//
// get_file
//
PICML::File get_file (const PICML::NamedType_in n)
{
  GAME::Mga::Object obj;

  while (obj->meta ()->name () != PICML::File::impl_type::metaname)
    obj = obj->parent ();

  return obj;
}

/**
 * Implementation of the has_component function.
 */
class has_interface_i : public PICML::Visitor
{
public:
  has_interface_i (void)
    : result_ (false)
  {

  }

  bool result (void) const
  {
    return this->result_;
  }

  virtual void visit_File (PICML::File_in file)
  {
    if (this->result_)
      return;

    if (file->get_Objects ().count ())
      this->result_ = true;
    else
    {
      for (auto package : file->get_Packages ())
        package->accept (this);
    }      
  }

  virtual void visit_Package (PICML::Package_in package)
  {
    if (this->result_)
      return;

    if (package->get_Objects ().count ())
      this->result_ = true;

    for (auto subpackage : package->get_Packages ())
      subpackage->accept (this);
  }

private:
  /// Result of the search.
  bool result_;
};

/**
 * Implementation of the has_component function.
 */
class has_component_i : public PICML::Visitor
{
public:
  has_component_i (void)
    : result_ (false)
  {

  }

  bool result (void) const
  {
    return this->result_;
  }

  virtual void visit_File (PICML::File_in file)
  {
    if (this->result_)
      return;

    if (file->get_Components ().count ())
      this->result_ = true;
    else
    {
      for (auto package : file->get_Packages ())
        package->accept (this);
    }      
  }

  virtual void visit_Package (PICML::Package_in package)
  {
    if (this->result_)
      return;

    if (package->get_Components ().count ())
      this->result_ = true;

    for (auto subpackage : package->get_Packages ())
      subpackage->accept (this);
  }

private:
  /// Result of the search.
  bool result_;
};

//
// has_component
//
bool has_component (const PICML::File_in file)
{
  has_component_i search;
  file->accept (&search);

  return search.result ();
}

//
// has_component
//
bool has_interface (const PICML::File_in file)
{
  has_interface_i search;
  file->accept (&search);

  return search.result ();
}

//
// has_interface
//
bool has_interface (const CUTS_BE_IDL_Node * node)
{
  return has_interface (node->file_);
}

///////////////////////////////////////////////////////////////////////////////
// has_events

/**
 * Implementation of the has_events function.
 */
class has_events_i : public PICML::Visitor
{
public:
  has_events_i (void)
    : result_ (false)
  {

  }

  bool result (void) const
  {
    return this->result_;
  }

  virtual void visit_File (PICML::File_in file)
  {
    if (this->result_)
      return;

    if (file->get_Events ().count ())
      this->result_ = true;
    else
    {
      for (auto package : file->get_Packages ())
        package->accept (this);
    }      
  }

  virtual void visit_Package (PICML::Package_in package)
  {
    if (this->result_)
      return;

    if (package->get_Events ().count ())
      this->result_ = true;

    for (auto subpackage : package->get_Packages ())
      subpackage->accept (this);
  }

private:
  /// Result of the search.
  bool result_;
};

//
// has_events
//
bool has_events (const PICML::File_in file)
{
  has_events_i search;
  file->accept (&search);

  return search.result ();
}

///////////////////////////////////////////////////////////////////////////////
// has_dds_events

/**
 * Implementation of the has_events function.
 */
class has_dds_events_i : public PICML::Visitor
{
public:
  has_dds_events_i (void)
    : result_ (false)
  {

  }

  bool result (void) const
  {
    return this->result_;
  }

  virtual void visit_File (PICML::File_in file)
  {
    if (this->result_)
      return;

    for (auto aggregate : file->get_Aggregates ())
      aggregate->accept (this);

    for (auto package : file->get_Packages ())
      package->accept (this);
  }

  virtual void visit_Package (PICML::Package_in package)
  {
    if (this->result_)
      return;

    for (auto aggregate : package->get_Aggregates ())
      aggregate->accept (this);

    for (auto package : package->get_Packages ())
      package->accept (this);
  }

  virtual void visit_Aggregate ( PICML::Aggregate_in aggr)
  {
    if (aggr->has_Key ())
      this->result_ = true;
  }

private:
  /// Result of the search.
  bool result_;
};

//
// has_dds_events
//
bool has_dds_events (const PICML::File_in file)
{
  has_dds_events_i search;
  file->accept (&search);

  return search.result ();
}

///////////////////////////////////////////////////////////////////////////////
// requires_executor

/**
 * Implementation of the has_events function.
 */
class requires_executor_i : public PICML::Visitor
{
public:
  requires_executor_i (void)
    : result_ (false)
  {

  }

  bool result (void) const
  {
    return this->result_;
  }

  virtual void visit_File (PICML::File & file)
  {
    if (this->result_)
      return;

    if (file->get_Events ().count ())
      this->result_ = true;

    if (file->get_Components ().count ())
      this->result_ = true;

    if (file->get_Objects ().count ())
      this->result_ = true;

    for (auto package : file->get_Packages ())
      package->accept (this);
  }

  virtual void visit_Package (PICML::Package_in package)
  {
    if (this->result_)
      return;

    if (package->get_Events ().count ())
      this->result_ = true;

    if (package->get_Components ().count ())
      this->result_ = true;

    if (package->get_Objects ().count ())
      this->result_ = true;

    for (auto subpackage : package->get_Packages ())
      subpackage->accept (this);
  }

private:
  /// Result of the search.
  bool result_;
};

//
// requires_executor
//
bool requires_executor (const PICML::File_in file)
{
  requires_executor_i search;
  file->accept (&search);

  return search.result ();
}

//
// has_interface
//
bool requires_executor (const CUTS_BE_IDL_Node * node)
{
  return requires_executor (node->file_);
}

//
// get_pathname
//
std::string get_pathname (const PICML::File_in file,
                          const std::string & separator,
                          const std::string & prefix,
                          const std::string & suffix)
{
  // Make sure we add the path to the pathname.
  std::string pathname = file->Path ();

  if (!pathname.empty ())
    pathname += "/";

  // Construct the remaining part of the pathname.
  pathname += prefix + std::string (file->name ()) + suffix;

  return pathname;
}

}
