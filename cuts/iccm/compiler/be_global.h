// -*- C++ -*-

//=============================================================================
/**
 *  @file       $File$
 *
 *  $Id$
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ICCM_BE_GLOBAL_H_
#define _CUTS_ICCM_BE_GLOBAL_H_

#include "ast_type.h"
#include "ast_eventtype.h"

#include "ace/Unbounded_Set.h"

#include "Compiler_export.h"

// Forward decl.
class AST_Generator;

/**
 * @class BE_GlobalData
 *
 * Defines a class containing all back end global data.
 */
class ICCM_COMPILER_Export BE_GlobalData
{
public:
  // Constructor.
  BE_GlobalData (void);

  // Destructor.
  virtual ~BE_GlobalData (void);

  // Command line passed to ACE_Process::spawn. Different
  // implementations in different backends.
  ACE_CString spawn_options (void);

  // Parse args that affect the backend.
  virtual void parse_args (long & i, char **av);
  virtual void prep_be_arg (char * s);
  virtual void print_usage (void);
  virtual void arg_post_proc (void);
  virtual void post_produce (void);

  // Cleanup.
  virtual void destroy (void);

  static void get_filename (const ACE_CString & pathname, ACE_CString & filename);
  static void get_basename (const ACE_CString & filename, ACE_CString & basename);
  static void normalize (const ACE_CString & value, ACE_CString & result);

  /// Get the target filename. This is a concatentation of the output
  /// path, the basename of the source file, and the suffix.
  const ACE_CString & get_target_executor_idl_filename (void) const;

  /// Get the source files basename. This is the source file name
  /// without the extension.
  const ACE_CString & get_source_basename (void) const;
  const ACE_CString & get_source_filename (void) const;

  /// The output path for the data.
  ACE_CString output_path_;

  /// Collection of files.
  ACE_CString source_file_;

  /// Suffix to apply to target filename.
  ACE_CString executor_idl_suffix_;

  ACE_CString wrapper_event_suffix_;

  ACE_CString stub_export_macro_;
  ACE_CString stub_export_macro_filename_;

  ACE_CString svnt_export_macro_;
  ACE_CString svnt_export_macro_filename_;

  const ACE_CString & get_stub_header_filename (void) const;
  const ACE_CString & get_stub_source_filename (void) const;

  const ACE_CString & get_svnt_header_filename (void) const;
  const ACE_CString & get_svnt_source_filename (void) const;

  const ACE_CString & get_event_mapping_header_filename (void) const;
  const ACE_CString & get_event_mapping_source_filename (void) const;

  // BEGIN: ARCHITECTURE SPECIFIC VALUES.
  virtual const ACE_CString & get_stub_file_prefix (void) const = 0;

  virtual const ACE_CString & get_context_template_header_filename (void) const = 0;
  virtual const ACE_CString & get_servant_template_header_filename (void) const = 0;

  virtual const ACE_CString & get_servant_template_typename (void) const = 0;
  virtual const ACE_CString & get_context_typename (void) const = 0;

  virtual const ACE_CString & get_consumer_template_typename (void) const = 0;
  virtual const ACE_CString & get_publisher_typename (void) const = 0;
  virtual const ACE_CString & get_publisher_template_typename (void) const = 0;
  virtual const ACE_CString & get_publisher_table_typename (void) const = 0;
  virtual const ACE_CString & get_publisher_table_template_typename (void) const = 0;

  bool is_wrapper_eventtype (AST_EventType * node) const;
  bool get_wrapper_eventtype (AST_EventType * node, ACE_CString & type) const;

private:
  /// Basename for the source file.
  mutable ACE_CString source_basename_;

  /// Filename for the source file (i.e., without a path).
  mutable ACE_CString source_filename_;

  /// Cached version of the target basename.
  mutable ACE_CString target_basename_;

  /// Cached version of the target filename.
  mutable ACE_CString target_executor_idl_file_;

  /// Header filename for the servant.
  mutable ACE_CString stub_header_filename_;

  /// Source filename for the servant.
  mutable ACE_CString stub_source_filename_;

  /// Header filename for the servant.
  mutable ACE_CString svnt_header_filename_;

  /// Source filename for the servant.
  mutable ACE_CString svnt_source_filename_;

  /// Header file that contains event mapping definitions.
  mutable ACE_CString event_mapping_header_filename_;

  /// Source file that contains event mapping implementations.
  mutable ACE_CString event_mapping_source_filename_;
};

extern ICCM_COMPILER_Export BE_GlobalData * be_global;

#endif /* IDL_TO_PICML_BE_GLOBAL_H */
