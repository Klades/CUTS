// -*- C++ -*-

//=============================================================================
/**
 * @file        Where_Clause_Builder.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_WHERE_CLAUSE_BUILDER_H_
#define _CUTS_WHERE_CLAUSE_BUILDER_H_

#include "cuts-unite.h"
#include "ace/SStringfwd.h"

/**
 * @class CUTS_Where_Clause_Builder
 *
 * This help class con
 */
class CUTS_UNITE_XML_Export CUTS_Where_Clause_Builder
{
public:
  /// Default constructor.
  CUTS_Where_Clause_Builder (void);

  /// Destructor.
  ~CUTS_Where_Clause_Builder (void);

  /**
   * Build the SQL WHERE class for the condition. There is also an
   * option to prepend the WHERE statement to the condition. By default
   * this option is not enabled.
   *
   * @param[in]       condition         Condition from XML document
   * @param[out]      result            String with SQL expression
   * @param[in]       prepend_where     Prepend WHERE statement
   */
  int build (const ::CUTS::XML::conditionType & condition,
             ACE_CString & result,
             bool prepend_where = false);
};

#if defined (__CUTS_INLINE__)
#include "Where_Clause_Builder.inl"
#endif

#endif  // !defined _CUTS_WHERE_CLAUSE_BUILDER_H_
