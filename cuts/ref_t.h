// -*- C++ -*-

//=============================================================================
/**
 * @file        ref_t.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_REF_T_H_
#define _CUTS_REF_T_H_

#include "value_of_t.h"

//=============================================================================
/**
 * @class CUTS_ref_t
 *
 * Wrapper class for a reference object.
 */
//=============================================================================

template <typename T>
class CUTS_ref_t
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       ref       Target object to reference.
   */
  CUTS_ref_t (T & ref);

  /**
   * Copy constructor.
   *
   * @param[in]       ref       Target object to reference.
   */
  CUTS_ref_t (const CUTS_ref_t & ref);

  /// Destructor.
  ~CUTS_ref_t (void);

  /**
   * Assignment operator.
   *
   * @param[in]       rhs       Right-hand side of the operator.
   */
  const CUTS_ref_t & operator = (const CUTS_ref_t & rhs);

  /**
   * Convert the object to a reference of type T.
   *
   * @return          This object as a reference.
   */
  operator T & (void) const;

private:
  /// Reference to the object.
  T & ref_;
};

/**
 * Factory for the CUTS_ref_t object.
 *
 * @param[in]       ref         Target reference object.
 * @return          Reference object in a wrapper object.
 */
template <typename T>
CUTS_ref_t <T> CUTS_ref (T & ref);

template <typename T>
T & CUTS_value_of (const CUTS_ref_t <T> & t);

//=============================================================================
/**
 * @class CUTS_cref_t
 *
 * Wrapper class for a reference object.
 */
//=============================================================================

template <typename T>
class CUTS_cref_t
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       ref       Target object to reference.
   */
  CUTS_cref_t (const T & ref);

  /**
   * Copy constructor.
   *
   * @param[in]       ref       Target object to reference.
   */
  CUTS_cref_t (const CUTS_cref_t & ref);

  /// Destructor.
  ~CUTS_cref_t (void);

  /**
   * Assignment operator.
   *
   * @param[in]       rhs       Right-hand side of the operator.
   */
  const CUTS_cref_t & operator = (const CUTS_cref_t & rhs);

  /**
   * Convert the object to a reference of type T.
   *
   * @return          This object as a reference.
   */
  operator const T & (void) const;

private:
  /// Reference to the object.
  const T & cref_;
};

/**
 * Factory for the CUTS_cref_t object.
 *
 * @param[in]       ref         Target reference object.
 * @return          Reference object in a wrapper object.
 */
template <typename T>
CUTS_cref_t <T> CUTS_cref (const T & ref);

template <typename T>
const T & CUTS_value_of (const CUTS_cref_t <T> & t);

#if defined (__CUTS_INLINE__)
#include "ref_t.inl"
#endif

#include "ref_t.cpp"

#endif  // !defined _CUTS_REF_T_H_
