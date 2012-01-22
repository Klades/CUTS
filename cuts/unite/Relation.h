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
 * @ingroup UNITE_Core
 *
 * @class CUTS_Relation_Causality
 *
 * Represent a causalities in Relations
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

  /// overloaded = operator
  const CUTS_Relation_Causality & operator = (const CUTS_Relation_Causality & copy);

   /**
   * Set the relation values
   * @param[in]     cause    cause variable value of the relation
   * @param[in]     effect   effect variable value for the relation
   */
  void set (const ACE_CString & cause, const ACE_CString & effect);

  /// Get the cause string
  const ACE_CString & cause (void) const;

  /// Get the effect string
  const ACE_CString & effect (void) const;

private:
  /// string representing the cause
  ACE_CString cause_;

  /// string representing the effect
  ACE_CString effect_;
};

/**
 * @class CUTS_Log_Format_Relation
 *
 * Represent a Relation between Log_Formats
 */
class CUTS_UNITE_Export CUTS_Log_Format_Relation
{
public:
  /// Type definition of the causality.
  typedef ACE_Vector <CUTS_Relation_Causality> causality_type;

  /// Default constructor
  CUTS_Log_Format_Relation (void);

  /// Copy constructor
  CUTS_Log_Format_Relation (const CUTS_Log_Format_Relation & copy);

  /// Destructor
  ~CUTS_Log_Format_Relation (void);

  /// Set the effect log format
  void effect (CUTS_Log_Format * format);

  /// Get the effect log format
  CUTS_Log_Format * effect (void);

  /// Get the effect log format for read only
  const CUTS_Log_Format * effect (void) const;

  /// Get the causality for the relation
  causality_type & causality (void);

  /// Get the causality for the relation
  const causality_type & causality (void) const;

  /// overloaded = operator
  const CUTS_Log_Format_Relation & operator = (const CUTS_Log_Format_Relation & copy);

private:
  /// The log format for the effect.
  CUTS_Log_Format * format_;

  /// Causality for the relation.
  causality_type causality_;
};

#endif  // !defined _CUTS_UNITE_RELATION_H_