// $Id$

#include "ace/CORBA_macros.h"
#include "ace/FILE_Connector.h"
#include "ace/FILE_IO.h"
#include "boost/spirit/include/classic_file_iterator.hpp"

//
// evaluate
//
template <typename IteratorT>
bool CUTS_Text_Processor::evaluate (IteratorT begin,
                                    IteratorT end,
                                    std::ostream & out,
                                    bool use_env,
                                    bool ignore_variables,
                                    bool ignore_commands)
{
  // Single pass expanding on the commands.
  if (ignore_variables && !ignore_commands)
    return this->command_sub_.evaluate (begin, end, out);

  this->property_eval_.config ().use_env_ = use_env;

  // Single pass expanding on the variables.
  if (ignore_commands && !ignore_variables)
  {
    if (this->property_eval_.evaluate (begin, end))
      out << this->buffer_.str ();
  }

  // Multi-pass expanding both variables and commands.

  // Create a temporary file on the disk.
  ACE_FILE_IO file;
  ACE_FILE_Connector disk (file,
                           reinterpret_cast <const ACE_FILE_Addr &> (ACE_Addr::sap_any));

  if (ACE_INVALID_HANDLE == file.get_handle ())
    return false;

  // Delete the temp file so we can use in the stream.
  ACE_FILE_Addr file_addr;
  file.get_local_addr (file_addr);

  std::string tempname = file_addr.get_path_name ();
  file.remove ();

  // Reopen the temp file using a stream.
  std::ofstream tempfile;
  tempfile.open (tempname.c_str ());

  if (!tempfile.is_open ())
    return false;

  // Expand the properties in to the temporary file.
  CUTS_Property_Evaluator_Stream_Actor tempfile_actor (tempfile);

  property_evaluator_type * temp_propeval = 0;
  ACE_NEW_THROW_EX (temp_propeval,
                    property_evaluator_type (this->property_eval_.property_map (), tempfile_actor),
                    ACE_bad_alloc ());

  ACE_Auto_Ptr <property_evaluator_type> auto_clean (temp_propeval);
  bool retval = temp_propeval->evaluate (begin, end);

  // Close the temp file from writing.
  tempfile.close ();

  if (retval)
  {
    // Reopen the temp file using an iterator this time.
    boost::spirit::classic::file_iterator < > temp_begin (tempname);

    if (temp_begin)
    {
      boost::spirit::classic::file_iterator < > temp_end = temp_begin.make_end ();
      retval = this->command_sub_.evaluate (temp_begin, temp_end, out);
    }
    else
      retval = false;
  }

  // Delete the temp file for good.
  if (ACE_OS::unlink (tempname.c_str ()) == -1)
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to delete temp file %s [%m]\n",
                tempname.c_str ()));

  return retval;
}
