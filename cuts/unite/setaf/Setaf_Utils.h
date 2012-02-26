// $Id: Setaf_Utils.h

#ifndef _CUTS_SETAF_UTILS_H_
#define _CUTS_SETAF_UTILS_H_

#include <vector>
#include <string>
#include "Setaf_Format.h"

namespace CUTS_SETAF_UTILS
{
  typedef std::vector <CUTS_Setaf_Log_Format *> Setaf_Entries;

  typedef std::vector <CUTS_Setaf_Log_Format_Relation *> Setaf_Relations;

  typedef std::vector <CUTS_Setaf_Log_Format *>::iterator lf_iterator;

  typedef std::vector <CUTS_Setaf_Log_Format_Relation *>::iterator rel_iterator;

  typedef std::vector <std::string> string_vector;

  typedef std::vector <CUTS_Setaf_Log_Format_Code *> Setaf_Code;

  typedef std::vector <CUTS_Setaf_Log_Format_Code *>::iterator code_iterator;

  enum type_t
  {
    /// The variable is a string
    ST_STRING,

    /// The variable is an integer
    ST_INTEGER,

    /// The varialbe is an float/double
    ST_UNITE,

  };

}

#endif  // !defined _CUTS_SETAF_UTILS_H_