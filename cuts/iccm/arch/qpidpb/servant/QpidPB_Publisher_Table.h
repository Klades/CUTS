// -*- C++ -*-

//=============================================================================
/**
 *  @file         QpidPB_Publisher_Table.h
 *
 *  $Id$
 *
 *  Code generated by iCCM skeleton project generator that is include
 *  in the CUTS (http://cuts.cs.iupui.edu) and developed by:
 *
 *      Software Engineering & Distributed System (SEDS) Group
 *      Indiana Univesity-Purdue University Indianapolis
 *      Indianapolis, IN 46202
 */
//=============================================================================

#ifndef _ICCM_QPIDPB_PUBLISHER_TABLE_H_
#define _ICCM_QPIDPB_PUBLISHER_TABLE_H_

#include "cuts/iccm/servant/Publisher_Table.h"

#ifdef _WIN32
  #undef max
  #undef min
#endif
#include "qpid/client/Connection.h"

#include "QpidPB_svnt_export.h"

namespace iCCM
{

/**
 * @class QpidPB_Publisher_Table
 */
class ICCM_QPIDPB_SVNT_Export QpidPB_Publisher_Table :
  public Publisher_Table
{
public:
  /// Default constructor.
  QpidPB_Publisher_Table (void);

  /// Destructor.
  virtual ~QpidPB_Publisher_Table (void);

  virtual void activate (void);
  virtual void passivate (void);

  virtual void configure_broker (const std::string & host, int port);
  virtual void queue (const std::string & queue);

protected:
  /// The qpid broker information
  std::string host_;
  int port_;
  std::string queue_;

  /// The qpid connection
  qpid::client::Connection connection_;
};

}

#if defined (__CUTS_INLINE__)
#include "QpidPB_Publisher_Table.inl"
#endif

#endif  // !defined _ICCM_QPIDPB_PUBLISHER_TABLE_H_
