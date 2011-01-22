// -*- C++ -*-

//=============================================================================
/**
 *  @file         CCM_Traits_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CCM_TRAITS_T_H_
#define _CUTS_CCM_TRAITS_T_H_

/**
 * @class CUTS_CCM_Traits_T
 *
 * Trait class for CCM. This class should be specialized by the event
 * type to override the default traits below.
 */
template <typename T>
class CUTS_CCM_Traits_T
{
public:
  /// Default definition of the consumer type.
  typedef ::Components::EventConsumerBase consumer_type;

  /// Default definition of the consumer _ptr type.
  typedef typename consumer_type::_ptr_type consumer_ptr_type;

  /// Default definition of the consumer _var type.
  typedef typename consumer_type::_var_type consumer_var_type;
};

#endif  // !defined _CUTS_CCM_TRAITS_T_H_
