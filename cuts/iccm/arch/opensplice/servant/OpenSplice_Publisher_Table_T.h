// -*- C++ -*-

//=============================================================================
/**
 *  @file         OpenSplice_Publisher_Table_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ICCM_OPENSPLICE_PUBLISHER_TABLE_T_H_
#define _CUTS_ICCM_OPENSPLICE_PUBLISHER_TABLE_T_H_

#include "cuts/iccm/servant/Publisher_Table_T.h"

#include "OpenSplice_Publisher_Table.h"
#include "OpenSplice_Publisher_T.h"

namespace iCCM
{

/**
 * @class OpenSplice_Publisher_Table_T
 */
template <typename EVENT>
class OpenSplice_Publisher_Table_T :
  public Publisher_Table_T < OpenSplice_Publisher_Table, OpenSplice_Publisher_T <EVENT>, false >
{
public:
  /// Type definition of the base type.
  typedef Publisher_Table_T < OpenSplice_Publisher_Table,
                              OpenSplice_Publisher_T <EVENT>,
                              false> base_type;

  /// Type definition of the traits for this object.
  typedef OpenSplice_Traits_T <EVENT> traits_type;

  /// Default constructor.
  OpenSplice_Publisher_Table_T (void);

  /// Destructor.
  virtual ~OpenSplice_Publisher_Table_T (void);

  /**
   * Configure the publisher table. This means that all connections
   * in this table use the specified publisher.
   *
   * @param[in]         publisher         Target publisher
   * @param[in]         topic_name        Topic name for writer
   */
  virtual void configure (::DDS::Publisher_ptr publisher, const ACE_CString & topic_name);

  /**
   * Subscribe an event consumer.
   */
  virtual ::Components::Cookie * subscribe (::Components::EventConsumerBase_ptr);

  /**
   * Unsubscribe an event consumer.
   */
  virtual ::Components::EventConsumerBase_ptr unsubscribe (::Components::Cookie *);

  /// Send an event.
  void send_event (EVENT * ev);

  EVENT * allocate_event (void);

protected:
  /// Type specific writer for the publisher.
  typename traits_type::writer_type_var writer_;
};

}

#include "OpenSplice_Publisher_Table_T.cpp"

#endif  // !defined _CUTS_OPENSPLICE_CCM_PUBLISHER_TABLE_T_H_
