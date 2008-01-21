// -*- C++ -*-

//=============================================================================
/**
 * @file    Traits.h
 *
 * $Id$
 *
 * This file contains the classes defining the traits of system dependent
 * artifacts, e.g. event types and user-defined workers
 *
 * @author James H. Hill <hillj@isis.vanderbilt.edu>
 */
//=============================================================================

#ifndef _CUTS_TRAITS_H_
#define _CUTS_TRAITS_H_

namespace CUTS
{
  /////////////////////////////////////////////////////////////////////////////
  // @@ builtin_type

  //===========================================================================
  /**
   * Trait that determines if a type is a builtin type. A builtin type is
   * one that is supported by the compiler by default, i.e., not an abstract
   * data type.
   */
  //===========================================================================

  template <typename T>
  struct builtin_type
  {
    /// The result type of the trait.
    static const bool result_type = false;
  };

  template < >
  struct builtin_type <char>
  {
    static const bool result_type = true;
  };

  template < >
  struct builtin_type <unsigned char>
  {
    static const bool result_type = true;
  };

  template < >
  struct builtin_type <short>
  {
    static const bool result_type = true;
  };

  template < >
  struct builtin_type <unsigned short>
  {
    static const bool result_type = true;
  };

  template < >
  struct builtin_type <long>
  {
    static const bool result_type = true;
  };

  template < >
  struct builtin_type <unsigned long>
  {
    static const bool result_type = true;
  };

  template < >
  struct builtin_type <int>
  {
    static const bool result_type = true;
  };

  template < >
  struct builtin_type <unsigned int>
  {
    static const bool result_type = true;
  };

  template < >
  struct builtin_type <float>
  {
    static const bool result_type = true;
  };

  template < >
  struct builtin_type <double>
  {
    static const bool result_type = true;
  };

  template < >
  struct builtin_type <long double>
  {
    static const bool result_type = true;
  };

  template < >
  struct builtin_type <long long>
  {
    static const bool result_type = true;
  };

  template < >
  struct builtin_type <unsigned long long>
  {
    static const bool result_type = true;
  };
}

#endif  // !defined _CUTS_TRAITS_H_
