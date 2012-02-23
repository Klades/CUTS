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

#include "cuts/iccm/arch/dds/servant/DDS_Publisher_Table_T.h"
#include "OpenSplice.h"

namespace iCCM
{

/**
 * @class OpenSplice_Publisher_Table_T
 *
 * Template version of the publisher table for OpenSplice.
 */
template <typename EVENT>
class OpenSplice_Publisher_Table_T :
  public DDS_Publisher_Table_T <OpenSplice, EVENT>
{
public:
  /// Default constructor.
  OpenSplice_Publisher_Table_T (void);

  /// Destructor.
  virtual ~OpenSplice_Publisher_Table_T (void);
};

}

#include "OpenSplice_Publisher_Table_T.cpp"

#endif  // !defined _CUTS_OPENSPLICE_CCM_PUBLISHER_TABLE_T_H_
