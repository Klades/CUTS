#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

// Forward declarations.
//
namespace naomi
{
  namespace attributes
  {
    class attributeType;
  }
}

#include <memory>
#include <list>
#include "XMLSchema/Types.hpp"

namespace naomi
{
  namespace attributes
  {
    // anonymous type for attributeType
    //
    class attributeType : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      // owner
      //
      public:
      ::XMLSchema::string< char > const& owner () const;
      void owner (::XMLSchema::string< char > const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::string< char > > owner_;

      // value
      //
      public:
      ::XMLSchema::string< char > const& value () const;
      void value (::XMLSchema::string< char > const& );

      protected:
      mutable ::std::auto_ptr< ::XMLSchema::string< char > > value_;

      // anonymous type for resourceType
      //
      public:
      class resourceType : public ::XSCRT::Type
      {
        typedef ::XSCRT::Type Base;

        // name
        //
        public:
        ::XMLSchema::string< char > const& name () const;
        ::XMLSchema::string< char >& name ();
        void name (::XMLSchema::string< char > const& );

        protected:
        ::std::auto_ptr< ::XMLSchema::string< char > > name_;

        // uri
        //
        public:
        ::XMLSchema::anyURI< char > const& uri () const;
        ::XMLSchema::anyURI< char >& uri ();
        void uri (::XMLSchema::anyURI< char > const& );

        protected:
        ::std::auto_ptr< ::XMLSchema::anyURI< char > > uri_;

        // checksum
        //
        public:
        bool checksum_p () const;
        ::XMLSchema::string< char > const& checksum () const;
        ::XMLSchema::string< char >& checksum ();
        void checksum (::XMLSchema::string< char > const& );

        protected:
        ::std::auto_ptr< ::XMLSchema::string< char > > checksum_;

        public:
        resourceType (::XMLSchema::string< char > const& name__,
                      ::XMLSchema::anyURI< char > const& uri__);

        resourceType (::XSCRT::XML::Element< char > const&);
        resourceType (resourceType const& s);

        resourceType&
        operator= (resourceType const& s);

        private:
        char regulator__;
      };


      // resource
      //
      public:
      typedef ::std::list< resourceType >::iterator resource_iterator;
      typedef ::std::list< resourceType >::const_iterator resource_const_iterator;
      resource_iterator begin_resource ();
      resource_iterator end_resource ();
      resource_const_iterator begin_resource () const;
      resource_const_iterator end_resource () const;
      void add_resource (resourceType const& );
      size_t count_resource (void) const;

      protected:
      ::std::list< resourceType > resource_;

      // units
      //
      public:
      bool units_p () const;
      ::XMLSchema::string< char > const& units () const;
      void units (::XMLSchema::string< char > const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::string< char > > units_;

      // documentation
      //
      public:
      bool documentation_p () const;
      ::XMLSchema::string< char > const& documentation () const;
      void documentation (::XMLSchema::string< char > const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::string< char > > documentation_;

      public:
      attributeType (::XMLSchema::string< char > const& owner__,
                     ::XMLSchema::string< char > const& value__);

      attributeType (::XSCRT::XML::Element< char > const&);
      attributeType (attributeType const& s);

      attributeType&
      operator= (attributeType const& s);

      private:
      char regulator__;
    };
  }
}

namespace naomi
{
  namespace attributes
  {
    namespace reader
    {
      attributeType
      attribute (xercesc::DOMDocument const*);
    }
  }
}

#include "XMLSchema/Traversal.hpp"

namespace naomi
{
  namespace attributes
  {
    namespace Traversal
    {
      // anonymous type for attributeType
      //
      struct attributeType : ::XMLSchema::Traversal::Traverser< ::naomi::attributes::attributeType >
      {
        virtual void
        traverse (Type&);

        virtual void
        traverse (Type const&);

        virtual void
        pre (Type&);

        virtual void
        pre (Type const&);

        virtual void
        owner (Type&);

        virtual void
        owner (Type const&);

        virtual void
        value (Type&);

        virtual void
        value (Type const&);

        // anonymous type for resourceType
        //
        public:
        struct resourceType : ::XMLSchema::Traversal::Traverser< ::naomi::attributes::attributeType::resourceType >
        {
          virtual void
          traverse (Type&);

