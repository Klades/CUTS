#include "cutsnode.h"

namespace CUTS
{
  namespace schemas
  {
    // ProcessOptions
    //

    ProcessOptions::
    ProcessOptions (::XSCRT::XML::Element< char > const& e)
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

      while (p.more_attributes ())
      {
        ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
        if (n ==  ("id"))
        {
          id_ = ::std::auto_ptr< ::XMLSchema::ID< char > > (new ::XMLSchema::ID< char > (a));
          id_->container (this);
          std::basic_string<ACE_TCHAR> temp (ACE_TEXT_CHAR_TO_TCHAR ((*id_).c_str()));
          (*ACE_Singleton<ID_Map::TSS_ID_Map, ACE_Null_Mutex>::instance())->
          add_id(temp, dynamic_cast<XSCRT::Type*> (this));
        }

        else if (n ==  ("delay"))
        {
          ::XMLSchema::double_ t (a);
          delay (t);
        }

        else if (n ==  ("waitforcompletion"))
        {
          ::XMLSchema::boolean t (a);
          waitforcompletion (t);
        }

        else 
        {
        }
      }
    }

    // ProcessList
    //

    ProcessList::
    ProcessList (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == "process")
        {
          ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::ProcessOptions, ACE_Null_Mutex >  t (new ::CUTS::schemas::ProcessOptions (e));
          add_process (t);
        }

        else 
        {
        }
      }
    }

    // NodeConfig
    //

    NodeConfig::
    NodeConfig (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == "environment")
        {
          ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::EnvConfig, ACE_Null_Mutex >  t (new ::CUTS::schemas::EnvConfig (e));
          add_environment (t);
        }

        else 
        {
        }
      }
    }

    // DependsItem
    //

    DependsItem::
    DependsItem (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_attributes ())
      {
        ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
        if (n ==  ("id"))
        {
          id_ = ::std::auto_ptr< ::XMLSchema::IDREF< char > > (new ::XMLSchema::IDREF< char > (a));
          id_->container (this);
          std::basic_string<ACE_TCHAR> temp (ACE_TEXT_CHAR_TO_TCHAR ((*id_).id().c_str()));

          (*ACE_Singleton<ID_Map::TSS_ID_Map, ACE_Null_Mutex>::instance())->
          add_idref(temp, dynamic_cast<XSCRT::Type*> (this));
        }

        else 
        {
        }
      }
    }

    // EnvConfig
    //

    EnvConfig::
    EnvConfig (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == "variables")
        {
          ::CUTS::schemas::VariableList t (e);
          variables (t);
        }

        else if (n == "startup")
        {
          ::CUTS::schemas::ProcessList t (e);
          startup (t);
        }

        else if (n == "shutdown")
        {
          ::CUTS::schemas::ProcessList t (e);
          shutdown (t);
        }

        else 
        {
        }
      }

      while (p.more_attributes ())
      {
        ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
        if (n ==  ("id"))
        {
          id_ = ::std::auto_ptr< ::XMLSchema::ID< char > > (new ::XMLSchema::ID< char > (a));
          id_->container (this);
          std::basic_string<ACE_TCHAR> temp (ACE_TEXT_CHAR_TO_TCHAR ((*id_).c_str()));
          (*ACE_Singleton<ID_Map::TSS_ID_Map, ACE_Null_Mutex>::instance())->
          add_id(temp, dynamic_cast<XSCRT::Type*> (this));
        }

        else if (n ==  ("inherit"))
        {
          ::XMLSchema::boolean t (a);
          inherit (t);
        }

        else if (n ==  ("active"))
        {
          ::XMLSchema::boolean t (a);
          active (t);
        }

        else 
        {
        }
      }
    }

    // Variable
    //

    Variable::
    Variable (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_attributes ())
      {
        ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
        if (n ==  ("name"))
        {
          name_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (a));
          name_->container (this);
        }

        else if (n ==  ("value"))
        {
          value_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (a));
          value_->container (this);
        }

        else 
        {
        }
      }
    }

    // VariableList
    //

    VariableList::
    VariableList (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == "import")
        {
          ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::VariableImport, ACE_Null_Mutex >  t (new ::CUTS::schemas::VariableImport (e));
          add_import (t);
        }

        else if (n == "variable")
        {
          ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::Variable, ACE_Null_Mutex >  t (new ::CUTS::schemas::Variable (e));
          add_variable (t);
        }

        else 
        {
        }
      }
    }

    // VariableImport
    //

    VariableImport::
    VariableImport (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_attributes ())
      {
        ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
        if (n ==  ("location"))
        {
          location_ = ::std::auto_ptr< ::XMLSchema::anyURI< char > > (new ::XMLSchema::anyURI< char > (a));
          location_->container (this);
        }

        else if (n ==  ("type"))
        {
          type_ = ::std::auto_ptr< ::CUTS::schemas::FileType > (new ::CUTS::schemas::FileType (a));
          type_->container (this);
        }

        else 
        {
        }
      }
    }

    // FileType
    //

    FileType::
    FileType (::XSCRT::XML::Element< char > const& e)
    : ::XSCRT::Type (e)
    {
      ::std::basic_string< char > v (e.value ());

      if (v ==  ("text")) v_ = text_l;
      else if (v ==  ("xml")) v_ = xml_l;
      else 
      {
      }
    }

    FileType::
    FileType (::XSCRT::XML::Attribute< char > const& a)
    : ::XSCRT::Type (a)
    {
      ::std::basic_string< char > v (a.value ());

      if (v ==  ("text")) v_ = text_l;
      else if (v ==  ("xml")) v_ = xml_l;
      else 
      {
      }
    }

    FileType const FileType::text (FileType::text_l);
    FileType const FileType::xml (FileType::xml_l);
  }
}

namespace CUTS
{
  namespace schemas
  {
    namespace reader
    {
      ::CUTS::schemas::NodeConfig
      node (xercesc::DOMDocument const* d)
      {
        //Initiate our Singleton as an ACE_TSS object (ensures thread
        //specific storage
        ID_Map::TSS_ID_Map* TSS_ID_Map (ACE_Singleton<ID_Map::TSS_ID_Map, ACE_Null_Mutex>::instance());


        ::XSCRT::XML::Element< char > e (d->getDocumentElement ());
        if (e.name () == ACE_TEXT("node"))
        {
          ::CUTS::schemas::NodeConfig r (e);

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
}

