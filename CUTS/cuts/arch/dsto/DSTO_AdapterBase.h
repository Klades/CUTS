#ifndef DSTO_ADAPTERBASE_H
#define DSTO_ADAPTERBASE_H

#include "ccm/CCM_ObjectS.h"

#include "ciao/Containers/Container_BaseC.h"

#include "DSTO_Utilities_export.h"

namespace DSTO
{
  class DSTO_Utilities_Export AdapterBase
    : public virtual POA_Components::CCMObject
  {
  protected:
    AdapterBase (const char * instance_name,
                 ::CIAO::Container_ptr container);
    ~AdapterBase (void);
    
  public:
    virtual ::CORBA::IRObject_ptr get_component_def (void);
    virtual ::Components::CCMHome_ptr get_ccm_home (void);
    virtual ::Components::PrimaryKeyBase * get_primary_key (void);
    virtual Components::SessionComponent_ptr get_executor (void);
    virtual void configuration_complete (void);
    virtual void remove (void);
    virtual ::Components::ComponentPortDescription * get_all_ports (void);
    virtual ::Components::EventConsumerBase_ptr get_consumer (
      const char *sink_name);
    virtual ::Components::Cookie * subscribe (
      const char * publisher_name,
      ::Components::EventConsumerBase_ptr subscriber);
    virtual ::Components::EventConsumerBase_ptr unsubscribe (
      const char * publisher_name,
      ::Components::Cookie * ck);
    virtual void connect_consumer (
      const char * emitter_name,
      ::Components::EventConsumerBase_ptr consumer);
    virtual ::Components::EventConsumerBase_ptr disconnect_consumer (
      const char * source_name);
    virtual ::Components::ConsumerDescriptions * get_all_consumers (void);
    virtual ::Components::ConsumerDescriptions * get_named_consumers (
      const ::Components::NameList & names);
    virtual ::Components::EmitterDescriptions * get_all_emitters (void);
    virtual ::Components::EmitterDescriptions * get_named_emitters (
      const ::Components::NameList & names);
    virtual ::Components::PublisherDescriptions * get_all_publishers (void);
    virtual ::Components::PublisherDescriptions * get_named_publishers (
      const ::Components::NameList & names);
    virtual CORBA::Object_ptr provide_facet (const char * name);
    virtual ::Components::FacetDescriptions * get_all_facets (void);
    virtual ::Components::FacetDescriptions * get_named_facets (
      const ::Components::NameList & names);
    virtual ::CORBA::Boolean same_component (
      ::CORBA::Object_ptr object_ref);
    virtual ::Components::Cookie * connect (
      const char * name,
      ::CORBA::Object_ptr connection);
    virtual ::CORBA::Object_ptr disconnect (
      const char * name,
      ::Components::Cookie * ck);
    virtual ::Components::ConnectionDescriptions * get_connections (
      const char * name);
    virtual ::Components::ReceptacleDescriptions * get_all_receptacles (void);
    virtual ::Components::ReceptacleDescriptions * get_named_receptacles (
      const ::Components::NameList & names);
      
    // CIAO-specific, needed to compile template instantiation of
    // port activator.  
    ::CORBA::Object_ptr
    get_facet_executor (const char *name);
    
  protected:
    void add_consumer (const char * port_name,
                       ::Components::EventConsumerBase_ptr port_ref);

    ::Components::EventConsumerBase_ptr lookup_consumer (
      const char * port_name);

    ::Components::ConsumerDescription *lookup_consumer_description (
      const char * port_name);

  protected:
    typedef
    ACE_Array_Map<ACE_CString,
                  ::Components::ConsumerDescription_var>
      ConsumerTable;
      
    ConsumerTable consumer_table_;
      
    ACE_CString ins_name_;
    ::CIAO::Container_var container_;

  private:
    /// For internal locking of table reads and writes.
    TAO_SYNCH_MUTEX lock_;
  };
}

#endif // DSTO_ADAPTERBASE_H