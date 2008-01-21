// -*- C++ -*-

//=============================================================================
/**
 * @file        dereference_t.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_DEREFERENCE_T_H_
#define _CUTS_DEREFERENCE_T_H_

template <typename T>
T CUTS_value_of (T t);

#if defined (__CUT_INLINE__)
#include "value_of_t.inl"
#endif

#include "value_of_t.cpp"

#endif  // _CUTS_DEREFERENCE_T_H_
