// -*- C++ -*-

//=============================================================================
/**
 *  @file         OpenSplice_Event_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_OPENSPLICE_EVENT_T_H_
#define _CUTS_OPENSPLICE_EVENT_T_H_

#include "cuts/config.h"

/**
 * @class CUTS_OpenSplice_Upcall_Event_T
 *
 * Wrapper class for sending a DDS event from a servant to the implementation.
 * This class stores a reference to the DDS event so it is not necessary to
 * create a duplicate copy of the DDS event in the CORBA event.
 */
template <typename EVENT, typename DDS_EVENT>
class CUTS_OpenSplice_Upcall_Event_T : public EVENT
{
public:
  /// Type definition of the CORBA event type.
  typedef EVENT event_type;

  /// Type definition of the DDS event type.
  typedef DDS_EVENT dds_event_type;

  /**
   * Initializing constructor.
   *
   * @param[in]       dds_event         The target DDS event
   */
  CUTS_OpenSplice_Upcall_Event_T (DDS_EVENT & dds_event);

  /// Destructor.
  virtual ~CUTS_OpenSplice_Upcall_Event_T (void);

  virtual void content (const DDS_EVENT & content);
  virtual const DDS_EVENT & content (void) const;
  virtual DDS_EVENT & content (void);

private:
  /// The contained DDS event object.
  DDS_EVENT & content_;
};

#if defined (__CUTS_INLINE__)
#include "OpenSplice_Event_T.inl"
#endif

#include "OpenSplice_Event_T.cpp"

#endif
