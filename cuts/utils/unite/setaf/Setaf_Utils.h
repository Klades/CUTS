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

}

#endif  // !defined _CUTS_SETAF_UTILS_H_