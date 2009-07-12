#include "test.h"

namespace CUTS
{
  // serviceDescription
  //

  serviceDescription::
  serviceDescription (::XSCRT::XML::Element< char > const& e)
  :Base (e), regulator__ ()
  {

    ::XSCRT::Parser< char > p (e);

    while (p.more_elements ())
    {
      ::XSCRT::XML::Element< char > e (p.next_element ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

      if (n == "location")
      {
        location_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
        location_->container (this);
      }

      else if (n == "entryPoint")
      {
        entryPoint_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
        entryPoint_->container (this);
      }

      else if (n == "params")
      {
        ::XMLSchema::string< char > t (e);
        params (t);
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

  // serviceList
  //

  serviceList::
  serviceList (::XSCRT::XML::Element< char > const& e)
  :Base (e), regulator__ ()
  {

    ::XSCRT::Parser< char > p (e);

    while (p.more_elements ())
    {
      ::XSCRT::XML::Element< char > e (p.next_element ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

      if (n == "service")
      {
        ACE_Refcounted_Auto_Ptr < ::CUTS::serviceDescription, ACE_Null_Mutex >  t (new ::CUTS::serviceDescription (e));
        add_service (t);
      }

      else 
      {
      }
    }
  }

  // testFile
  //

  testFile::
  testFile (::XSCRT::XML::Element< char > const& e)
  :Base (e), regulator__ ()
  {

    ::XSCRT::Parser< char > p (e);

    while (p.more_elements ())
    {
      ::XSCRT::XML::Element< char > e (p.next_element ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

      if (n == "startup")
      {
        ::CUTS::processOptions t (e);
        startup (t);
      }

      else if (n == "shutdown")
      {
        ::CUTS::processOptions t (e);
        shutdown (t);
      }

      else if (n == "services")
      {
        ::CUTS::serviceList t (e);
        services (t);
      }

      else 
      {
      }
    }
  }

  // processOptions
  //

  processOptions::
  processOptions (::XSCRT::XML::Element< char > const& e)
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

      else if (n == "output")
      {
        ::XMLSchema::string< char > t (e);
        output (t);
      }

      else if (n == "error")
      {
        ::XMLSchema::string< char > t (e);
        error (t);
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
    ::CUTS::testFile
    test (xercesc::DOMDocument const* d)
    {
      ::XSCRT::XML::Element< char > e (d->getDocumentElement ());
      if (e.name () == "test")
      {
        ::CUTS::testFile r (e);
        return r;
      }

      else
      {
        throw 1;
      }
    }
  }
}

