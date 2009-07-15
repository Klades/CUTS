// $Id$

#include "File_Generator.h"

#if !defined (__CUTS_INLINE__)
#include "File_Generator.inl"
#endif

#include "boost/spirit/iterator/file_iterator.hpp"
#include "cuts/utils/Text_Processor.h"
#include <fstream>
#include <sstream>

//
// ~CUTS_CUTE_Model_Interpreter
//
CUTS_File_Generator::~CUTS_File_Generator (void)
{
  for (property_manager_map::ITERATOR iter (this->config_mgr_);
       !iter.done ();
       ++ iter)
  {
    delete iter->item ();
  }
}

//
// base_config
//
void CUTS_File_Generator::
base_config (CUTS_Property_Map & config, const std::string & basename)
{
  CUTS_Property_Map * base_config = 0;

  if (0 == this->config_mgr_.find (basename.c_str (), base_config))
    config.join (*base_config, true);
}

//
// handle_config
//
int CUTS_File_Generator::
handle_config (const CUTS_Property_Map & config)
{
  // Get filename extension of template file, if it exist.
  size_t pos = this->template_.find_last_of ('.');

  ACE_CString filename;

  if (config.get ("config.name", filename) != 0)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to locate configuration name\n"),
                       -1);

  // Store a duplicate of the configuration just in case it
  // is used a base configuration in other configurations.
  CUTS_Property_Map * dup_config = 0;

  ACE_NEW_RETURN (dup_config,
                  CUTS_Property_Map (config),
                  -1);

  if (0 != dup_config)
    this->config_mgr_.bind (filename, dup_config);

  // Construct the path of the filename.
  std::ostringstream ostr;
  ostr << this->output_ << "/" << filename.c_str ();

  if (pos != std::string::npos)
    ostr << this->template_.substr (pos);

  // Now, generate the file using the template.
  std::ofstream outfile;
  outfile.open (ostr.str ().c_str ());

  // Open the template file for parsing.
  boost::spirit::
    file_iterator < > file_begin (this->template_.c_str ());

  if (file_begin)
  {
    // Locate the end of the template file.
    boost::spirit::file_iterator < > file_end = file_begin.make_end ();

    if (outfile.is_open ())
    {
      CUTS_Text_Processor processor (config);

      if (processor.evaluate (file_begin,
                              file_end,
                              outfile,
                              this->use_env_,
                              this->ignore_variables_,
                              this->ignore_commands_))
      {
        ACE_DEBUG ((LM_DEBUG,
                    "%T (%t) - %M - successfully generated %s\n",
                    filename.c_str ()));
      }
      else
      {
        ACE_ERROR ((LM_ERROR,
                    "%T (%t) - %M - failed to generate %s\n",
                    filename.c_str ()));
      }

      outfile.close ();
    }
  }

  return 0;
}
