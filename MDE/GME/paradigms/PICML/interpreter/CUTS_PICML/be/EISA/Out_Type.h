// -*- C++ -*-

//=============================================================================
/**
 * @file    EISA_Out_Type.h
 *
 * $Id$
 *
 * @author  James H. Hill
 */
//=============================================================================

#ifndef _CUTS_EISA_OUT_TYPE_H_
#define _CUTS_EISA_OUT_TYPE_H_

#include "../BE_Type_Map.h"
#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"

/**
 * @class CUTS_EISA_Out_Type
 *
 * CIAO C++ mapping for return types.
 */
class CUTS_EISA_Out_Type : public CUTS_BE_Type_Map
{
public:
  /// Default constructor.
  CUTS_EISA_Out_Type (void);

  /// Destructor.
  ~CUTS_EISA_Out_Type (void);

private:
  // prevent the following operations
  CUTS_EISA_Out_Type (const CUTS_EISA_Out_Type &);
  const CUTS_EISA_Out_Type & operator = (const CUTS_EISA_Out_Type &);
};

/// Macro to simply requesting the return types mapping.
#define CIAO_OUT_TYPE(type) \
  ACE_Singleton <CUTS_EISA_Out_Type, ACE_Null_Mutex>::instance ()->value (type)

#if defined (__CUTS_INLINE__)
#include "Out_Type.inl"
#endif

#endif  // !defined _CUTS_EISA_OUT_TYPE_H_
