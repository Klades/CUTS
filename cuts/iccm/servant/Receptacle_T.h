// -*- C++ -*-

//==============================================================================
/**
 *  @file        Receptacle_T.h
 *
 *  $Id$
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _ICCM_RECEPTACLE_T_H_
#define _ICCM_RECEPTACLE_T_H_

#include "Receptacle.h"

namespace iCCM
{

/**
 * @class Receptacle_T
 *
 * Templated receptacle for a concrete target type
 */
template <typename T>
class Receptacle_T : public Receptacle
{
public:
  /// Default constructor.
  Receptacle_T (void);

  /// Destructor.
  virtual ~Receptacle_T (void);

  // Connect the receptacle to the provided facet
  virtual ::Components::Cookie * connect (::CORBA::Object_ptr obj);

  // Disconnect the receptacle
  virtual ::CORBA::Object_ptr disconnect (::Components::Cookie * c);

  // Connection getter
  virtual typename T::_ptr_type get_connection (void);

private:
  ACE_Utils::UUID uuid_;

  typename T::_var_type connection_;
};

} // namespace iCCM

#if defined (__CUTS_INLINE__)
#include "Receptacle_T.inl"
#endif  // !defined __CUTS_INLINE__

#include "Receptacle_T.cpp"

#endif  // _ICCM_RECEPTACLE_T_H_
