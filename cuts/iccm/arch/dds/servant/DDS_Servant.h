// -*- C++ -*-

//=============================================================================
/**
 *  @file         DDS_Servant.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _ICCM_DDS_SERVANT_H_
#define _ICCM_DDS_SERVANT_H_

#include "cuts/iccm/servant/Servant.h"

namespace iccm
{
  class DomainParticipantQos;
}

namespace iCCM
{

/**
 * @class DDS_Servant
 *
 * Base class for all DDS servant objects. This class enables the container
 * to send commands to the servant, such as configuration information for
 * each of its topics.
 */
template <typename T>
class DDS_Servant : public Servant
{
public:
  typedef typename T::corba_poa_eventconsumer_type corba_poa_eventconsumer_type;
  typedef typename T::eventconsumer_type eventconsumer_type;
  typedef typename T::publisher_type publisher_type;
  typedef typename T::publisher_table_type publisher_table_type;

  typedef typename T::domainparticipant_var_type domainparticipant_var_type;
  typedef typename T::datawriter_ptr_type datawriter_ptr_type;
  typedef typename T::datareaderqos_type datareaderqos_type;
  typedef typename T::topicqos_type topicqos_type;
  typedef typename T::subscriber_ptr_type subscriber_ptr_type;
  typedef typename T::subscriber_var_type subscriber_var_type;
  typedef typename T::publisher_ptr_type publisher_ptr_type;
  typedef typename T::publisher_var_type publisher_var_type;

  /// Destructor.
  virtual ~DDS_Servant (void);

  /// Perform default configuration.
  virtual void configure (void);

  /**
   * Configure the servant with Qos properties. Each DDS implementation
   * must implement this method since (1) each has their on nomenclature
   * and (2) we want to hide all usage of XML and XSC, which is used by
   * the DDS configuration.
   *
   * @param[in]       qos         Qos configuration
   */
  virtual void configure (const ::iccm::DomainParticipantQos & qos) = 0;

protected:
  /// Default constructor.
  DDS_Servant (const char * name);

  /// Do the default configuration.
  void do_default_configure (void);

  /// Create a data writer object.
  virtual datawriter_ptr_type
    create_datawriter (const char * name,
                       const char * topic_name,
                       const topicqos_type & topic_qos,
                       publisher_ptr_type publisher,
                       bool isprivate,
                       bool isinstance) = 0;

  /// Configure the event consumer for future data readers.
  virtual void
    configure_eventconsumer (const char * name,
                             const datareaderqos_type * qos,
                             const topicqos_type * topic_qos,
                             subscriber_ptr_type publisher,
                             bool is_global) = 0;

  /// The domain participant for the servant.
  domainparticipant_var_type participant_;

  /// The publisher for the servant.
  publisher_var_type publisher_;

  /// The subscriber for the servant.
  subscriber_var_type subscriber_;

  /// Collection of non-default publishers for this servant.
  ACE_Hash_Map_Manager <ACE_CString,
                        publisher_var_type,
                        ACE_Null_Mutex> publishers_;

  /// Collection of non-default subscribers.
  ACE_Hash_Map_Manager <ACE_CString,
                        subscriber_var_type,
                        ACE_Null_Mutex> subscribers_;

  /// Collection of topic QoS entities.
  ACE_Hash_Map_Manager <ACE_CString,
                        topicqos_type *,
                        ACE_Null_Mutex> topic_qos_;

  /// Collection of datareader QoS entities
  ACE_Hash_Map_Manager <ACE_CString,
                        datareaderqos_type *,
                        ACE_Null_Mutex> datareader_qos_;
};

}

#if defined (__CUTS_INLINE__)
#include "DDS_Servant.inl"
#endif

#include "DDS_Servant.cpp"

#endif  // !defined _CUTS_OPENSPLICE_CCM_SERVANT_H_
