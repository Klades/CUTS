// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_Servant_VTable_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_SERVANT_VTABLE_T_H_
#define _CUTS_TCPIP_SERVANT_VTABLE_T_H_

#include "ace/Array_Base.h"
#include "ace/Thread_Mutex.h"
#include "cuts/config.h"

// Forward decl.
template <typename T>
class CUTS_TCPIP_Servant_VTable_Init_Guard_T;

// Forward decl.
class CUTS_TCPIP_InputCDR;

/**
 * @class CUTS_TCPIP_Servant_VTable_T
 */
template <typename T>
class CUTS_TCPIP_Servant_VTable_T
{
public:
  // Friend decl.
  friend class CUTS_TCPIP_Servant_VTable_Init_Guard_T <T>;

  /// Type definition of the initialization guard.
  typedef CUTS_TCPIP_Servant_VTable_Init_Guard_T <T> init_guard_type;

  /// Type definition of the servant type.
  typedef T servant_type;

  /// Type defintion of the pointer-to-member functions.
  typedef int (* method_type) (T *, CUTS_TCPIP_InputCDR & input);

  /// Default constructor.
  CUTS_TCPIP_Servant_VTable_T (void);

  /// Destructor.
  ~CUTS_TCPIP_Servant_VTable_T (void);

  method_type & operator [] (size_t index);

  const method_type & operator [] (size_t index) const;

  bool is_init (void) const;

  size_t size (void) const;

private:
  /// Lock for initializing the virtual table.
  ACE_Thread_Mutex lock_;

  /// Type definition of the virtual table.
  typedef ACE_Array_Base <method_type> vtable_type;

  /// Implementation of the virtual table.
  vtable_type vtable_;

  bool is_init_;
};

/**
 * @class CUTS_TCPIP_Servant_VTable_Init_Guard_T
 */
template <typename T>
class CUTS_TCPIP_Servant_VTable_Init_Guard_T
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]         vtable        Target virtual table
   * @param[in]         size          Size of the virtual table.
   */
  CUTS_TCPIP_Servant_VTable_Init_Guard_T (CUTS_TCPIP_Servant_VTable_T <T> & vtable,
                                          size_t n);

  /// Destructor.
  ~CUTS_TCPIP_Servant_VTable_Init_Guard_T (void);

private:
  /// Virtual table that guard is associated with.
  CUTS_TCPIP_Servant_VTable_T <T> & vtable_;

  /// Size of the virtual table.
  size_t size_;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_Servant_VTable_T.inl"
#endif

#include "TCPIP_Servant_VTable_T.cpp"

#endif  // !defined _CUTS_TCPIP_SERVANT_VTABLE_T_H_
