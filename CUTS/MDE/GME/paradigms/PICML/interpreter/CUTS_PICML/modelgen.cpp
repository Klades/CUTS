#include "modelgen.h"

namespace CUTS
{
  // Generator_Description
  //

  Generator_Description::
  Generator_Description (::XSCRT::XML::Element< char > const& e)
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

  // Configuration
  //

  Configuration::
  Configuration (::XSCRT::XML::Element< char > const& e)
  :Base (e), regulator__ ()
  {

    ::XSCRT::Parser< char > p (e);

    while (p.more_elements ())
    {
      ::XSCRT::XML::Element< char > e (p.next_element ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

      if (n == ACE_TEXT("backend"))
      {
        ::CUTS::Generators t (e);
        backend (t);
      }

      else 
      {
      }
    }
  }

  // Generators
  //

  Generators::
  Generators (::XSCRT::XML::Element< char > const& e)
  :Base (e), regulator__ ()
  {

    ::XSCRT::Parser< char > p (e);

    while (p.more_elements ())
    {
      ::XSCRT::XML::Element< char > e (p.next_element ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

      if (n == ACE_TEXT("generator"))
      {
        ACE_Refcounted_Auto_Ptr < ::CUTS::Generator_Description, ACE_Null_Mutex >  t (new ::CUTS::Generator_Description (e));
        add_generator (t);
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
    ::CUTS::Configuration
    modelgen (xercesc::DOMDocument const* d)
    {
      //Initiate our Singleton as an ACE_TSS object (ensures thread
      //specific storage
      ID_Map::TSS_ID_Map* TSS_ID_Map (ACE_Singleton<ID_Map::TSS_ID_Map, ACE_Null_Mutex>::instance());


      ::XSCRT::XML::Element< char > e (d->getDocumentElement ());
      if (e.name () == ACE_TEXT("modelgen"))
      {
        ::CUTS::Configuration r (e);

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

#include "XMLSchema/TypeInfo.hpp"

namespace CUTS
{
  namespace
  {
    ::XMLSchema::TypeInfoInitializer < char > XMLSchemaTypeInfoInitializer_ (::XSCRT::extended_type_info_map ());

    struct Generator_DescriptionTypeInfoInitializer
    {
      Generator_DescriptionTypeInfoInitializer ()
      {
        ::XSCRT::TypeId id (typeid (::CUTS::Generator_Description));
        ::XSCRT::ExtendedTypeInfo nf (id);

        nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
        ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
      }
    };

    Generator_DescriptionTypeInfoInitializer Generator_DescriptionTypeInfoInitializer_;

    struct ConfigurationTypeInfoInitializer
    {
      ConfigurationTypeInfoInitializer ()
      {
        ::XSCRT::TypeId id (typeid (::CUTS::Configuration));
        ::XSCRT::ExtendedTypeInfo nf (id);

        nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
        ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
      }
    };

    ConfigurationTypeInfoInitializer ConfigurationTypeInfoInitializer_;

    struct GeneratorsTypeInfoInitializer
    {
      GeneratorsTypeInfoInitializer ()
      {
        ::XSCRT::TypeId id (typeid (::CUTS::Generators));
        ::XSCRT::ExtendedTypeInfo nf (id);

        nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
        ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
      }
    };

    GeneratorsTypeInfoInitializer GeneratorsTypeInfoInitializer_;
  }
}

