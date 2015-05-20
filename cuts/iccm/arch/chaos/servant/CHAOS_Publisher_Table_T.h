// -*- C++ -*-

//=============================================================================
/**
 *  @file         CHAOS_Publisher_Table_T.h
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

#ifndef _ICCM_CHAOS_PUBLISHER_TABLE_T_H_
#define _ICCM_CHAOS_PUBLISHER_TABLE_T_H_

#include "cuts/iccm/servant/Publisher_Table_T.h"

#include "CHAOS_Publisher_Table.h"
#include "CHAOS_Publisher_T.h"

namespace iCCM
{

/**
 * @class CHAOS_Publisher_Table_T
 */
template <typename EVENT>
class CHAOS_Publisher_Table_T :
  public Publisher_Table_T < CHAOS_Publisher_Table, CHAOS_Publisher_T <EVENT>, true >
{
public:
  /// Type definition of the base type.
  typedef Publisher_Table_T < CHAOS_Publisher_Table,
                              CHAOS_Publisher_T <EVENT>,
                              true > base_type;

  /// Default constructor.
  CHAOS_Publisher_Table_T (void);

  /// Destructor.
  virtual ~CHAOS_Publisher_Table_T (void);

  /// Send an event.
  virtual void send_event (EVENT * ev);

  /// Allocate a new event.
  virtual EVENT * allocate_event (void);
};

}

#include "CHAOS_Publisher_Table_T.cpp"

#endif  // !defined _ICCM_CHAOS_PUBLISHER_TABLE_T_H_
