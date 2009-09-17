#include "cuts-unite.h"

namespace CUTS
{
  namespace XML
  {
    // testConfig
    //

    testConfig::
    testConfig (::XSCRT::XML::Element< char > const& e)
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

        else if (n == "datagraph")
        {
          datagraph_ = ::std::auto_ptr< ::CUTS::XML::datagraphLink > (new ::CUTS::XML::datagraphLink (e));
          datagraph_->container (this);
        }

        else if (n == "grouping")
        {
          ::CUTS::XML::groupingType t (e);
          grouping (t);
        }

        else if (n == "services")
        {
          ::CUTS::XML::serviceList t (e);
          services (t);
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
          ::CUTS::XML::relationList t (e);
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
          ACE_Refcounted_Auto_Ptr < ::CUTS::XML::relationType, ACE_Null_Mutex >  t (new ::CUTS::XML::relationType (e));
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
          ACE_Refcounted_Auto_Ptr < ::CUTS::XML::causalityType, ACE_Null_Mutex >  t (new ::CUTS::XML::causalityType (e));
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
          ACE_Refcounted_Auto_Ptr < ::CUTS::XML::logformatType, ACE_Null_Mutex >  t (new ::CUTS::XML::logformatType (e));
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
          ACE_Refcounted_Auto_Ptr < ::CUTS::XML::groupitemType, ACE_Null_Mutex >  t (new ::CUTS::XML::groupitemType (e));
          add_groupitem (t);
        }

        else 
        {
        }
      }
    }

    // datagraphType
    //

    datagraphType::
    datagraphType (::XSCRT::XML::Element< char > const& e)
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

        else if (n == "logformats")
        {
          ::CUTS::XML::logformatList t (e);
          logformats (t);
        }

        else 
        {
        }
      }
    }

    // datagraphLink
    //

    datagraphLink::
    datagraphLink (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_attributes ())
      {
        ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
        if (n == "location")
        {
          location_ = ::std::auto_ptr< ::XMLSchema::anyURI< char > > (new ::XMLSchema::anyURI< char > (a));
          location_->container (this);
        }

        else 
        {
        }
      }
    }

    // filterList
    //

    filterList::
    filterList (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == "filter")
        {
          ACE_Refcounted_Auto_Ptr < ::CUTS::XML::filterType, ACE_Null_Mutex >  t (new ::CUTS::XML::filterType (e));
          add_filter (t);
        }

        else 
        {
        }
      }
    }

    // filterType
    //

    filterType::
    filterType (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == "variable")
        {
          ACE_Refcounted_Auto_Ptr < ::CUTS::XML::filterVariableType, ACE_Null_Mutex >  t (new ::CUTS::XML::filterVariableType (e));
          add_variable (t);
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

        else if (n == "target")
        {
          target_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (a));
          target_->container (this);
        }

        else 
        {
        }
      }
    }

    // filterVariableType
    //

    filterVariableType::
    filterVariableType (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_attributes ())
      {
        ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
        if (n == "name")
        {
          ::XMLSchema::string< char > t (a);
          name (t);
        }

        else if (n == "when")
        {
          ::XMLSchema::string< char > t (a);
          when (t);
        }

        else 
        {
        }
      }
    }

    // serviceType
    //

    serviceType::
    serviceType (::XSCRT::XML::Element< char > const& e)
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

        else if (n == "classname")
        {
          classname_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
          classname_->container (this);
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
          ACE_Refcounted_Auto_Ptr < ::CUTS::XML::serviceType, ACE_Null_Mutex >  t (new ::CUTS::XML::serviceType (e));
          add_service (t);
        }

        else 
        {
        }
      }
    }

    // conditionType
    //

    conditionType::
    conditionType (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == "expression")
        {
          ACE_Refcounted_Auto_Ptr < ::CUTS::XML::expressionType, ACE_Null_Mutex >  t (new ::CUTS::XML::expressionType (e));
          add_expression (t);
        }

        else if (n == "condition")
        {
          ACE_Refcounted_Auto_Ptr < ::CUTS::XML::conditionType, ACE_Null_Mutex >  t (new ::CUTS::XML::conditionType (e));
          add_condition (t);
        }

        else 
        {
        }
      }

      while (p.more_attributes ())
      {
        ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
        if (n == "type")
        {
          type_ = ::std::auto_ptr< ::CUTS::XML::joinType > (new ::CUTS::XML::joinType (a));
          type_->container (this);
        }

        else if (n == "negate")
        {
          ::XMLSchema::boolean t (a);
          negate (t);
        }

        else 
        {
        }
      }
    }

    // joinType
    //

    joinType::
    joinType (::XSCRT::XML::Element< char > const& e)
    : ::XSCRT::Type (e)
    {
      ::std::basic_string< char > v (e.value ());

      if (v == "conjunction") v_ = conjunction_l;
      else if (v == "disjunction") v_ = disjunction_l;
      else 
      {
      }
    }

    joinType::
    joinType (::XSCRT::XML::Attribute< char > const& a)
    : ::XSCRT::Type (a)
    {
      ::std::basic_string< char > v (a.value ());

      if (v == "conjunction") v_ = conjunction_l;
      else if (v == "disjunction") v_ = disjunction_l;
      else 
      {
      }
    }

    joinType const joinType::conjunction (joinType::conjunction_l);
    joinType const joinType::disjunction (joinType::disjunction_l);

    // expressionType
    //

    expressionType::
    expressionType (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_attributes ())
      {
        ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
        if (n == "format")
        {
          format_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (a));
          format_->container (this);
        }

        else if (n == "variable")
        {
          variable_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (a));
          variable_->container (this);
        }

        else if (n == "value")
        {
          value_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (a));
          value_->container (this);
        }

        else if (n == "negate")
        {
          ::XMLSchema::boolean t (a);
          negate (t);
        }

        else 
        {
        }
      }
    }

    // aspectType
    //

    aspectType::
    aspectType (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == "id")
        {
          id_ = ::std::auto_ptr< ::XMLSchema::ID< char > > (new ::XMLSchema::ID< char > (e));
          id_->container (this);
        }

        else if (n == "condition")
        {
          ACE_Refcounted_Auto_Ptr < ::CUTS::XML::conditionType, ACE_Null_Mutex >  t (new ::CUTS::XML::conditionType (e));
          add_condition (t);
        }

        else 
        {
        }
      }
    }

    // aspectsType
    //

    aspectsType::
    aspectsType (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == "aspect")
        {
          ACE_Refcounted_Auto_Ptr < ::CUTS::XML::aspectType, ACE_Null_Mutex >  t (new ::CUTS::XML::aspectType (e));
          add_aspect (t);
        }

        else 
        {
        }
      }
    }
  }
}

