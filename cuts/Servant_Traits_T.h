// -*- C++ -*-

//=============================================================================
/**
 * @file        Servant_Traits_T.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_SERVANT_TRAITS_T_H_
#define _CUTS_SERVANT_TRAITS_T_H_

#include "config.h"

// Forward decl.
struct CUTS_NIL;

/**
 * @class CUTS_Servant_Trait_T
 */
template <typename T, typename NEXT = CUTS_NIL>
class CUTS_Servant_Trait_T
{
public:
  /// Default constructor.
  CUTS_Servant_Trait_T (void);

  /// Destructor.
  ~CUTS_Servant_Trait_T (void);

  /**
   * Activate the specified object.
   *
   * @param[in]       obj         Object to activate
   */
  int handle_activate (::CORBA::Object_ptr obj);

  /**
   * Deactivate the specified object.
   *
   * @param[in]       obj         Object to deactivate
   */
  int handle_deactivate (::CORBA::Object_ptr obj);

  int set_value (int id, const ACE_CString & value);

  int get_value (int id, ACE_CString & value);

private:
  /// The next trait.
  NEXT next_;

  // The value of the trait.
  ACE_CString trait_value_;
};

/**
 * @class CUTS_Servant_Trait_T
 */
template <typename T>
class CUTS_Servant_Trait_T <T, CUTS_NIL>
{
public:
  /// Default constructor.
  CUTS_Servant_Trait_T (void);

  /// Destructor.
  ~CUTS_Servant_Trait_T (void);

  /**
   * Activate the specified object.
   *
   * @param[in]       obj         Object to activate
   */
  int handle_activate (::CORBA::Object_ptr obj);

  /**
   * Deactivate the specified object.
   *
   * @param[in]       obj         Object to deactivate
   */
  int handle_deactivate (::CORBA::Object_ptr obj);

  int set_value (int id, const ACE_CString & value);

  int get_value (int id, ACE_CString & value);

private:
  // The value of the trait.
  ACE_CString trait_value_;
};

#if defined (__CUTS_INLINE__)
#include "Servant_Traits_T.inl"
#endif

#include "Servant_Traits_T.cpp"

#endif  // !defined _CUTS_SERVANT_TRAITS_T_H_
