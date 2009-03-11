// -*- C++ -*-
// $Id$

#include "boost/spirit/iterator/file_iterator.hpp"
#include "cuts/utils/Text_Processor.h"
#include <fstream>
#include <sstream>

//
// operator ()
//
template <typename IteratorT>
void CUTS_File_Generator::operator () (IteratorT begin, IteratorT end) const
{
  // Override this configuration with the properties from the
  // properties specified at the command-line.
  this->config_.join (this->overrides_, true);

  // Get filename extension of template file, if it exist.
  size_t pos = this->template_.find_last_of ('.');

  ACE_CString filename;

  if (this->config_.get ("name", filename) != 0)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to locate configuration name\n"));
    return;
  }

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
      CUTS_Text_Processor processor (this->config_);

      if (processor.evaluate (file_begin,
                              file_end,
                              outfile,
                              this->use_env_,
                              this->ignore_variables_,
                              this->ignore_commands_) == 0)
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
}

