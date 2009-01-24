// $Id$

#include "ace/FILE_Connector.h"
#include "ace/FILE_IO.h"
#include "boost/spirit/iterator/file_iterator.hpp"

//
// evaluate
//
template <typename IteratorT>
int CUTS_Text_Processor::evaluate (IteratorT begin,
                                   IteratorT end,
                                   std::ostream & out,
                                   bool use_env,
                                   bool ignore_variables,
                                   bool ignore_commands)
{
  // Single pass expanding on the commands.
  if (ignore_variables && !ignore_commands)
    return this->command_sub_.evaluate (begin, end, out);

  // Single pass expanding on the variables.
  if (ignore_commands && !ignore_variables)
    return this->prop_expander_.expand (begin, end, use_env, out);

  // Multi-pass expanding both variables and commands.
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

  if (tempfile.is_open ())
  {
    // Expand the properties in the file.
    if (!ignore_variables)
      retval = this->prop_expander_.expand (begin, end, use_env, tempfile);

    if (retval == 0)
    {
      // Close the temp file from writing.
      tempfile.close ();

      // Reopen the temp file using an iterator this time.
      boost::spirit::file_iterator < > temp_begin (tempname);

      if (temp_begin)
      {
        boost::spirit::file_iterator < > temp_end = temp_begin.make_end ();

        // Second pass will substitute all commands.
        if (!ignore_commands)
          retval = this->command_sub_.evaluate (temp_begin, temp_end, out);

        if (retval != 0)
          ACE_ERROR ((LM_ERROR,
                      "%T (%t) - %M - command substitution failed\n"));
      }
      else
      {
        ACE_ERROR ((LM_ERROR,
                    "%T (%t) - %M - failed to open temp file %s for reading\n",
                    tempname.c_str ()));
      }
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - variable substitution failed\n"));
    }
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to open temp file %s for writing\n",
                tempname.c_str ()));

    retval = -1;
  }

  // Delete the temp file for good.
  if (ACE_OS::unlink (tempname.c_str ()) == -1)
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to delete temp file %s [%m]\n",
                tempname.c_str ()));

  return retval;
}
