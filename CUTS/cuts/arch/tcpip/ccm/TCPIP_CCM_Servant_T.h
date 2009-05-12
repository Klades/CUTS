// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_Servant_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_SERVANT_T_H_
#define _CUTS_TCPIP_CCM_SERVANT_T_H_

#include "ccm/CCM_EventsS.h"
#include "ccm/CCM_HomeS.h"
#include "ccm/CCM_EnumerationS.h"
#include "cuts/arch/tcpip/TCPIP_Servant_T.h"
#include "TCPIP_CCM_Servant.h"

// Forward decl.
class CUTS_TCPIP_Servant_Manager;

/**
 * @class CUTS_TCPIP_CCM_Events_Impl
 */
template <typename T, typename CTX, typename EXEC, typename POA_EXEC>
class CUTS_TCPIP_CCM_Servant_T :
  public POA_EXEC,
  public CUTS_TCPIP_CCM_Servant,
  public CUTS_TCPIP_Servant_T <T, CTX, EXEC>
{
protected:
  typedef CUTS_TCPIP_Servant_T <T, CTX, EXEC> base_type;

  CUTS_TCPIP_CCM_Servant_T (T * servant,
                            CUTS_TCPIP_Servant_Manager & svnt_mgr,
                            typename EXEC::_ptr_type executor);

public:

  virtual ~CUTS_TCPIP_CCM_Servant_T (void);

  virtual void activate_component (void);

  virtual void passivate_component (void);

  // event-related methods

  virtual ::Components::Cookie *
    subscribe (const char * publisher_name,
                ::Components::EventConsumerBase_ptr subscriber);

  virtual ::Components::EventConsumerBase_ptr
    unsubscribe (const char * publisher_name, ::Components::Cookie * ck);

  virtual Components::EventConsumerBase_ptr
    get_consumer (const char *);

  virtual void
    connect_consumer (const char *, Components::EventConsumerBase_ptr);

  virtual Components::EventConsumerBase_ptr
    disconnect_consumer (const char *);

  virtual Components::ConsumerDescriptions *
    get_all_consumers (void);

  virtual Components::ConsumerDescriptions *
    get_named_consumers (const Components::NameList &);

  virtual Components::EmitterDescriptions *
    get_all_emitters (void);

  virtual Components::EmitterDescriptions *
    get_named_emitters (const Components::NameList &);

  virtual Components::PublisherDescriptions *
    get_all_publishers (void);

  virtual Components::PublisherDescriptions *
    get_named_publishers (const Components::NameList &);

  // facet/receptacle methods

  ::CORBA::Object_ptr provide_facet (const char *);

  ::Components::FacetDescriptions * get_all_facets (void);

  ::Components::FacetDescriptions * get_named_facets (const Components::NameList &);

  ::Components::Cookie * connect (const char *, ::CORBA::Object_ptr);

  ::CORBA::Object_ptr disconnect (const char *, ::Components::Cookie *);

  ::Components::ConnectionDescriptions * get_connections (const char *);

  ::Components::ReceptacleDescriptions * get_all_receptacles (void);

  ::Components::ReceptacleDescriptions * get_named_receptacles (const Components::NameList &);

  // component-related methods
  ::CORBA::Boolean same_component (::CORBA::Object_ptr);

  ::CORBA::IRObject_ptr get_component_def (void);

  ::Components::CCMHome_ptr get_ccm_home (void);

  ::Components::PrimaryKeyBase * get_primary_key (void);

  virtual void configuration_complete (void);

  virtual void remove (void);

  ::Components::ComponentPortDescription * get_all_ports (void);

protected:
  CUTS_TCPIP_Servant_Manager & svnt_mgr_;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Servant_T.inl"
#endif

#include "TCPIP_CCM_Servant_T.cpp"

#endif  // !defined _CUTS_TCPIP_CCM_SERVANT_T_H_
