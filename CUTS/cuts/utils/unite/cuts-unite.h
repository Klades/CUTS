#ifndef CUTS_UNITE_H
#define CUTS_UNITE_H

// Forward declarations.
//
namespace CUTS
{
  class uniteConfig;
  class logformatType;
  class relationList;
  class causalityType;
  class relationType;
  class logformatList;
  class groupitemType;
  class groupingType;
  class datagraphType;
  class datagraphLink;
}

#include <memory>
#include <list>
#include "XMLSchema/Types.hpp"

namespace CUTS
{
  class uniteConfig : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    // name
    // 
    public:
    ::XMLSchema::string< char > const& name () const;
    void name (::XMLSchema::string< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::string< char > > name_;

    // description
    // 
    public:
    bool description_p () const;
    ::XMLSchema::string< char > const& description () const;
    void description (::XMLSchema::string< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::string< char > > description_;

    // evaluation
    // 
    public:
    ::XMLSchema::string< char > const& evaluation () const;
    void evaluation (::XMLSchema::string< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::string< char > > evaluation_;

    // aggregation
    // 
    public:
    ::XMLSchema::string< char > const& aggregation () const;
    void aggregation (::XMLSchema::string< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::string< char > > aggregation_;

    // datagraph
    // 
    public:
    ::CUTS::datagraphLink const& datagraph () const;
    void datagraph (::CUTS::datagraphLink const& );

    protected:
    ::std::auto_ptr< ::CUTS::datagraphLink > datagraph_;

    // grouping
    // 
    public:
    bool grouping_p () const;
    ::CUTS::groupingType const& grouping () const;
    void grouping (::CUTS::groupingType const& );

    protected:
    ::std::auto_ptr< ::CUTS::groupingType > grouping_;

    public:
    uniteConfig (::XMLSchema::string< char > const& name__,
                 ::XMLSchema::string< char > const& evaluation__,
                 ::XMLSchema::string< char > const& aggregation__,
                 ::CUTS::datagraphLink const& datagraph__);

    uniteConfig (::XSCRT::XML::Element< char > const&);
    uniteConfig (uniteConfig const& s);

    uniteConfig&
    operator= (uniteConfig const& s);

    private:
    char regulator__;
  };


  class logformatType : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    // value
    // 
    public:
    ::XMLSchema::string< char > const& value () const;
    void value (::XMLSchema::string< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::string< char > > value_;

    // relations
    // 
    public:
    bool relations_p () const;
    ::CUTS::relationList const& relations () const;
    void relations (::CUTS::relationList const& );

    protected:
    ::std::auto_ptr< ::CUTS::relationList > relations_;

    // id
    // 
    public:
    ::XMLSchema::ID< char > const& id () const;
    ::XMLSchema::ID< char >& id ();
    void id (::XMLSchema::ID< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::ID< char > > id_;

    public:
    logformatType (::XMLSchema::string< char > const& value__,
                   ::XMLSchema::ID< char > const& id__);

    logformatType (::XSCRT::XML::Element< char > const&);
    logformatType (logformatType const& s);

    logformatType&
    operator= (logformatType const& s);

    private:
    char regulator__;
  };


  class relationList : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    // relation
    // 
    public:
    typedef ::std::list< ::CUTS::relationType >::iterator relation_iterator;
    typedef ::std::list< ::CUTS::relationType >::const_iterator relation_const_iterator;
    relation_iterator begin_relation ();
    relation_iterator end_relation ();
    relation_const_iterator begin_relation () const;
    relation_const_iterator end_relation () const;
    void add_relation (::CUTS::relationType const& );
    size_t count_relation (void) const;

    protected:
    ::std::list< ::CUTS::relationType > relation_;

    public:
    relationList ();

    relationList (::XSCRT::XML::Element< char > const&);
    relationList (relationList const& s);

    relationList&
    operator= (relationList const& s);

    private:
    char regulator__;
  };


  class causalityType : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    // cause
    // 
    public:
    ::XMLSchema::string< char > const& cause () const;
    ::XMLSchema::string< char >& cause ();
    void cause (::XMLSchema::string< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::string< char > > cause_;

    // effect
    // 
    public:
    ::XMLSchema::string< char > const& effect () const;
    ::XMLSchema::string< char >& effect ();
    void effect (::XMLSchema::string< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::string< char > > effect_;

    public:
    causalityType (::XMLSchema::string< char > const& cause__,
                   ::XMLSchema::string< char > const& effect__);

    causalityType (::XSCRT::XML::Element< char > const&);
    causalityType (causalityType const& s);

    causalityType&
    operator= (causalityType const& s);

    private:
    char regulator__;
  };


  class relationType : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    // causality
    // 
    public:
    typedef ::std::list< ::CUTS::causalityType >::iterator causality_iterator;
    typedef ::std::list< ::CUTS::causalityType >::const_iterator causality_const_iterator;
    causality_iterator begin_causality ();
    causality_iterator end_causality ();
    causality_const_iterator begin_causality () const;
    causality_const_iterator end_causality () const;
    void add_causality (::CUTS::causalityType const& );
    size_t count_causality (void) const;

    protected:
    ::std::list< ::CUTS::causalityType > causality_;

    // effectref
    // 
    public:
    ::XMLSchema::NCName< char > const& effectref () const;
    ::XMLSchema::NCName< char >& effectref ();
    void effectref (::XMLSchema::NCName< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::NCName< char > > effectref_;

    public:
    relationType (::XMLSchema::NCName< char > const& effectref__);

    relationType (::XSCRT::XML::Element< char > const&);
    relationType (relationType const& s);

    relationType&
    operator= (relationType const& s);

    private:
    char regulator__;
  };


  class logformatList : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    // logformat
    // 
    public:
    typedef ::std::list< ::CUTS::logformatType >::iterator logformat_iterator;
    typedef ::std::list< ::CUTS::logformatType >::const_iterator logformat_const_iterator;
    logformat_iterator begin_logformat ();
    logformat_iterator end_logformat ();
    logformat_const_iterator begin_logformat () const;
    logformat_const_iterator end_logformat () const;
    void add_logformat (::CUTS::logformatType const& );
    size_t count_logformat (void) const;

    protected:
    ::std::list< ::CUTS::logformatType > logformat_;

    public:
    logformatList (::std::list< ::CUTS::logformatType > const& logformat__);

    logformatList (::XSCRT::XML::Element< char > const&);
    logformatList (logformatList const& s);

    logformatList&
    operator= (logformatList const& s);

    private:
    char regulator__;
  };


  class groupitemType : public ::XSCRT::Type
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

    public:
    groupitemType (::XMLSchema::string< char > const& name__);

    groupitemType (::XSCRT::XML::Element< char > const&);
    groupitemType (groupitemType const& s);

    groupitemType&
    operator= (groupitemType const& s);

    private:
    char regulator__;
  };


  class groupingType : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    // groupitem
    // 
    public:
    typedef ::std::list< ::CUTS::groupitemType >::iterator groupitem_iterator;
    typedef ::std::list< ::CUTS::groupitemType >::const_iterator groupitem_const_iterator;
    groupitem_iterator begin_groupitem ();
    groupitem_iterator end_groupitem ();
    groupitem_const_iterator begin_groupitem () const;
    groupitem_const_iterator end_groupitem () const;
    void add_groupitem (::CUTS::groupitemType const& );
    size_t count_groupitem (void) const;

    protected:
    ::std::list< ::CUTS::groupitemType > groupitem_;

    public:
    groupingType (::std::list< ::CUTS::groupitemType > const& groupitem__);

    groupingType (::XSCRT::XML::Element< char > const&);
    groupingType (groupingType const& s);

    groupingType&
    operator= (groupingType const& s);

    private:
    char regulator__;
  };


  class datagraphType : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    // name
    // 
    public:
    ::XMLSchema::string< char > const& name () const;
    void name (::XMLSchema::string< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::string< char > > name_;

    // logformats
    // 
    public:
    ::CUTS::logformatList const& logformats () const;
    void logformats (::CUTS::logformatList const& );

    protected:
    ::std::auto_ptr< ::CUTS::logformatList > logformats_;

    public:
    datagraphType (::XMLSchema::string< char > const& name__,
                   ::CUTS::logformatList const& logformats__);

    datagraphType (::XSCRT::XML::Element< char > const&);
    datagraphType (datagraphType const& s);

    datagraphType&
    operator= (datagraphType const& s);

    private:
    char regulator__;
  };


  class datagraphLink : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    // location
    // 
    public:
    ::XMLSchema::anyURI< char > const& location () const;
    ::XMLSchema::anyURI< char >& location ();
    void location (::XMLSchema::anyURI< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::anyURI< char > > location_;

    public:
    datagraphLink (::XMLSchema::anyURI< char > const& location__);

    datagraphLink (::XSCRT::XML::Element< char > const&);
    datagraphLink (datagraphLink const& s);

    datagraphLink&
    operator= (datagraphLink const& s);

    private:
    char regulator__;
  };
}

namespace CUTS
{
  namespace reader
  {
    ::CUTS::uniteConfig
    unite (xercesc::DOMDocument const*);
  }


  namespace reader
  {
    ::CUTS::datagraphType
    datagraph (xercesc::DOMDocument const*);
  }
}

#include "cuts-unite.inl"

#endif // CUTS_UNITE_H
