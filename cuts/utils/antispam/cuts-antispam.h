#ifndef CUTS_ANTISPAM_H
#define CUTS_ANTISPAM_H

// Forward declarations.
//
namespace CUTS
{
  class antispamConfig;
  class componentList;
  class inputType;
  class componentType;
  class assemblyType;
  class instanceInputType;
  class instanceType;
  class connectionType;
  class deploymentType;
  class hostType;
}

#include <memory>
#include <list>
#include "XMLSchema/Types.hpp"

namespace CUTS
{
  class antispamConfig : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    // components
    // 
    public:
    bool components_p () const;
    ::CUTS::componentList const& components () const;
    void components (::CUTS::componentList const& );

    protected:
    ::std::auto_ptr< ::CUTS::componentList > components_;

    // assembly
    // 
    public:
    bool assembly_p () const;
    ::CUTS::assemblyType const& assembly () const;
    void assembly (::CUTS::assemblyType const& );

    protected:
    ::std::auto_ptr< ::CUTS::assemblyType > assembly_;

    // deployment
    // 
    public:
    bool deployment_p () const;
    ::CUTS::deploymentType const& deployment () const;
    void deployment (::CUTS::deploymentType const& );

    protected:
    ::std::auto_ptr< ::CUTS::deploymentType > deployment_;

    public:
    antispamConfig ();

    antispamConfig (::XSCRT::XML::Element< char > const&);
    antispamConfig (antispamConfig const& s);

    antispamConfig&
    operator= (antispamConfig const& s);

