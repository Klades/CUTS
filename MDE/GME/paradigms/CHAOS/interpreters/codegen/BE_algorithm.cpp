// $Id$

#include "StdAfx.h"
#include "BE_algorithm.h"
#include "boost/bind.hpp"

namespace CUTS_BE
{

/**
 * Implementation of the has_component function.
 */
class has_component_i : public CHAOS::Visitor
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

  virtual void Visit_File (const CHAOS::File & file)
  {
    if (!this->result_)
      this->Visit_FilePackage_i (file);
  }

  virtual void Visit_Package (const CHAOS::Package & package)
  {
    if (!this->result_)
      this->Visit_FilePackage_i (package);
  }

protected:
  void Visit_FilePackage_i (const Udm::Object & obj)
  {
    //// Gather all the necessary elements.
    //std::set <CHAOS::Event> events =
    //  Udm::ChildrenAttr <CHAOS::Event> (obj.__impl (), Udm::NULLCHILDROLE);

    //if (!events.empty ())
    //{
    //  this->result_ = true;
    //  return;
    //}

    std::set <CHAOS::Component> components =
      Udm::ChildrenAttr <CHAOS::Component> (obj.__impl (), Udm::NULLCHILDROLE);

    if (!components.empty ())
    {
      this->result_ = true;
      return;
    }

    // Visit the remaining packages.
    std::set <CHAOS::Package> packages =
      Udm::ChildrenAttr <CHAOS::Package> (obj.__impl (), Udm::NULLCHILDROLE);

    for (auto package : packages)
      package.Accept (*this);
  }

private:
  /// Result of the search.
  bool result_;
};

//
// has_component
//
bool has_component (const CHAOS::File & file)
{
  has_component_i search;
  CHAOS::File (file).Accept (search);

  return search.result ();
}

/**
 * Implementation of the has_events function.
 */
class has_events_i : public CHAOS::Visitor
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

  virtual void Visit_File (const CHAOS::File & file)
  {
    if (!this->result_)
      this->Visit_FilePackage_i (file);
  }

  virtual void Visit_Package (const CHAOS::Package & package)
  {
    if (!this->result_)
      this->Visit_FilePackage_i (package);
  }

protected:
  void Visit_FilePackage_i (const Udm::Object & obj)
  {
    // Gather all the necessary elements.
    std::set <CHAOS::Event> events =
      Udm::ChildrenAttr <CHAOS::Event> (obj.__impl (), Udm::NULLCHILDROLE);

    if (!events.empty ())
    {
      this->result_ = true;
      return;
    }

    // Visit the remaining packages.
    std::set <CHAOS::Package> packages =
      Udm::ChildrenAttr <CHAOS::Package> (obj.__impl (), Udm::NULLCHILDROLE);

    for (auto package : packages)
      package.Accept (*this);
  }

private:
  /// Result of the search.
  bool result_;
};

//
// has_events
//
bool has_events (const CHAOS::File & file)
{
  has_events_i search;
  CHAOS::File (file).Accept (search);

  return search.result ();
}

}
