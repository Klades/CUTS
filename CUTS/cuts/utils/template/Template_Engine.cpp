// $Id$

#include "Template_Engine.h"

#if !defined (__CUTS_INLINE__)
#include "Template_Engine.inl"
#endif

#include "boost/spirit/iterator/file_iterator.hpp"

//
// process
//
bool CUTS_Template_Engine::
process (const char * filename, bool use_env, std::ostream & out)
{
  // Find the start of the file.
  boost::spirit::file_iterator <char> begin (filename);

  if (begin)
  {
    // Find the end of the file.
    boost::spirit::file_iterator <char> end = begin.make_end ();

    if (this->pe_.expand (begin, end, use_env, out))
      return true;

    ACE_ERROR ((LM_ERROR,
                "%T - %M - failed to convert template file [file=%s]\n",
                filename));
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - failed to open file %s for reading\n",
                filename));
  }

  return false;
}