    private:
    char regulator__;
  };


  class componentList : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    // component
    // 
    public:
    typedef ::std::list< ::CUTS::componentType >::iterator component_iterator;
    typedef ::std::list< ::CUTS::componentType >::const_iterator component_const_iterator;
    component_iterator begin_component ();
    component_iterator end_component ();
    component_const_iterator begin_component () const;
    component_const_iterator end_component () const;
    void add_component (::CUTS::componentType const& );
    size_t count_component (void) const;

    protected:
    ::std::list< ::CUTS::componentType > component_;

    public:
    componentList ();

    componentList (::XSCRT::XML::Element< char > const&);
    componentList (componentList const& s);

    componentList&
    operator= (componentList const& s);

    private:
    char regulator__;
  };


  class inputType : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    // output
    // 
    public:
    typedef ::std::list< ::XMLSchema::string< char > >::iterator output_iterator;
    typedef ::std::list< ::XMLSchema::string< char > >::const_iterator output_const_iterator;
    output_iterator begin_output ();
    output_iterator end_output ();
    output_const_iterator begin_output () const;
    output_const_iterator end_output () const;
    void add_output (::XMLSchema::string< char > const& );
    size_t count_output (void) const;

    protected:
    ::std::list< ::XMLSchema::string< char > > output_;

    // name
    // 
    public:
    ::XMLSchema::string< char > const& name () const;
    ::XMLSchema::string< char >& name ();
    void name (::XMLSchema::string< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::string< char > > name_;

    public:
    inputType (::XMLSchema::string< char > const& name__);

    inputType (::XSCRT::XML::Element< char > const&);
    inputType (inputType const& s);

    inputType&
    operator= (inputType const& s);

    private:
    char regulator__;
  };


  class componentType : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    // input
    // 
    public:
    typedef ::std::list< ::CUTS::inputType >::iterator input_iterator;
    typedef ::std::list< ::CUTS::inputType >::const_iterator input_const_iterator;
    input_iterator begin_input ();
    input_iterator end_input ();
    input_const_iterator begin_input () const;
    input_const_iterator end_input () const;
    void add_input (::CUTS::inputType const& );
    size_t count_input (void) const;

    protected:
    ::std::list< ::CUTS::inputType > input_;

    // type
    // 
    public:
    ::XMLSchema::string< char > const& type () const;
    ::XMLSchema::string< char >& type ();
    void type (::XMLSchema::string< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::string< char > > type_;

    public:
    componentType (::XMLSchema::string< char > const& type__);

    componentType (::XSCRT::XML::Element< char > const&);
    componentType (componentType const& s);

    componentType&
    operator= (componentType const& s);

    private:
    char regulator__;
  };


  class assemblyType : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    // instance
    // 
    public:
    typedef ::std::list< ::CUTS::instanceType >::iterator instance_iterator;
    typedef ::std::list< ::CUTS::instanceType >::const_iterator instance_const_iterator;
    instance_iterator begin_instance ();
    instance_iterator end_instance ();
    instance_const_iterator begin_instance () const;
    instance_const_iterator end_instance () const;
    void add_instance (::CUTS::instanceType const& );
    size_t count_instance (void) const;

    protected:
    ::std::list< ::CUTS::instanceType > instance_;

    // connection
    // 
    public:
    typedef ::std::list< ::CUTS::connectionType >::iterator connection_iterator;
    typedef ::std::list< ::CUTS::connectionType >::const_iterator connection_const_iterator;
    connection_iterator begin_connection ();
    connection_iterator end_connection ();
    connection_const_iterator begin_connection () const;
    connection_const_iterator end_connection () const;
    void add_connection (::CUTS::connectionType const& );
    size_t count_connection (void) const;

    protected:
    ::std::list< ::CUTS::connectionType > connection_;

    public:
    assemblyType ();

    assemblyType (::XSCRT::XML::Element< char > const&);
    assemblyType (assemblyType const& s);

    assemblyType&
    operator= (assemblyType const& s);

    private:
    char regulator__;
  };


  class instanceInputType : public ::XSCRT::Type
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

    // baseline
    // 
    public:
    ::XMLSchema::double_ const& baseline () const;
    ::XMLSchema::double_& baseline ();
    void baseline (::XMLSchema::double_ const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::double_ > baseline_;

    // arrival
    // 
    public:
    bool arrival_p () const;
    ::XMLSchema::double_ const& arrival () const;
    ::XMLSchema::double_& arrival ();
    void arrival (::XMLSchema::double_ const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::double_ > arrival_;

    public:
    instanceInputType (::XMLSchema::string< char > const& name__,
                       ::XMLSchema::double_ const& baseline__);

    instanceInputType (::XSCRT::XML::Element< char > const&);
    instanceInputType (instanceInputType const& s);

    instanceInputType&
    operator= (instanceInputType const& s);

    private:
    char regulator__;
  };


  class instanceType : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    // input
    // 
    public:
    typedef ::std::list< ::CUTS::instanceInputType >::iterator input_iterator;
    typedef ::std::list< ::CUTS::instanceInputType >::const_iterator input_const_iterator;
    input_iterator begin_input ();
    input_iterator end_input ();
    input_const_iterator begin_input () const;
    input_const_iterator end_input () const;
    void add_input (::CUTS::instanceInputType const& );
    size_t count_input (void) const;

    protected:
    ::std::list< ::CUTS::instanceInputType > input_;

    // type
    // 
    public:
    ::XMLSchema::string< char > const& type () const;
    ::XMLSchema::string< char >& type ();
    void type (::XMLSchema::string< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::string< char > > type_;

    // name
    // 
    public:
    ::XMLSchema::string< char > const& name () const;
    ::XMLSchema::string< char >& name ();
    void name (::XMLSchema::string< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::string< char > > name_;

    public:
    instanceType (::XMLSchema::string< char > const& type__,
                  ::XMLSchema::string< char > const& name__);

    instanceType (::XSCRT::XML::Element< char > const&);
    instanceType (instanceType const& s);

    instanceType&
    operator= (instanceType const& s);

    private:
    char regulator__;
  };


  class connectionType : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    // src
    // 
    public:
    ::XMLSchema::string< char > const& src () const;
    ::XMLSchema::string< char >& src ();
    void src (::XMLSchema::string< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::string< char > > src_;

    // dst
    // 
    public:
    ::XMLSchema::string< char > const& dst () const;
    ::XMLSchema::string< char >& dst ();
    void dst (::XMLSchema::string< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::string< char > > dst_;

    public:
    connectionType (::XMLSchema::string< char > const& src__,
                    ::XMLSchema::string< char > const& dst__);

    connectionType (::XSCRT::XML::Element< char > const&);
    connectionType (connectionType const& s);

    connectionType&
    operator= (connectionType const& s);

    private:
    char regulator__;
  };


  class deploymentType : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    // host
    // 
    public:
    typedef ::std::list< ::CUTS::hostType >::iterator host_iterator;
    typedef ::std::list< ::CUTS::hostType >::const_iterator host_const_iterator;
    host_iterator begin_host ();
    host_iterator end_host ();
    host_const_iterator begin_host () const;
    host_const_iterator end_host () const;
    void add_host (::CUTS::hostType const& );
    size_t count_host (void) const;

    protected:
    ::std::list< ::CUTS::hostType > host_;

    public:
    deploymentType ();

    deploymentType (::XSCRT::XML::Element< char > const&);
    deploymentType (deploymentType const& s);

    deploymentType&
    operator= (deploymentType const& s);

    private:
    char regulator__;
  };


  class hostType : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    // instance
    // 
    public:
    typedef ::std::list< ::XMLSchema::string< char > >::iterator instance_iterator;
    typedef ::std::list< ::XMLSchema::string< char > >::const_iterator instance_const_iterator;
    instance_iterator begin_instance ();
    instance_iterator end_instance ();
    instance_const_iterator begin_instance () const;
    instance_const_iterator end_instance () const;
    void add_instance (::XMLSchema::string< char > const& );
    size_t count_instance (void) const;

    protected:
    ::std::list< ::XMLSchema::string< char > > instance_;

    // name
    // 
    public:
    ::XMLSchema::string< char > const& name () const;
    ::XMLSchema::string< char >& name ();
    void name (::XMLSchema::string< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::string< char > > name_;

    public:
    hostType (::XMLSchema::string< char > const& name__);

    hostType (::XSCRT::XML::Element< char > const&);
    hostType (hostType const& s);

    hostType&
    operator= (hostType const& s);

    private:
    char regulator__;
  };
}

namespace CUTS
{
  namespace reader
  {
    ::CUTS::antispamConfig
    antispam (xercesc::DOMDocument const*);
  }
}

#include "cuts-antispam.inl"

#endif // CUTS_ANTISPAM_H
