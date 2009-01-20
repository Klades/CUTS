// -*- C++ -*-

//=============================================================================
/**
 * @file          Text_Processor.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEXT_PROCESSOR_H_
#define _CUTS_TEXT_PROCESSOR_H_

#include "Property_Expander.h"
#include "Command_Substitution.h"
#include "ace/FILE_Connector.h"
#include "ace/FILE_IO.h"
#include "boost/spirit/iterator/file_iterator.hpp"

// Forward decl.
class CUTS_Property_Map;

/**
 * @class CUTS_Text_Processor
 *
 * Preprocess for string values. The preprocessor will expand all environment
 * variables, and substitute all commands with the generated text.
 */
class CUTS_UTILS_Export CUTS_Text_Processor
{
public:
  /// Default constructor.
  CUTS_Text_Processor (const CUTS_Property_Map & map);

  /// Destructor.
  ~CUTS_Text_Processor (void);

  /**
   * Run the preprocess on a string.
   *
   * @param[in]         str           String to preprocess.
   * @param[out]        output        Resultant string.
   */
  int evaluate (const char * str, ACE_CString & output);

  template <typename IteratorT>
  int evaluate (IteratorT begin, IteratorT end, std::ostream & out)
  {
    int retval = 0;

    // Create a temporary file on the disk.
    ACE_FILE_IO file;
    ACE_FILE_Connector disk (file,
                             reinterpret_cast <const ACE_FILE_Addr &> (ACE_Addr::sap_any));

    if (file.get_handle () == ACE_INVALID_HANDLE)
      return -1;

    // Delete the temp file so we can use in the stream.
    ACE_FILE_Addr file_addr;
    file.get_local_addr (file_addr);

    std::string tempname = file_addr.get_path_name ();
    file.remove ();

    // Reopen the temp file using a stream.
    std::ofstream tempfile;
    tempfile.open (tempname.c_str ());

    if (!tempfile.is_open ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to open temp file %s for writing\n",
                         tempname.c_str ()),
                         -1);

    if (!this->prop_expander_.expand (begin, end, true, tempfile))
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to expand environment variables\n"),
                         -1);

    // Close the temp file from writing.
    tempfile.close ();

    // Reopen the temp file using an iterator this time.
    boost::spirit::file_iterator < > temp_begin (tempname);

    if (!temp_begin)
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to open temp file %s for reading\n",
                         tempname.c_str ()),
                         -1);

    boost::spirit::file_iterator < > temp_end = temp_begin.make_end ();

    // Second pass will substitute all commands.
    if (!this->command_sub_.evaluate (temp_begin, temp_end, out))
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to substitute some of the commands\n"),
                         -1);

    // Delete the temp file for good.
    ACE_OS::unlink (tempname.c_str ());

    return 0;
  }

private:
  /// Environment variable substitution engine.
  CUTS_Property_Expander prop_expander_;

  /// Command substitution engine.
  CUTS_Command_Substitution command_sub_;
};

#if defined (__CUTS_INLINE__)
#include "Text_Processor.inl"
#endif

#endif  // !defined _CUTS_NODE_PREPROCESSOR_H_
