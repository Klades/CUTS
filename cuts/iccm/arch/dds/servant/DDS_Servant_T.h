// -*- C++ -*-

//=============================================================================
/**
 *  @file         DDS_Servant_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _ICCM_DDS_SERVANT_T_H_
#define _ICCM_DDS_SERVANT_T_H_

#include "cuts/iccm/servant/Servant_T.h"
#include "DDS_Servant.h"

namespace iCCM
{

/**
 * @class DDS_Servant_T
 *
 * Base type version of all DDS servants. It implements the default
 * behavior that all DDS servants are expected to implement.
 */
template <typename TRAIT, typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
class DDS_Servant_T :
  public Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, typename TRAIT::servant_type>
{
public:
  /// Type definition of the base type.
  typedef Servant_T <T,
                     CONTEXT,
                     EXECUTOR,
                     POA_EXEC,
                     typename TRAIT::servant_type> base_type;

  /**
   * Initializing constuctor.
   *
   * @param[in]       name              Name of the servant
   * @param[in]       port_poa          The POA for activating ports
   * @param[in]       impl              Reference to the implementation
   */
  DDS_Servant_T (T * _this,
                 const char * name,
                 ::PortableServer::POA_ptr port_poa,
                 typename EXECUTOR::_ptr_type impl);

  /// Destructor.
  virtual ~DDS_Servant_T (void);

  /// Configure the servant.
  virtual void configure (void);
  virtual void configure (const ::iccm::DomainParticipantQos & qos);

protected:
  virtual typename TRAIT::datawriter_ptr_type
    create_datawriter (const char * name,
                       const typename TRAIT::topicqos_type & topic_qos,
                       typename TRAIT::publisher_ptr_type publisher,
                       bool isprivate,
                       bool isinstance);

  virtual void
    configure_eventconsumer (const char * name,
                             const typename TRAIT::datareaderqos_type & qos,
                             const typename TRAIT::topicqos_type & topic_qos,
                             typename TRAIT::subscriber_ptr_type subscriber,
                             bool is_global);

  /// Type definition of the consumer map.
  typedef typename base_type::consumer_map_type consumer_map_type;

  /// Type definition of the emitter map.
  typedef typename base_type::emits_map_type emits_map_type;

  /// Type definition of the publisher map.
  typedef typename base_type::publishes_map_type publishes_map_type;
};

}

#if defined (__CUTS_INLINE__)
#include "DDS_Servant_T.inl"
#endif

#include "DDS_Servant_T.cpp"

#endif  // !defined _CUTS_OPENSPLICE_CCM_SERVANT_T_H_
