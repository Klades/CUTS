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

      if (n == ACE_TEXT("location"))
      {
        location_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
        location_->container (this);
      }

      else if (n == ACE_TEXT("entryPoint"))
      {
        entryPoint_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
        entryPoint_->container (this);
      }

      else if (n == ACE_TEXT("params"))
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
        std::basic_string<ACE_TCHAR> temp (ACE_TEXT_CHAR_TO_TCHAR ((*id_).c_str()));
        (*ACE_Singleton<ID_Map::TSS_ID_Map, ACE_Null_Mutex>::instance())->
        add_id(temp, dynamic_cast<XSCRT::Type*> (this));
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

      if (n == ACE_TEXT("service"))
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

      if (n == ACE_TEXT("startup"))
      {
        ::CUTS::processOptions t (e);
        startup (t);
      }

      else if (n == ACE_TEXT("shutdown"))
      {
        ::CUTS::processOptions t (e);
        shutdown (t);
      }

      else if (n == ACE_TEXT("services"))
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

      if (n == ACE_TEXT("executable"))
      {
        executable_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
        executable_->container (this);
      }

      else if (n == ACE_TEXT("arguments"))
      {
        ::XMLSchema::string< char > t (e);
        arguments (t);
      }

      else if (n == ACE_TEXT("workingdirectory"))
      {
        ::XMLSchema::string< char > t (e);
        workingdirectory (t);
      }

      else if (n == ACE_TEXT("output"))
      {
        ::XMLSchema::string< char > t (e);
        output (t);
      }

      else if (n == ACE_TEXT("error"))
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
      //Initiate our Singleton as an ACE_TSS object (ensures thread
      //specific storage
      ID_Map::TSS_ID_Map* TSS_ID_Map (ACE_Singleton<ID_Map::TSS_ID_Map, ACE_Null_Mutex>::instance());


      ::XSCRT::XML::Element< char > e (d->getDocumentElement ());
      if (e.name () == ACE_TEXT("test"))
      {
        ::CUTS::testFile r (e);

        (*TSS_ID_Map)->resolve_idref();

        return r;
      }

      else
      {
        throw 1;
      }
    }
  }
}

