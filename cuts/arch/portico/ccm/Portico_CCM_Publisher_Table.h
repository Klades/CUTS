// -*- C++ -*-

//=============================================================================
/**
 *  @file         Portico_Publisher_Table.h
 *
 *  Id: CCM_Publisher_Table.h.tmpl 3238 2011-12-07 04:12:45Z hillj Portico_Publisher_Table.h 3086 2011-01-22 05:53:51Z hillj
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _PORTICO_CCM_SUBSCRIBER_TABLE_H_
#define _PORTICO_CCM_SUBSCRIBER_TABLE_H_

#include "ace/UUID.h"
#include "cuts/arch/ccm/CCM_Publisher_Table.h"
#include "RTI.hh"

#include "Portico_CCM_export.h"

/**
 * @class Portico_CCM_Publisher_Table
 */
class PORTICO_CCM_Export Portico_CCM_Publisher_Table :
  public CUTS_CCM_Publisher_Table
{
public:
  /// Default constructor.
  Portico_CCM_Publisher_Table (void);

  /// Destructor.
  virtual ~Portico_CCM_Publisher_Table (void);

  /**
   * Initialize this publisher's handle.
   *
   * @param[in]           rtiamb            Pointer to the ambassador
   */
  virtual void init (RTI::RTIambassador * rtiamb) = 0;

  /// Finalized the publisher table.
  virtual void fini (void);

protected:
  /// Pointer to the ambassador.
  RTI::RTIambassador * rtiamb_;

  /// Object instance this table is publishing.
  RTI::ObjectHandle obj_handle_;

  /// Tag assigned to this publisher table.
  ACE_Utils::UUID tag_;
};

#if defined (__CUTS_INLINE__)
#include "Portico_CCM_Publisher_Table.inl"
#endif

#endif  // !defined _PORTICO_CCM_SUBSCRIBER_TABLE_H_
