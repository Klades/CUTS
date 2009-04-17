// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_Servant_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _TCPIP_SERVANT_T_H_
#define _TCPIP_SERVANT_T_H_

#include "TCPIP_Servant.h"
#include "ace/Array.h"

/**
 * @class CUTS_TCPIP_Servant_T
 */
template <typename T>
class CUTS_TCPIP_Servant_T :
  public CUTS_TCPIP_Servant
{
public:
  /// Type definition of the servant type.
  typedef T servant_type;

  /// Type defintion of the pointer-to-member functions.
  typedef int (T::*method_type) (ACE_Message_Block & ev);

  /// Type definition of the dispatch table.
  typedef ACE_Array <method_type> jmptbl_type;

  // Method for handling the event. It will dispatch the events
  // to the correct method.
  virtual int handle_event (ACE_UINT32 id, ACE_Message_Block & ev);

protected:
  /**
   * Initializing constructor
   *
   * @param[in]           servant         Target servant.
   * @param[in]           vtable_size     Size of the jump table.
   */
  CUTS_TCPIP_Servant_T (T * servant, size_t vtable_size = 0);

  /// Destructor.
  virtual ~CUTS_TCPIP_Servant_T (void);

  /// Event dispatcher for the servant.
  jmptbl_type vtable_;

private:
  /// Pointer to the servant.
  T * servant_;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_Servant_T.inl"
#endif

#include "TCPIP_Servant_T.cpp"

#endif  // !defined _TCPIP_SERVANT_T_H_
