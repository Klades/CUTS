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

      if (n == "location")
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

      if (n == "backend")
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

      if (n == "generator")
      {
        ::CUTS::Generator_Description t (e);
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
      ::XSCRT::XML::Element< char > e (d->getDocumentElement ());
      if (e.name () == "modelgen")
      {
        ::CUTS::Configuration r (e);
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

