// -*- C++ -*-

//=============================================================================
/**
 * @file        Log_Format.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_UNITE_LOG_FORMAT_H_
#define _CUTS_UNITE_LOG_FORMAT_H_

#include "Unite_export.h"
#include "Variable_Table.h"
#include "Relation.h"
#include <vector>

// Forward decl.
struct real_pcre;
typedef struct real_pcre pcre;

// Forward decl.
struct pcre_extra;

class CUTS_Log_Format_Adapter;

/**
 * @ingroup UNITE_Core
 *
 * @class CUTS_Log_Format
 */
class CUTS_UNITE_Export CUTS_Log_Format
{
public:
  typedef std::vector <CUTS_Log_Format_Relation> relations_type;

  /// Default constructor.
  CUTS_Log_Format (const ACE_CString & name);

  /// Destructor.
  ~CUTS_Log_Format (void);

  /// Given a log format string compiles it and populate variables, relations.
  bool compile (const ACE_CString & format);

  /// Checks whether the pcre expression is not null
  bool is_valid (void) const;


  /**
   * Check whether the messages matches a specified log format
   * unit test.
   * @param[in]     message   the input trace from the test database
   * @param[in]     adapter   log format adapter if it is set.
   * @return        true if mathced, otherwise false
   */
  bool match (const ACE_CString & message,
              CUTS_Log_Format_Adapter * adapter) ;

  /// Reset the log format.
  void reset (void);

  /// Get the name of the log format
  const ACE_CString & name (void) const;

  /// Get the relation types
  relations_type & relations (void);

  /// Get the relation types only for reading
  const relations_type & relations (void) const;

  /// Get the variables map only for reading
  const CUTS_Log_Format_Variable_Table & variables (void) const;

  /// Get the variable map
  CUTS_Log_Format_Variable_Table & variables (void);

  /// Set the captures_size
  void captures_size (size_t size);

  /// Get the captures_size
  size_t captures_size (void);

 /// Set the captures array
  ACE_Auto_Array_Ptr <int> & captures (void);




private:

  /// Name of the log format.
  ACE_CString name_;

  /// Compiled version of the log format.
  pcre * expr_;

  /// Extra information about the log format.
  pcre_extra * extra_;

  /// Variables in the log format.
  CUTS_Log_Format_Variable_Table vars_;

  /// Relation types for the log format.
  relations_type relations_;

  /// Number of captures in the log format.
  size_t captures_size_;

  /// Indices for storing capture information.
  ACE_Auto_Array_Ptr <int> captures_;

  // prevent the following operations
  CUTS_Log_Format (const CUTS_Log_Format &);
  const CUTS_Log_Format & operator = (const CUTS_Log_Format &);
};

#endif  // !defined _CUTS_UNITE_LOG_FORMAT_H_
