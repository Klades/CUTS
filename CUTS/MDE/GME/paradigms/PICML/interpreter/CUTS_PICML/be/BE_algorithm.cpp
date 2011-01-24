// $Id$

#include "BE_algorithm.h"
#include "BE_IDL_Node.h"
#include "boost/bind.hpp"

namespace CUTS_BE
{
//
// get_file
//
PICML::File get_file (const PICML::NamedType & n)
{
  Udm::Object obj = n.GetParent ();

  while (obj.type () != PICML::File::meta)
    obj = obj.GetParent ();

  return PICML::File::Cast (obj);
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

  virtual void Visit_File (const PICML::File & file)
  {
    if (!this->result_)
      this->Visit_FilePackage_i (file);
  }

  virtual void Visit_Package (const PICML::Package & package)
  {
    if (!this->result_)
      this->Visit_FilePackage_i (package);
  }

protected:
  void Visit_FilePackage_i (const Udm::Object & obj)
  {
    std::set <PICML::Object> objects =
      Udm::ChildrenAttr <PICML::Object> (obj.__impl (), Udm::NULLCHILDROLE);

    if (!objects.empty ())
    {
      this->result_ = true;
      return;
    }

    // Visit the remaining packages.
    std::set <PICML::Package> packages =
      Udm::ChildrenAttr <PICML::Package> (obj.__impl (), Udm::NULLCHILDROLE);

    std::for_each (packages.begin (),
                   packages.end (),
                   boost::bind (&PICML::Package::Accept,
                                _1,
                                boost::ref (*this)));
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

  virtual void Visit_File (const PICML::File & file)
  {
    if (!this->result_)
      this->Visit_FilePackage_i (file);
  }

  virtual void Visit_Package (const PICML::Package & package)
  {
    if (!this->result_)
      this->Visit_FilePackage_i (package);
  }

protected:
  void Visit_FilePackage_i (const Udm::Object & obj)
  {
    std::set <PICML::Component> components =
      Udm::ChildrenAttr <PICML::Component> (obj.__impl (), Udm::NULLCHILDROLE);

    if (!components.empty ())
    {
      this->result_ = true;
      return;
    }

    // Visit the remaining packages.
    std::set <PICML::Package> packages =
      Udm::ChildrenAttr <PICML::Package> (obj.__impl (), Udm::NULLCHILDROLE);

    std::for_each (packages.begin (),
                   packages.end (),
                   boost::bind (&PICML::Package::Accept,
                                _1,
                                boost::ref (*this)));
  }

private:
  /// Result of the search.
  bool result_;
};

//
// has_component
//
bool has_component (const PICML::File & file)
{
  has_component_i search;
  PICML::File (file).Accept (search);

  return search.result ();
}

//
// has_component
//
bool has_interface (const PICML::File & file)
{
  has_interface_i search;
  PICML::File (file).Accept (search);

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

  virtual void Visit_File (const PICML::File & file)
  {
    if (!this->result_)
      this->Visit_FilePackage_i (file);
  }

  virtual void Visit_Package (const PICML::Package & package)
  {
    if (!this->result_)
      this->Visit_FilePackage_i (package);
  }

protected:
  void Visit_FilePackage_i (const Udm::Object & obj)
  {
    // Gather all the necessary elements.
    std::set <PICML::Event> events =
      Udm::ChildrenAttr <PICML::Event> (obj.__impl (), Udm::NULLCHILDROLE);

    if (!events.empty ())
    {
      this->result_ = true;
      return;
    }

    // Visit the remaining packages.
    std::set <PICML::Package> packages =
      Udm::ChildrenAttr <PICML::Package> (obj.__impl (), Udm::NULLCHILDROLE);

    std::for_each (packages.begin (),
                   packages.end (),
                   boost::bind (&PICML::Package::Accept,
                                _1,
                                boost::ref (*this)));
  }

private:
  /// Result of the search.
  bool result_;
};

//
// has_events
//
bool has_events (const PICML::File & file)
{
  has_events_i search;
  PICML::File (file).Accept (search);

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

  virtual void Visit_File (const PICML::File & file)
  {
    if (!this->result_)
      this->Visit_FilePackage_i (file);
  }

  virtual void Visit_Package (const PICML::Package & package)
  {
    if (!this->result_)
      this->Visit_FilePackage_i (package);
  }

  virtual void Visit_Aggregate (const PICML::Aggregate & aggr)
  {
    PICML::Key key = aggr.Key_child ();
    this->result_ |= (key != Udm::null);
  }

protected:
  void Visit_FilePackage_i (const Udm::Object & obj)
  {
    // Gather all the necessary elements.
    std::set <PICML::Aggregate> structs =
      Udm::ChildrenAttr <PICML::Aggregate> (obj.__impl (), Udm::NULLCHILDROLE);

    std::for_each (structs.begin (),
                   structs.end (),
                   boost::bind (&PICML::Aggregate::Accept,
                                _1,
                                boost::ref (*this)));

    // Visit the remaining packages.
    std::set <PICML::Package> packages =
      Udm::ChildrenAttr <PICML::Package> (obj.__impl (), Udm::NULLCHILDROLE);

    std::for_each (packages.begin (),
                   packages.end (),
                   boost::bind (&PICML::Package::Accept,
                                _1,
                                boost::ref (*this)));
  }

private:
  /// Result of the search.
  bool result_;
};

//
// has_dds_events
//
bool has_dds_events (const PICML::File & file)
{
  has_dds_events_i search;
  PICML::File (file).Accept (search);

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

  virtual void Visit_File (const PICML::File & file)
  {
    if (!this->result_)
      this->Visit_FilePackage_i (file);
  }

  virtual void Visit_Package (const PICML::Package & package)
  {
    if (!this->result_)
      this->Visit_FilePackage_i (package);
  }

protected:
  void Visit_FilePackage_i (const Udm::Object & obj)
  {
    // Gather all the necessary elements.
    std::set <PICML::Event> events =
      Udm::ChildrenAttr <PICML::Event> (obj.__impl (), Udm::NULLCHILDROLE);

    if (!events.empty ())
    {
      this->result_ = true;
      return;
    }

    std::set <PICML::Component> c =
      Udm::ChildrenAttr <PICML::Component> (obj.__impl (), Udm::NULLCHILDROLE);

    if (!c.empty ())
    {
      this->result_ = true;
      return;
    }

    std::set <PICML::Object> o =
      Udm::ChildrenAttr <PICML::Object> (obj.__impl (), Udm::NULLCHILDROLE);

    if (!o.empty ())
    {
      this->result_ = true;
      return;
    }

    // Visit the remaining packages.
    std::set <PICML::Package> packages =
      Udm::ChildrenAttr <PICML::Package> (obj.__impl (), Udm::NULLCHILDROLE);

    std::for_each (packages.begin (),
                   packages.end (),
                   boost::bind (&PICML::Package::Accept,
                                _1,
                                boost::ref (*this)));
  }

private:
  /// Result of the search.
  bool result_;
};

//
// requires_executor
//
bool requires_executor (const PICML::File & file)
{
  requires_executor_i search;
  PICML::File (file).Accept (search);

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
std::string get_pathname (const PICML::File & file,
                          const std::string & separator,
                          const std::string & prefix,
                          const std::string & suffix)
{
  // Make sure we add the path to the pathname.
  std::string pathname = file.Path ();

  if (!pathname.empty ())
    pathname += "/";

  // Construct the remaining part of the pathname.
  pathname += prefix + std::string (file.name ()) + suffix;

  return pathname;
}

}
