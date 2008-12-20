#include "attribute.h"

namespace naomi
{
  namespace attributes
  {
    // attributeType::resourceType
    //

    attributeType::resourceType::
    resourceType (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_attributes ())
      {
        ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
        if (n == "name")
        {
          name_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (a));
          name_->container (this);
        }

        else if (n == "uri")
        {
          uri_ = ::std::auto_ptr< ::XMLSchema::anyURI< char > > (new ::XMLSchema::anyURI< char > (a));
          uri_->container (this);
        }

        else if (n == "checksum")
        {
          ::XMLSchema::string< char > t (a);
          checksum (t);
        }

        else
        {
        }
      }
    }

    // attributeType
    //

    attributeType::
    attributeType (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == "owner")
        {
          owner_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
          owner_->container (this);
        }

        else if (n == "value")
        {
          value_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
          value_->container (this);
        }

        else if (n == "resource")
        {
          resourceType t (e);
          add_resource (t);
        }

        else if (n == "units")
        {
          ::XMLSchema::string< char > t (e);
          units (t);
        }

        else if (n == "documentation")
        {
          ::XMLSchema::string< char > t (e);
          documentation (t);
        }

        else
        {
        }
      }
    }
  }
}

namespace naomi
{
  namespace attributes
  {
    namespace reader
    {
      attributeType
      attribute (xercesc::DOMDocument const* d)
      {
        ::XSCRT::XML::Element< char > e (d->getDocumentElement ());
        if (e.name () == "attribute")
        {
          attributeType r (e);
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

#include "XMLSchema/TypeInfo.hpp"

namespace naomi
{
  namespace attributes
  {
    namespace
    {
      ::XMLSchema::TypeInfoInitializer < char > XMLSchemaTypeInfoInitializer_ (::XSCRT::extended_type_info_map ());

      // anonymous type for attributeType
      //
      struct attributeTypeTypeInfoInitializer
      {
        attributeTypeTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::naomi::attributes::attributeType));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }

        // anonymous type for resourceType
        //
        public:
        struct resourceTypeTypeInfoInitializer
        {
          resourceTypeTypeInfoInitializer ()
          {
            ::XSCRT::TypeId id (typeid (::naomi::attributes::attributeType::resourceType));
            ::XSCRT::ExtendedTypeInfo nf (id);

            nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
            ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
          }
        };

        resourceTypeTypeInfoInitializer resourceTypeTypeInfoInitializer_;
      };

      attributeTypeTypeInfoInitializer attributeTypeTypeInfoInitializer_;
    }
  }
}

namespace naomi
{
  namespace attributes
  {
    namespace Traversal
    {
      // attributeType::resourceType
      //
      //

      void attributeType::resourceType::
      traverse (Type& o)
      {
        pre (o);
        name (o);
        uri (o);
        if (o.checksum_p ()) checksum (o);
        else checksum_none (o);
        post (o);
      }

      void attributeType::resourceType::
      traverse (Type const& o)
      {
        pre (o);
        name (o);
        uri (o);
        if (o.checksum_p ()) checksum (o);
        else checksum_none (o);
        post (o);
      }

      void attributeType::resourceType::
      pre (Type&)
      {
      }

      void attributeType::resourceType::
      pre (Type const&)
      {
      }

      void attributeType::resourceType::
      name (Type& o)
      {
        dispatch (o.name ());
      }

      void attributeType::resourceType::
      name (Type const& o)
      {
        dispatch (o.name ());
      }

      void attributeType::resourceType::
      uri (Type& o)
      {
        dispatch (o.uri ());
      }

      void attributeType::resourceType::
      uri (Type const& o)
      {
        dispatch (o.uri ());
      }

      void attributeType::resourceType::
      checksum (Type& o)
      {
        dispatch (o.checksum ());
      }

      void attributeType::resourceType::
      checksum (Type const& o)
      {
        dispatch (o.checksum ());
      }

      void attributeType::resourceType::
      checksum_none (Type&)
      {
      }

      void attributeType::resourceType::
      checksum_none (Type const&)
      {
      }

      void attributeType::resourceType::
      post (Type&)
      {
      }

      void attributeType::resourceType::
      post (Type const&)
      {
      }

      // attributeType
      //
      //

      void attributeType::
      traverse (Type& o)
      {
        pre (o);
        owner (o);

        if (o.count_resource () == 0)
          value (o);
        else
          resource (o);

        if (o.units_p ()) units (o);
        else units_none (o);
        if (o.documentation_p ()) documentation (o);
        else documentation_none (o);
        post (o);
      }

      void attributeType::
      traverse (Type const& o)
      {
        pre (o);
        owner (o);

        if (o.count_resource () == 0)
          value (o);
        else
          resource (o);

        if (o.units_p ()) units (o);
        else units_none (o);
        if (o.documentation_p ()) documentation (o);
        else documentation_none (o);
        post (o);
      }

      void attributeType::
      pre (Type&)
      {
      }

      void attributeType::
      pre (Type const&)
      {
      }

      void attributeType::
      owner (Type& o)
      {
        dispatch (o.owner ());
      }

      void attributeType::
      owner (Type const& o)
      {
        dispatch (o.owner ());
      }

      void attributeType::
      value (Type& o)
      {
        dispatch (o.value ());
      }

      void attributeType::
      value (Type const& o)
      {
        dispatch (o.value ());
      }

      void attributeType::
      resource (Type& o)
      {
        // VC6 anathema strikes again
        //
        ::naomi::attributes::attributeType::resource_iterator b (o.begin_resource()), e (o.end_resource());

        if (b != e)
        {
          resource_pre (o);
          for (; b != e;)
          {
            dispatch (*b);
            if (++b != e) resource_next (o);
          }

          resource_post (o);
        }

        else resource_none (o);
      }

