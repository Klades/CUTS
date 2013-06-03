// -*- C++ -*-

//=============================================================================
/**
 *  @file         DDS_Publisher_Table.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _ICCM_DDS_PUBLISHER_TABLE_H_
#define _ICCM_DDS_PUBLISHER_TABLE_H_

#include "cuts/iccm/servant/Publisher_Table.h"

namespace iCCM
{

/**
 * @class DDS_Publisher_Table
 *
 * Template publisher
 */
template <typename T>
class DDS_Publisher_Table : public Publisher_Table
{
public:
  /// Type definition of the DDS entities.
  typedef typename T::publisher_ptr_type publisher_ptr_type;
  typedef typename T::publisher_ptr_type publisher_var_type;
  typedef typename T::topic_ptr_type topic_ptr_type;
  typedef typename T::topicqos_type topicqos_type;
  typedef typename T::datawriter_ptr_type datawriter_ptr_type;
  typedef typename T::datawriter_var_type datawriter_var_type;

  /// Default constructor.
  DDS_Publisher_Table (void);

  /// Destructor.
  virtual ~DDS_Publisher_Table (void);

  /**
   * Configure the publisher table. This means that all connections
   * in this table use the specified publisher.
   *
   * @param[in]         publisher         Target publisher
   * @param[in]         topic_name        Topic name for writer
   */
  virtual void configure (publisher_ptr_type publisher,
                          const topicqos_type & qos,
                          const char * topic_name,
                          bool isinstance) = 0;

  /// Get the publisher table data writer.
  datawriter_ptr_type get_datawriter (void);

  /// Test if the publisher table is configured.
  bool is_configured (void) const;

protected:
  /**
   * Helper method for configuring the publisher table.
   *
   * @param[in]         publisher         Target publisher
   * @param[in]         topic             Topic for writer
   */
  virtual void configure (publisher_ptr_type publisher,
                          topic_ptr_type topic);

  /// Abstract writer associated with the table.
  datawriter_var_type abs_writer_;
};

}

#if defined (__CUTS_INLINE__)
#include "DDS_Publisher_Table.inl"
#endif

#include "DDS_Publisher_Table.cpp"

#endif  // !defined _CUTS_OPENSPLICE_CCM_PUBLISHER_TABLE_H_
