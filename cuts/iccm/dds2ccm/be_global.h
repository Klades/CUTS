/* -*- c++ -*- */
// $Id$

// ============================================================================
//
// = LIBRARY
//    IDL_TO_PICML_BE_DLL
//
// = FILENAME
//    be_global.h
//
// = DESCRIPTION
//    Header file for class containing compiler back end global data.
//
// = AUTHOR
//    Jeff Parsons <parsons@cs.wustl.edu>
//
// ============================================================================

#ifndef IDL_TO_PICML_BE_GLOBAL_H
#define IDL_TO_PICML_BE_GLOBAL_H

#include "ast_type.h"
#include "ace/Unbounded_Set.h"

// Forward decl.
class AST_Generator;

/**
 * @class BE_GlobalData
 *
 * Defines a class containing all back end global data.
 */
class BE_GlobalData
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
  void parse_args (long &i, char **av);

  // Cleanup.
  void destroy (void);

  /// Get the target filename. This is a concatentation of the output
  /// path, the basename of the source file, and the suffix.
  const ACE_CString & get_target_filename (void) const;

  /// Get the basename for the target file. This is a concatentation
  /// of the the basename of the source file and the suffix.
  const ACE_CString & get_target_basename (void) const;

  static void get_filename (const ACE_CString & pathname, ACE_CString & filename);
  static ACE_CString & normalize (ACE_CString & file);

  /// The output path for the data.
  ACE_CString output_path_;

  /// Collection of files.
  ACE_CString source_file_;

  /// Suffix to apply to target filename.
  ACE_CString suffix_;

private:
  /// Cached version of the target basename.
  mutable ACE_CString target_basename_;

  /// Cached version of the target filename.
  mutable ACE_CString target_filename_;
};

#endif /* IDL_TO_PICML_BE_GLOBAL_H */