namespace CUTS
{
  namespace XML
  {
    namespace reader
    {
      ::CUTS::XML::testConfig
      test (xercesc::DOMDocument const* d)
      {
        ::XSCRT::XML::Element< char > e (d->getDocumentElement ());
        if (e.name () == "test")
        {
          ::CUTS::XML::testConfig r (e);
          return r;
        }

        else
        {
          throw 1;
        }
      }
    }

    namespace reader
    {
      ::CUTS::XML::datagraphType
      datagraph (xercesc::DOMDocument const* d)
      {
        ::XSCRT::XML::Element< char > e (d->getDocumentElement ());
        if (e.name () == "datagraph")
        {
          ::CUTS::XML::datagraphType r (e);
          return r;
        }

        else
        {
          throw 1;
        }
      }
    }

    namespace reader
    {
      ::CUTS::XML::filterList
      filters (xercesc::DOMDocument const* d)
      {
        ::XSCRT::XML::Element< char > e (d->getDocumentElement ());
        if (e.name () == "filters")
        {
          ::CUTS::XML::filterList r (e);
          return r;
        }

        else
        {
          throw 1;
        }
      }
    }

    namespace reader
    {
      ::CUTS::XML::aspectsType
      aspects (xercesc::DOMDocument const* d)
      {
        ::XSCRT::XML::Element< char > e (d->getDocumentElement ());
        if (e.name () == "aspects")
        {
          ::CUTS::XML::aspectsType r (e);
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

