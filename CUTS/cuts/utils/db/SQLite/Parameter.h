// -*- C++ -*-

//=============================================================================
/**
 * @file          Parameter.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_DB_SQLITE_PARAMETER_H_
#define _CUTS_DB_SQLITE_PARAMETER_H_

#include "DB_SQLite_export.h"
#include "cuts/utils/db/DB_Parameter.h"

class CUTS_DB_SQLITE_Export CUTS_DB_SQLite_Parameter :
  public CUTS_DB_Parameter
{
public:
  CUTS_DB_SQLite_Parameter (void);

  virtual ~CUTS_DB_SQLite_Parameter (void);
};

#endif  // !defined _CUTS_DB_SQLITE_PARAMETER_H_
