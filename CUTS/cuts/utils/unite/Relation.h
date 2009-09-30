// -*- C++ -*-

//=============================================================================
/**
 * @file        Relation.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_UNITE_RELATION_H_
#define _CUTS_UNITE_RELATION_H_

#include "Unite_export.h"
#include "ace/SString.h"
#include "ace/Vector_T.h"

// Forward decl.
class CUTS_Log_Format;

/**
 * @ingroup UNITE_Common
 *
 * @class CUTS_Relation_Causality
 */
class CUTS_UNITE_Export CUTS_Relation_Causality
{
public:
  /// Default constructor.
  CUTS_Relation_Causality (void);

  /**
   * Initializing constructor.
   */
  CUTS_Relation_Causality (const ACE_CString & cause,
                           const ACE_CString & effect);

  /**
   * Copy constructor.
   */
  CUTS_Relation_Causality (const CUTS_Relation_Causality & copy);

  const CUTS_Relation_Causality & operator = (const CUTS_Relation_Causality & copy);

  void set (const ACE_CString & cause, const ACE_CString & effect);

  const ACE_CString & cause (void) const;

  const ACE_CString & effect (void) const;

private:
  ACE_CString cause_;

  ACE_CString effect_;
};

/**
 * @class CUTS_Log_Format_Relation
 */
class CUTS_UNITE_Export CUTS_Log_Format_Relation
{
public:
  /// Type definition of the causality.
  typedef ACE_Vector <CUTS_Relation_Causality> causality_type;

  /// Default constructor
  CUTS_Log_Format_Relation (void);

  CUTS_Log_Format_Relation (const CUTS_Log_Format_Relation & copy);

  /// Destructor
  ~CUTS_Log_Format_Relation (void);

  void effect (CUTS_Log_Format * format);

  CUTS_Log_Format * effect (void);

  const CUTS_Log_Format * effect (void) const;

  /// Get the causality for the relation
  causality_type & causality (void);

  /// Get the causality for the relation
  const causality_type & causality (void) const;

  const CUTS_Log_Format_Relation & operator = (const CUTS_Log_Format_Relation & copy);

private:
  /// The log format for the effect.
  CUTS_Log_Format * format_;

  /// Causality for the relation.
  causality_type causality_;
};

#endif  // !defined _CUTS_UNITE_RELATION_H_
