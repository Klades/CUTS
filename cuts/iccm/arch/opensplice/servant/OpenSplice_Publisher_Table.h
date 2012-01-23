// -*- C++ -*-

//=============================================================================
/**
 *  @file         OpenSplice_Publisher_Table.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _ICCM_OPENSPLICE_PUBLISHER_TABLE_H_
#define _ICCM_OPENSPLICE_PUBLISHER_TABLE_H_

#include "cuts/iccm/servant/Publisher_Table.h"
#include "OpenSplice_svnt_export.h"

#include "ccpp_dds_dcps.h"

namespace iCCM
{

/**
 * @class OpenSplice_Publisher_Table
 */
class ICCM_OPENSPLICE_SVNT_Export OpenSplice_Publisher_Table :
  public Publisher_Table
{
public:
  /// Default constructor.
  OpenSplice_Publisher_Table (void);

  /// Destructor.
  virtual ~OpenSplice_Publisher_Table (void);

  /**
   * Configure the publisher table. This means that all connections
   * in this table use the specified publisher.
   *
   * @param[in]         publisher         Target publisher
   * @param[in]         topic_name        Topic name for writer
   */
  virtual void configure (::DDS::Publisher_ptr publisher,
                          const ACE_CString & topic_name) = 0;

protected:
  /**
   * Helper method for configuring the publisher table.
   *
   * @param[in]         publisher         Target publisher
   * @param[in]         topic             Topic for writer
   */
  virtual void configure (::DDS::Publisher_ptr publisher,
                          ::DDS::Topic_ptr topic);

  /// Publisher assigned to this table.
  ::DDS::Publisher_var publisher_;

  /// Abstract writer associated with the table.
  ::DDS::DataWriter_var abstract_writer_;
};

}

#if defined (__CUTS_INLINE__)
#include "OpenSplice_Publisher_Table.inl"
#endif

#endif  // !defined _CUTS_OPENSPLICE_CCM_PUBLISHER_TABLE_H_
