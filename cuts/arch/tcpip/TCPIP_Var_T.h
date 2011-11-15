// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_SPEC.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_VAR_T_H_
#define _CUTS_TCPIP_VAR_T_H_

#include "cuts/config.h"

/**
 * @class CUTS_TCPIP_Var_T
 */
template <typename T>
class CUTS_TCPIP_Var_T
{
public:
  /// Default constructor.
  CUTS_TCPIP_Var_T (void);

  /**
   * Initializing constructor.
   */
  CUTS_TCPIP_Var_T (T * ptr);

  /**
   * Copy constructor.
   */
  CUTS_TCPIP_Var_T (const CUTS_TCPIP_Var_T & copy);

  /// Destructor.
  ~CUTS_TCPIP_Var_T (void);

  /**
   * Assignment operator. This version of the assignment operator
   * will take ownership of the \a ptr object. It will not increment
   * the reference count of \ptr.
   *
   * @param[in]       ptr         Pointer to the object.
   */
  const CUTS_TCPIP_Var_T & operator = (T * ptr);

  /**
   * Assignment operator. This version of the assignment operator
   * will increment/decrement the reference count accordingly.
   *
   * @param[in]       rhs         Right-hand side of operator
   */
  const CUTS_TCPIP_Var_T & operator = (const CUTS_TCPIP_Var_T & rhs);

  T * operator -> (void);

  const T * operator -> (void) const;

  T & operator * (void);

  const T & operator * (void) const;

  operator T * (void);
  operator const T * (void) const;

  T * _retn (void);

private:
  /// Pointer to the variable.
  T * ptr_;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_Var_T.inl"
#endif

#include "TCPIP_Var_T.cpp"

#endif  // !defined _CUTS_TCPIP_VAR_T_H_