      void attributeType::
      resource (Type const& o)
      {
        // VC6 anathema strikes again
        //
        ::naomi::attributes::attributeType::resource_const_iterator b (o.begin_resource()), e (o.end_resource());

        if (b != e)
        {
          resource_pre (o);
          for (; b != e;)
          {
            dispatch (*b);
            if (++b != e) resource_next (o);
          }

          resource_post (o);
        }

        else resource_none (o);
      }

      void attributeType::
      resource_pre (Type&)
      {
      }

      void attributeType::
      resource_pre (Type const&)
      {
      }

      void attributeType::
      resource_next (Type&)
      {
      }

      void attributeType::
      resource_next (Type const&)
      {
      }

      void attributeType::
      resource_post (Type&)
      {
      }

      void attributeType::
      resource_post (Type const&)
      {
      }

      void attributeType::
      resource_none (Type&)
      {
      }

      void attributeType::
      resource_none (Type const&)
      {
      }

      void attributeType::
      units (Type& o)
      {
        dispatch (o.units ());
      }

      void attributeType::
      units (Type const& o)
      {
        dispatch (o.units ());
      }

      void attributeType::
      units_none (Type&)
      {
      }

      void attributeType::
      units_none (Type const&)
      {
      }

      void attributeType::
      documentation (Type& o)
      {
        dispatch (o.documentation ());
      }

      void attributeType::
      documentation (Type const& o)
      {
        dispatch (o.documentation ());
      }

      void attributeType::
      documentation_none (Type&)
      {
      }

      void attributeType::
      documentation_none (Type const&)
      {
      }

      void attributeType::
      post (Type&)
      {
      }

      void attributeType::
      post (Type const&)
      {
      }
    }
  }
}

namespace naomi
{
  namespace attributes
  {
    namespace Writer
    {
      // resourceType
      //
      //

      attributeType::resourceType::
      resourceType (::XSCRT::XML::Element< char >& e)
      : ::XSCRT::Writer< char > (e)
      {
      }

      attributeType::resourceType::
      resourceType ()
      {
      }

      void attributeType::resourceType::
      traverse (Type const& o)
      {
        Traversal::attributeType::resourceType::traverse (o);
      }

      void attributeType::resourceType::
      name (Type const& o)
      {
        ::XSCRT::XML::Attribute< char > a ("name", "", top_ ());
        attr_ (&a);
        Traversal::attributeType::resourceType::name (o);
        attr_ (0);
      }

      void attributeType::resourceType::
      uri (Type const& o)
      {
        ::XSCRT::XML::Attribute< char > a ("uri", "", top_ ());
        attr_ (&a);
        Traversal::attributeType::resourceType::uri (o);
        attr_ (0);
      }

      void attributeType::resourceType::
      checksum (Type const& o)
      {
        ::XSCRT::XML::Attribute< char > a ("checksum", "", top_ ());
        attr_ (&a);
        Traversal::attributeType::resourceType::checksum (o);
        attr_ (0);
      }

      // attributeType
      //
      //

      attributeType::
      attributeType (::XSCRT::XML::Element< char >& e)
      : ::XSCRT::Writer< char > (e)
      {
      }

      attributeType::
      attributeType ()
      {
      }

      void attributeType::
      traverse (Type const& o)
      {
        Traversal::attributeType::traverse (o);
      }

      void attributeType::
      owner (Type const& o)
      {
        push_ (::XSCRT::XML::Element< char > ("owner", "http://www.atl.lmco.com/naomi/attributes", top_ ()));
        Traversal::attributeType::owner (o);
        pop_ ();
      }

      void attributeType::
      value (Type const& o)
      {
        push_ (::XSCRT::XML::Element< char > ("value", "http://www.atl.lmco.com/naomi/attributes", top_ ()));
        Traversal::attributeType::value (o);
        pop_ ();
      }

      void attributeType::
      resource_pre (Type const&)
      {
        push_ (::XSCRT::XML::Element< char > ("resource", "http://www.atl.lmco.com/naomi/attributes", top_ ()));
      }

      void attributeType::
      resource_next (Type const& o)
      {
        resource_post (o);
        resource_pre (o);
      }

      void attributeType::
      resource_post (Type const&)
      {
        pop_ ();
      }

      void attributeType::
      units (Type const& o)
      {
        push_ (::XSCRT::XML::Element< char > ("units", "http://www.atl.lmco.com/naomi/attributes", top_ ()));
        Traversal::attributeType::units (o);
        pop_ ();
      }

      void attributeType::
      documentation (Type const& o)
      {
        push_ (::XSCRT::XML::Element< char > ("documentation", "http://www.atl.lmco.com/naomi/attributes", top_ ()));
        Traversal::attributeType::documentation (o);
        pop_ ();
      }
    }
  }
}

namespace naomi
{
  namespace attributes
  {
    namespace writer
    {
      void
      attribute (::naomi::attributes::attributeType const& s, xercesc::DOMDocument* d)
      {
        ::XSCRT::XML::Element< char > e (d->getDocumentElement ());
        if (e.name () != "attribute")
        {
          throw 1;
        }

        struct W : virtual ::naomi::attributes::Writer::attributeType,
        virtual ::XMLSchema::Writer::FundamentalType< ::XMLSchema::string< char >, char >,
        virtual ::naomi::attributes::Writer::attributeType::resourceType,
        virtual ::XMLSchema::Writer::FundamentalType< ::XMLSchema::anyURI< char >, char >,
        virtual ::XSCRT::Writer< char >
        {
          W (::XSCRT::XML::Element< char >& e)
          : ::XSCRT::Writer< char > (e)
          {
          }
        };

        W w (e);
        w.dispatch (s);
      }
    }
  }
}

