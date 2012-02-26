/* -*- C++ -*- */
// $Id: Log_Format_Adapter.h 80826 2010-03-17


#ifndef _CUTS_LOG_FORMAT_ADAPTER_H
#define _CUTS_LOG_FORMAT_ADAPTER_H

#include "Unite_export.h"
#include "Log_Format.h"
#include "Variable.h"
#include "Variable_Table.h"


/**
 * @ingroup UNITE_Core
 *
 * @class CUTS_Log_Format
 *
 * Represent Log_Format_Adapter in UNITE. Log_Format_Adapter
 * is used to enhance the UNITE finctionality for
 * non-standard system execution traces
 */
class CUTS_UNITE_Export CUTS_Log_Format_Adapter
{

public:

  /// Type definition for 16 bit int Log_Format_Variable
  typedef CUTS_Basic_Log_Format_Variable_T <ACE_INT16> int16_var;

  /// Type definition for 16 bit unsigned int Log_Format_Variable
  typedef CUTS_Basic_Log_Format_Variable_T <ACE_UINT16> uint16_var;

  /// Type definition for 32 bit int Log_Format_Variable
  typedef CUTS_Basic_Log_Format_Variable_T <ACE_INT32> int32_var;

  /// Type definition for 32 bit unsigned int Log_Format_Variable
  typedef CUTS_Basic_Log_Format_Variable_T <ACE_UINT32> uint32_var;

  /// Type definition for 64 bit int Log_Format_Variable
  typedef CUTS_Basic_Log_Format_Variable_T <ACE_INT64> long_var;

  /// Type definition for 64 bit unsigned int Log_Format_Variable
  typedef CUTS_Basic_Log_Format_Variable_T <ACE_UINT64> ulong_var;

  /// Type definition for double Log_Format_Variable
  typedef CUTS_Basic_Log_Format_Variable_T <double> double_var;

  /// Type definition for float Log_Format_Variable
  typedef CUTS_Basic_Log_Format_Variable_T <float> float_var;

  // virtual destructor.
  virtual ~CUTS_Log_Format_Adapter (void);

  // Initializes the adapter
  virtual void init () = 0;

  /**
   * Add new log format variables to the log format.
   * @param[in]     lfmt   The log format variables need to be added.
   */
  virtual void update_log_format (CUTS_Log_Format * lfmt) = 0;

  /**
   * Add new log format relations.
   * @param[in]     lfmt   The log format the relations need to be added.
   */
  virtual void update_relations (CUTS_Log_Format * lfmt) = 0;

 /**
   * Populate values for the variables.
   * @param[in]     lhs   The set of log format variables.
   * @param[in]     rhs   The log format need to be adapted.
   */
  virtual void update_values (CUTS_Log_Format_Variable_Table & vars,
                              CUTS_Log_Format * lfmt) = 0;

  /// reset private variables of the adapter
  virtual void reset () = 0;

  /// close the adapter
  virtual void close () = 0;

  /**
   * Implementation for adding new variables
   * @param[in]     lfmt Adaptive log format
   * @param[in]     Id   name of the log format variable.
   * @param[in]     Type of the variable
   */
  void add_variable (CUTS_Log_Format * lfmt,
                     const char * Id,
                     const char * type);


  /**
   * Implementation for adding new relations
   * @param[in]     lfmt        Adaptive log format
   * @param[in]     effect      Effect log format.
   * @param[in]     cause_var   cause variable.
   * @paran[in]     effect_var  effect variable.
   */
  void add_relation (CUTS_Log_Format * lfmt,
                     const char * effect,
                     const char * cause_var,
                     const char * effect_var);

};

// useful when trying to load the Adapter from a shared library
#define CUTS_LOG_FORMAT_ADAPTER_SYMBOL_NAME   "create_Cuts_Log_Format_Adapter"

/// Declares the create method for dynamically loading the adapters
#define CUTS_LOG_FORMAT_ADAPTER_EXPORT_DECL(export_macro) \
  extern "C" export_macro \
  CUTS_Log_Format_Adapter * create_Cuts_Log_Format_Adapter (void)

#endif /* _CUTS_LOG_FORMAT_ADAPTER_H */