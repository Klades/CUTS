// $Id:

#include "Setaf_Format.h"

#if !defined (__CUTS_INLINE__)
#include "Setaf_Format.inl"
#endif


//
// process_format_string
//
void CUTS_Setaf_Log_Format::
process_format_string (std::string & format_string)
{
  // Process the datapoints in the log format and
  // populate the object

  size_t pos = format_string.find (".");
  this->name_ = format_string.substr (0, pos);
  this->id_ = format_string.substr (pos + 1);
}

//
// process_relation_strings
//
void CUTS_Setaf_Log_Format_Relation::
process_relation_strings (std::string & cause_string,
                          std::string & effect_string)
{
  // Process the relations string in the specifiaction and
  // populate the object

  size_t pos1 = cause_string.find (".");
  this->cause_lf_ = cause_string.substr (0, pos1);
  this->cause_var_ = cause_string.substr (pos1 + 1);

  size_t pos2 = effect_string.find (".");
  this->effect_lf_ = effect_string.substr (0, pos2);
  this->effect_var_ = effect_string.substr (pos2 + 1);

}