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

        if (n == ACE_TEXT("name"))
        {
          name_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
          name_->container (this);
        }

        else if (n == ACE_TEXT("description"))
        {
          ::XMLSchema::string< char > t (e);
          description (t);
        }

        else if (n == ACE_TEXT("evaluation"))
        {
          evaluation_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
          evaluation_->container (this);
        }

        else if (n == ACE_TEXT("aggregation"))
        {
          aggregation_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
          aggregation_->container (this);
        }

        else if (n == ACE_TEXT("datagraph"))
        {
          datagraph_ = ::std::auto_ptr< ::CUTS::XML::datagraphLink > (new ::CUTS::XML::datagraphLink (e));
          datagraph_->container (this);
        }

        else if (n == ACE_TEXT("grouping"))
        {
          ::CUTS::XML::groupingType t (e);
          grouping (t);
        }

        else if (n == ACE_TEXT("services"))
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

        if (n == ACE_TEXT("value"))
        {
          value_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
          value_->container (this);
        }

        else if (n == ACE_TEXT("relations"))
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
          std::basic_string<ACE_TCHAR> temp (ACE_TEXT_CHAR_TO_TCHAR ((*id_).c_str()));
          (*ACE_Singleton<ID_Map::TSS_ID_Map, ACE_Null_Mutex>::instance())->
          add_id(temp, dynamic_cast<XSCRT::Type*> (this));
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

        if (n == ACE_TEXT("relation"))
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

        if (n == ACE_TEXT("causality"))
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

        if (n == ACE_TEXT("logformat"))
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

        if (n == ACE_TEXT("groupitem"))
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

        if (n == ACE_TEXT("name"))
        {
          name_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
          name_->container (this);
        }

        else if (n == ACE_TEXT("logformats"))
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

        if (n == ACE_TEXT("filter"))
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

        if (n == ACE_TEXT("variable"))
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
          std::basic_string<ACE_TCHAR> temp (ACE_TEXT_CHAR_TO_TCHAR ((*id_).c_str()));
          (*ACE_Singleton<ID_Map::TSS_ID_Map, ACE_Null_Mutex>::instance())->
          add_id(temp, dynamic_cast<XSCRT::Type*> (this));
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

        if (n == ACE_TEXT("location"))
        {
          location_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
          location_->container (this);
        }

        else if (n == ACE_TEXT("classname"))
        {
          classname_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
          classname_->container (this);
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

        if (n == ACE_TEXT("expression"))
        {
          ACE_Refcounted_Auto_Ptr < ::CUTS::XML::expressionType, ACE_Null_Mutex >  t (new ::CUTS::XML::expressionType (e));
          add_expression (t);
        }

        else if (n == ACE_TEXT("condition"))
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

        if (n == ACE_TEXT("name"))
        {
          ::XMLSchema::ID< char > t (e);
          name (t);
          std::basic_string<ACE_TCHAR> temp (ACE_TEXT_CHAR_TO_TCHAR ((*name_).c_str()));
          (*ACE_Singleton<ID_Map::TSS_ID_Map, ACE_Null_Mutex>::instance())->
          add_id(temp, dynamic_cast<XSCRT::Type*> (this));
        }

        else if (n == ACE_TEXT("viewpoint"))
        {
          ::CUTS::XML::viewpointType t (e);
          viewpoint (t);
        }

        else if (n == ACE_TEXT("condition"))
        {
          ::XMLSchema::string< char > t (e);
          condition (t);
        }

        else 
        {
        }
      }
    }

    // validationType
    //

    validationType::
    validationType (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("name"))
        {
          ::XMLSchema::ID< char > t (e);
          name (t);
          std::basic_string<ACE_TCHAR> temp (ACE_TEXT_CHAR_TO_TCHAR ((*name_).c_str()));
          (*ACE_Singleton<ID_Map::TSS_ID_Map, ACE_Null_Mutex>::instance())->
          add_id(temp, dynamic_cast<XSCRT::Type*> (this));
        }

        else if (n == ACE_TEXT("condition"))
        {
          ::CUTS::XML::conditionType t (e);
          condition (t);
        }

        else 
        {
        }
      }
    }

    // viewpointType
    //

    viewpointType::
    viewpointType (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_attributes ())
      {
        ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
        if (n == "before")
        {
          ::XMLSchema::unsignedInt t (a);
          before (t);
        }

        else if (n == "after")
        {
          ::XMLSchema::unsignedInt t (a);
          after (t);
        }

        else 
        {
        }
      }
    }

    // executionStateType
    //

    executionStateType::
    executionStateType (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("context"))
        {
          context_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
          context_->container (this);
        }

        else if (n == ACE_TEXT("value"))
        {
          value_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
          value_->container (this);
        }

        else 
        {
        }
      }

      while (p.more_attributes ())
      {
        ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
        if (n == "minoccurs")
        {
          ::XMLSchema::unsignedInt t (a);
          minoccurs (t);
        }

        else if (n == "priority")
        {
          ::XMLSchema::unsignedInt t (a);
          priority (t);
        }

        else if (n == "id")
        {
          ::XMLSchema::ID< char > t (a);
          id (t);
          std::basic_string<ACE_TCHAR> temp (ACE_TEXT_CHAR_TO_TCHAR ((*id_).c_str()));
          (*ACE_Singleton<ID_Map::TSS_ID_Map, ACE_Null_Mutex>::instance())->
          add_id(temp, dynamic_cast<XSCRT::Type*> (this));
        }

        else if (n == "maxoccurs")
        {
          ::XMLSchema::string< char > t (a);
          maxoccurs (t);
        }

        else 
        {
        }
      }
    }

    // validityType
    //

    validityType::
    validityType (::XSCRT::XML::Element< char > const& e)
    : ::XSCRT::Type (e)
    {
      ::std::basic_string< char > v (e.value ());

      if (v == "valid") v_ = valid_l;
      else if (v == "invalid") v_ = invalid_l;
      else 
      {
      }
    }

    validityType::
    validityType (::XSCRT::XML::Attribute< char > const& a)
    : ::XSCRT::Type (a)
    {
      ::std::basic_string< char > v (a.value ());

      if (v == "valid") v_ = valid_l;
      else if (v == "invalid") v_ = invalid_l;
      else 
      {
      }
    }

    validityType const validityType::valid (validityType::valid_l);
    validityType const validityType::invalid (validityType::invalid_l);

    // correctnessTestType
    //

    correctnessTestType::
    correctnessTestType (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("datagraph"))
        {
          datagraph_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
          datagraph_->container (this);
        }

        else if (n == ACE_TEXT("state"))
        {
          ACE_Refcounted_Auto_Ptr < ::CUTS::XML::executionStateType, ACE_Null_Mutex >  t (new ::CUTS::XML::executionStateType (e));
          add_state (t);
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
        //Initiate our Singleton as an ACE_TSS object (ensures thread
        //specific storage
        ID_Map::TSS_ID_Map* TSS_ID_Map (ACE_Singleton<ID_Map::TSS_ID_Map, ACE_Null_Mutex>::instance());


        ::XSCRT::XML::Element< char > e (d->getDocumentElement ());
        if (e.name () == ACE_TEXT("test"))
        {
          ::CUTS::XML::testConfig r (e);

          (*TSS_ID_Map)->resolve_idref();

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
        //Initiate our Singleton as an ACE_TSS object (ensures thread
        //specific storage
        ID_Map::TSS_ID_Map* TSS_ID_Map (ACE_Singleton<ID_Map::TSS_ID_Map, ACE_Null_Mutex>::instance());


        ::XSCRT::XML::Element< char > e (d->getDocumentElement ());
        if (e.name () == ACE_TEXT("datagraph"))
        {
          ::CUTS::XML::datagraphType r (e);

          (*TSS_ID_Map)->resolve_idref();

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
        //Initiate our Singleton as an ACE_TSS object (ensures thread
        //specific storage
        ID_Map::TSS_ID_Map* TSS_ID_Map (ACE_Singleton<ID_Map::TSS_ID_Map, ACE_Null_Mutex>::instance());


        ::XSCRT::XML::Element< char > e (d->getDocumentElement ());
        if (e.name () == ACE_TEXT("filters"))
        {
          ::CUTS::XML::filterList r (e);

          (*TSS_ID_Map)->resolve_idref();

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
      ::CUTS::XML::aspectType
      aspect (xercesc::DOMDocument const* d)
      {
        //Initiate our Singleton as an ACE_TSS object (ensures thread
        //specific storage
        ID_Map::TSS_ID_Map* TSS_ID_Map (ACE_Singleton<ID_Map::TSS_ID_Map, ACE_Null_Mutex>::instance());


        ::XSCRT::XML::Element< char > e (d->getDocumentElement ());
        if (e.name () == ACE_TEXT("aspect"))
        {
          ::CUTS::XML::aspectType r (e);

          (*TSS_ID_Map)->resolve_idref();

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
      ::CUTS::XML::validationType
      validation (xercesc::DOMDocument const* d)
      {
        //Initiate our Singleton as an ACE_TSS object (ensures thread
        //specific storage
        ID_Map::TSS_ID_Map* TSS_ID_Map (ACE_Singleton<ID_Map::TSS_ID_Map, ACE_Null_Mutex>::instance());


        ::XSCRT::XML::Element< char > e (d->getDocumentElement ());
        if (e.name () == ACE_TEXT("validation"))
        {
          ::CUTS::XML::validationType r (e);

          (*TSS_ID_Map)->resolve_idref();

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
      ::CUTS::XML::correctnessTestType
      correctness (xercesc::DOMDocument const* d)
      {
        //Initiate our Singleton as an ACE_TSS object (ensures thread
        //specific storage
        ID_Map::TSS_ID_Map* TSS_ID_Map (ACE_Singleton<ID_Map::TSS_ID_Map, ACE_Null_Mutex>::instance());


        ::XSCRT::XML::Element< char > e (d->getDocumentElement ());
        if (e.name () == ACE_TEXT("correctness"))
        {
          ::CUTS::XML::correctnessTestType r (e);

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

