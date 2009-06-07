// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_Single_Subsciber_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CCM_TRAITS_T_H_
#define _CUTS_CCM_TRAITS_T_H_

template <typename T>
class CUTS_CCM_Traits_T
{
public:
  typedef ::Components::EventConsumerBase consumer_type;
  typedef typename consumer_type::_ptr_type consumer_ptr_type;
  typedef typename consumer_type::_var_type consumer_var_type;
};

#endif  // !defined _CUTS_CCM_TRAITS_T_H_
