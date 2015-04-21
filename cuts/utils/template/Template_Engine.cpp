// $Id$

#include "Template_Engine.h"

#if !defined (__CUTS_INLINE__)
#include "Template_Engine.inl"
#endif

#include "boost/spirit/include/classic_file_iterator.hpp"

//
// process
//
bool CUTS_Template_Engine::process (const char * filename,
                                    std::ostream & out,
                                    bool use_env,
                                    bool ignore_variables,
                                    bool ignore_commands)
{
  // Find the start of the file.
  boost::spirit::classic::file_iterator <char> begin (filename);

  if (begin)
  {
    // Find the end of the file.
    boost::spirit::classic::file_iterator <char> end = begin.make_end ();

    return this->tp_.evaluate (begin,
                               end,
                               out,
                               use_env,
                               ignore_variables,
                               ignore_commands) == 0 ? true : false;
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to open file %s for reading\n",
                filename));
  }

  return false;
}
