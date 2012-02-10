// -*- C++ -*-

//=============================================================================
/**
 *  @file         OpenSplice_Servant_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ICCM_OPENSPLICE_SERVANT_T_H_
#define _CUTS_ICCM_OPENSPLICE_SERVANT_T_H_

#include "ccm/CCM_EventsS.h"
#include "ccm/CCM_HomeS.h"
#include "ccm/CCM_EnumerationS.h"

#include "ace/Hash_Map_Manager.h"
#include "ace/RW_Thread_Mutex.h"
#include "ace/SString.h"

#include "cuts/iccm/servant/Servant_T.h"

#include "OpenSplice_Servant.h"
#include "OpenSplice_EventConsumer_T.h"
#include "OpenSplice_Publisher_T.h"
#include "OpenSplice_Publisher_Table_T.h"

namespace iccm
{
// Forward decl.
class DomainParticipantQos;
}

namespace iCCM
{

/**
 * @class OpenSplice_Servant_T
 */
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
class OpenSplice_Servant_T :
  public Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, OpenSplice_Servant>
{
public:
  /// Type definition of the base type.
  typedef Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, OpenSplice_Servant> base_type;

  /**
   * Initializing constuctor.
   *
   * @param[in]       name              Name of the servant
   * @param[in]       port_poa          The POA for activating ports
   * @param[in]       impl              Reference to the implementation
   */
  OpenSplice_Servant_T (T * _this,
                        const char * name,
                        ::PortableServer::POA_ptr port_poa,
                        typename EXECUTOR::_ptr_type impl);

  /// Destructor.
  virtual ~OpenSplice_Servant_T (void);

  /// Configure the servant.
  virtual void configure (void);
  virtual void configure (const ::iccm::DomainParticipantQos & qos);

protected:
  /// Do the default configuration.
  void do_default_configure (void);

  virtual ::DDS::DataWriter_ptr
    create_datawriter (const char * name,
                       const ::DDS::TopicQos & topic_qos,
                       ::DDS::Publisher_ptr publisher);

  virtual void
    configure_eventconsumer (const char * name,
                             const ::DDS::DataReaderQos & qos,
                             const ::DDS::TopicQos * topic_qos,
                             ::DDS::Subscriber_ptr publisher);

  /// Type definition of the consumer map.
  typedef typename base_type::consumer_map_type consumer_map_type;

  /// Type definition of the emitter map.
  typedef typename base_type::emits_map_type emits_map_type;

  /// Type definition of the publisher map.
  typedef typename base_type::publishes_map_type publishes_map_type;
};

}

#if defined (__CUTS_INLINE__)
#include "OpenSplice_Servant_T.inl"
#endif

#include "OpenSplice_Servant_T.cpp"

#endif  // !defined _CUTS_OPENSPLICE_CCM_SERVANT_T_H_
