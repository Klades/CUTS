// -*- C++ -*-

//=============================================================================
/**
 * @file        Text_Variable_Importer.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEXT_VARIABLE_IMPORTER_H_
#define _CUTS_TEXT_VARIABLE_IMPORTER_H_

#include "Variable_Importer_Strategy.h"

/**
 * @class CUTS_Text_Variable_Importer
 *
 * Implementation of the CUTS_Variable_Importer_Strategy. This implementation
 * assumes the format of the file is a plain text file. Each line of the text
 * file contains a variable that is in the format NAME=VALUE, where NAME is
 * the name of the value and VALUE is the value of the variable.
 */
class CUTS_Text_Variable_Importer :
  public CUTS_Variable_Importer_Strategy
{
public:
  /// Default constructor.
  CUTS_Text_Variable_Importer (void);

  /// Destructor.
  virtual ~CUTS_Text_Variable_Importer (void);

  // Import the variables.
  virtual int handle_import (const ACE_CString & location,
                             CUTS_Property_Map & vars);
};

#if defined (__CUTS_INLINE__)
#include "Text_Variable_Importer.inl"
#endif

#endif  // !defined _CUTS_TEXT_VARIABLE_IMPORTER_H_
