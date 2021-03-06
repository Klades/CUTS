// -*- C++ -*-

//=============================================================================
/**
 * @file    EISA_In_Type.h
 *
 * $Id$
 *
 * @author  James H. Hill
 */
//=============================================================================

#ifndef _CUTS_EISA_IN_TYPE_H_
#define _CUTS_EISA_IN_TYPE_H_

#include "../BE_Type_Map.h"
#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"

/**
 * @class CUTS_EISA_In_Type
 *
 * CIAO C++ mapping for return types.
 */
class CUTS_EISA_In_Type : public CUTS_BE_Type_Map
{
public:
  /// Default constructor.
  CUTS_EISA_In_Type (void);

  /// Destructor.
  ~CUTS_EISA_In_Type (void);

private:
  // prevent the following operations
  CUTS_EISA_In_Type (const CUTS_EISA_In_Type &);
  const CUTS_EISA_In_Type & operator = (const CUTS_EISA_In_Type &);
};

/// Macro to simply requesting the return types mapping.
#define CIAO_IN_TYPE(type) \
  ACE_Singleton <CUTS_EISA_In_Type, ACE_Null_Mutex>::instance ()->value (type)

#if defined (__CUTS_INLINE__)
#include "In_Type.inl"
#endif

#endif  // !defined _CUTS_EISA_IN_TYPE_H_
