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

  //typedef std::auto_ptr <CUTS_Log_Format_Adapter> adapter_ptr;

    /// Default constructor.
  CUTS_Log_Format (const ACE_CString & name);

  /// Destructor.
  ~CUTS_Log_Format (void);

  bool compile (const ACE_CString & format);

  bool is_valid (void) const;

  bool match (const ACE_CString & message, 
	  CUTS_Log_Format_Adapter *adapter) ;

  /// Reset the log format.
  void reset (void);

  const ACE_CString & name (void) const;

  relations_type & relations (void);

  const relations_type & relations (void) const;

  const CUTS_Log_Format_Variable_Table & variables (void) const;

  CUTS_Log_Format_Variable_Table & variables (void);

  void captures_size(size_t size); 

  size_t captures_size(void); 

  ACE_Auto_Array_Ptr <int> captures(void);

  size_t captures_size_;

  ACE_Auto_Array_Ptr <int> captures_;

  
private:
  //void reset (void);

  /// Name of the log format.
  ACE_CString name_;

  /// Compiled version of the log format.
  pcre * expr_;

  /// Extra information about the log format.
  pcre_extra * extra_;

  /// Variables in the log format.
  CUTS_Log_Format_Variable_Table vars_;

  /// Relations for the log format.
  relations_type relations_;

  /// Number of captures in the log format.
  //size_t captures_size_;

  /// This will be useful for adapter.
  int id_value_;

  /// Indices for storing capture information.
  //ACE_Auto_Array_Ptr <int> captures_;

  // prevent the following operations
  CUTS_Log_Format (const CUTS_Log_Format &);
  const CUTS_Log_Format & operator = (const CUTS_Log_Format &);
};

#endif  // !defined _CUTS_UNITE_LOG_FORMAT_H_
