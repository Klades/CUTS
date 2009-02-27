#include "cuts-unite.h"

namespace CUTS
{
  // uniteConfig
  //

  uniteConfig::
  uniteConfig (::XSCRT::XML::Element< char > const& e)
  :Base (e), regulator__ ()
  {

    ::XSCRT::Parser< char > p (e);

    while (p.more_elements ())
    {
      ::XSCRT::XML::Element< char > e (p.next_element ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

      if (n == "name")
      {
        name_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
        name_->container (this);
      }

      else if (n == "description")
      {
        ::XMLSchema::string< char > t (e);
        description (t);
      }

      else if (n == "evaluation")
      {
        evaluation_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
        evaluation_->container (this);
      }

      else if (n == "aggregation")
      {
        aggregation_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
        aggregation_->container (this);
      }

      else if (n == "logformats")
      {
        logformats_ = ::std::auto_ptr< ::CUTS::logformatList > (new ::CUTS::logformatList (e));
        logformats_->container (this);
      }

      else if (n == "grouping")
      {
        ::CUTS::groupingType t (e);
        grouping (t);
      }

      else 
      {
      }
    }
  }

  // logformatType
  //

  logformatType::
  logformatType (::XSCRT::XML::Element< char > const& e)
  :Base (e), regulator__ ()
  {

    ::XSCRT::Parser< char > p (e);

    while (p.more_elements ())
    {
      ::XSCRT::XML::Element< char > e (p.next_element ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

      if (n == "value")
      {
        value_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
        value_->container (this);
      }

      else if (n == "relations")
      {
        ::CUTS::relationList t (e);
        relations (t);
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

  // relationList
  //

  relationList::
  relationList (::XSCRT::XML::Element< char > const& e)
  :Base (e), regulator__ ()
  {

    ::XSCRT::Parser< char > p (e);

    while (p.more_elements ())
    {
      ::XSCRT::XML::Element< char > e (p.next_element ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

      if (n == "relation")
      {
        ::CUTS::relationType t (e);
        add_relation (t);
      }

      else 
      {
      }
    }
  }

  // causalityType
  //

  causalityType::
  causalityType (::XSCRT::XML::Element< char > const& e)
  :Base (e), regulator__ ()
  {

    ::XSCRT::Parser< char > p (e);

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "cause")
      {
        cause_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (a));
        cause_->container (this);
      }

      else if (n == "effect")
      {
        effect_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (a));
        effect_->container (this);
      }

      else 
      {
      }
    }
  }

  // relationType
  //

  relationType::
  relationType (::XSCRT::XML::Element< char > const& e)
  :Base (e), regulator__ ()
  {

    ::XSCRT::Parser< char > p (e);

    while (p.more_elements ())
    {
      ::XSCRT::XML::Element< char > e (p.next_element ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

      if (n == "causality")
      {
        ::CUTS::causalityType t (e);
        add_causality (t);
      }

      else 
      {
      }
    }

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "effectref")
      {
        effectref_ = ::std::auto_ptr< ::XMLSchema::NCName< char > > (new ::XMLSchema::NCName< char > (a));
        effectref_->container (this);
      }

      else 
      {
      }
    }
  }

  // logformatList
  //

  logformatList::
  logformatList (::XSCRT::XML::Element< char > const& e)
  :Base (e), regulator__ ()
  {

    ::XSCRT::Parser< char > p (e);

    while (p.more_elements ())
    {
      ::XSCRT::XML::Element< char > e (p.next_element ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

      if (n == "logformat")
      {
        ::CUTS::logformatType t (e);
        add_logformat (t);
      }

      else 
      {
      }
    }
  }

  // groupitemType
  //

  groupitemType::
  groupitemType (::XSCRT::XML::Element< char > const& e)
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

      else 
      {
      }
    }
  }

  // groupingType
  //

  groupingType::
  groupingType (::XSCRT::XML::Element< char > const& e)
  :Base (e), regulator__ ()
  {

    ::XSCRT::Parser< char > p (e);

    while (p.more_elements ())
    {
      ::XSCRT::XML::Element< char > e (p.next_element ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

      if (n == "groupitem")
      {
        ::CUTS::groupitemType t (e);
        add_groupitem (t);
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
    ::CUTS::uniteConfig
    unite (xercesc::DOMDocument const* d)
    {
      ::XSCRT::XML::Element< char > e (d->getDocumentElement ());
      if (e.name () == "unite")
      {
        ::CUTS::uniteConfig r (e);
        return r;
      }

      else
      {
        throw 1;
      }
    }
  }
}

