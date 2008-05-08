#include "cutsnode.h"

namespace CUTS
{
  // taskDescription
  //

  taskDescription::
  taskDescription (::XSCRT::XML::Element< char > const& e)
  :Base (e), regulator__ ()
  {

    ::XSCRT::Parser< char > p (e);

    while (p.more_elements ())
    {
      ::XSCRT::XML::Element< char > e (p.next_element ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

      if (n == "executable")
      {
        executable_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
        executable_->container (this);
      }

      else if (n == "arguments")
      {
        ::XMLSchema::string< char > t (e);
        arguments (t);
      }

      else if (n == "workingdirectory")
      {
        ::XMLSchema::string< char > t (e);
        workingdirectory (t);
      }

      else 
      {
      }
    }

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "id")
      {
        id_ = ::std::auto_ptr< ::XMLSchema::ID< char > > (new ::XMLSchema::ID< char > (a));
        id_->container (this);
      }

      else 
      {
      }
    }
  }

  // taskList
  //

  taskList::
  taskList (::XSCRT::XML::Element< char > const& e)
  :Base (e), regulator__ ()
  {

    ::XSCRT::Parser< char > p (e);

    while (p.more_elements ())
    {
      ::XSCRT::XML::Element< char > e (p.next_element ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

      if (n == "task")
      {
        ::CUTS::taskDescription t (e);
        add_task (t);
      }

      else 
      {
      }
    }
  }

  // nodeConfig
  //

  nodeConfig::
  nodeConfig (::XSCRT::XML::Element< char > const& e)
  :Base (e), regulator__ ()
  {

    ::XSCRT::Parser< char > p (e);

    while (p.more_elements ())
    {
      ::XSCRT::XML::Element< char > e (p.next_element ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

      if (n == "tasklist")
      {
        ::CUTS::taskList t (e);
        tasklist (t);
      }

      else 
      {
      }
    }
  }
}

namespace CUTS
{
  namespace reader
  {
    ::CUTS::nodeConfig
    node (xercesc::DOMDocument const* d)
    {
      ::XSCRT::XML::Element< char > e (d->getDocumentElement ());
      if (e.name () == "node")
      {
        ::CUTS::nodeConfig r (e);
        return r;
      }

      else
      {
        throw 1;
      }
    }
  }
}