          virtual void
          traverse (Type const&);

          virtual void
          pre (Type&);

          virtual void
          pre (Type const&);

          virtual void
          name (Type&);

          virtual void
          name (Type const&);

          virtual void
          uri (Type&);

          virtual void
          uri (Type const&);

          virtual void
          checksum (Type&);

          virtual void
          checksum (Type const&);

          virtual void
          checksum_none (Type&);

          virtual void
          checksum_none (Type const&);

          virtual void
          post (Type&);

          virtual void
          post (Type const&);
        };

        virtual void
        resource (Type&);

        virtual void
        resource (Type const&);

        virtual void
        resource_pre (Type&);

        virtual void
        resource_pre (Type const&);

        virtual void
        resource_next (Type&);

        virtual void
        resource_next (Type const&);

        virtual void
        resource_post (Type&);

        virtual void
        resource_post (Type const&);

        virtual void
        resource_none (Type&);

        virtual void
        resource_none (Type const&);

        virtual void
        units (Type&);

        virtual void
        units (Type const&);

        virtual void
        units_none (Type&);

        virtual void
        units_none (Type const&);

        virtual void
        documentation (Type&);

        virtual void
        documentation (Type const&);

        virtual void
        documentation_none (Type&);

        virtual void
        documentation_none (Type const&);

        virtual void
        post (Type&);

        virtual void
        post (Type const&);
      };
    }
  }
}

#include "XMLSchema/Writer.hpp"

namespace naomi
{
  namespace attributes
  {
    namespace Writer
    {
      // anonymous type for attributeType
      //
      struct attributeType : Traversal::attributeType,
      virtual ::XSCRT::Writer< char >
      {
        typedef ::naomi::attributes::attributeType Type;
        attributeType (::XSCRT::XML::Element< char >&);

        virtual void
        traverse (Type &o)
        {
          this->traverse (const_cast <Type const &> (o));
        }

        virtual void
        traverse (Type const&);

        virtual void
        owner (Type &o)
        {
          this->owner (const_cast <Type const &> (o));
        }

        virtual void
        owner (Type const&);

        virtual void
        value (Type &o)
        {
          this->value (const_cast <Type const &> (o));
        }

        virtual void
        value (Type const&);

        virtual void
        resource_pre (Type &o)
        {
          this->resource_pre (const_cast <Type const &> (o));
        }

        virtual void
        resource_pre (Type const&);

        virtual void
        resource_next (Type &o)
        {
          this->resource_next (const_cast <Type const &> (o));
        }

        virtual void
        resource_next (Type const&);

        virtual void
        resource_post (Type &o)
        {
          this->resource_post (const_cast <Type const &> (o));
        }

        virtual void
        resource_post (Type const&);

        // anonymous type for resourceType
        //
        public:
        struct resourceType : Traversal::attributeType::resourceType,
        virtual ::XSCRT::Writer< char >
        {
          typedef ::naomi::attributes::attributeType::resourceType Type;
          resourceType (::XSCRT::XML::Element< char >&);

          virtual void
          traverse (Type &o)
          {
            this->traverse (const_cast <Type const &> (o));
          }

          virtual void
          traverse (Type const&);

          virtual void
          name (Type &o)
          {
            this->name (const_cast <Type const &> (o));
          }

          virtual void
          name (Type const&);

          virtual void
          uri (Type &o)
          {
            this->uri (const_cast <Type const &> (o));
          }

          virtual void
          uri (Type const&);

          virtual void
          checksum (Type &o)
          {
            this->checksum (const_cast <Type const &> (o));
          }

          virtual void
          checksum (Type const&);

          protected:
          resourceType ();
        };

        virtual void
        units (Type &o)
        {
          this->units (const_cast <Type const &> (o));
        }

        virtual void
        units (Type const&);

        virtual void
        documentation (Type &o)
        {
          this->documentation (const_cast <Type const &> (o));
        }

        virtual void
        documentation (Type const&);

        protected:
        attributeType ();
      };
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
      attribute (::naomi::attributes::attributeType const&, xercesc::DOMDocument*);
    }
  }
}

#include "attribute.inl"

#endif // ATTRIBUTE_H
