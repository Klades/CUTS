// -*- C++ -*-

//=============================================================================
/**
 *  @file         OpenSplice_EventConsumer_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_OPENSPLICE_CCM_EVENTCONSUMER_T_H_
#define _CUTS_OPENSPLICE_CCM_EVENTCONSUMER_T_H_

#include "cuts/arch/opensplice/OpenSplice_Traits_T.h"
#include "OpenSplice_EventConsumer.h"

template <typename SERVANT, typename EVENT>
class CUTS_OpenSplice_CCM_EventConsumer_T :
  public CUTS_OpenSplice_CCM_EventConsumer
{
public:
  /// Type definition of the servant type.
  typedef SERVANT servant_type;
  typedef EVENT event_type;

  typedef CUTS_OpenSplice_Traits_T <EVENT> traits_type;
  typedef typename traits_type::reader_type reader_type;
  typedef typename traits_type::reader_var_type reader_var_type;

  typedef void (*DESERIALIZE_METHOD) (SERVANT *, const EVENT &);

  /**
   * Initializing constructor.
   *
   * @param[in]         servant         The parent servant.
   * @param[in]         callback        Deserialized method on servant.
   */
  CUTS_OpenSplice_CCM_EventConsumer_T (SERVANT * servant,
                                       DESERIALIZE_METHOD callback);

  /// Destructor.
  virtual ~CUTS_OpenSplice_CCM_EventConsumer_T (void);

  virtual int configure (::DDS::Subscriber_ptr subscriber,
                         const char * inst,
                         const char * topic_name);

  /// Callback for notification of new data.
  virtual void on_data_available (::DDS::DataReader_ptr reader);

private:
  /// Servant to pass event.
  SERVANT * servant_;

  /// Method for deserializing an event.
  DESERIALIZE_METHOD callback_;

  /// The concrete reader for this consumer.
  reader_var_type reader_;
};

#include "OpenSplice_EventConsumer_T.cpp"

#endif  // !definef _CUTS_OPENSPLICE_EVENTCONSUMER_T_H_
