#include "Dmac_Log_Format.h"
#include <iostream>


bool compare_time (CUTS_Dmac_Log_Msg_Details & ins1,
                   CUTS_Dmac_Log_Msg_Details & ins2)
{
  double val1 = ins1.time_val ();
  double val2 = ins2.time_val ();

  return val1 <= val2;
}

//
// CUTS_Dmac_Log_Format
//
CUTS_Dmac_Log_Format::CUTS_Dmac_Log_Format (
    int id,
    CUTS_DMAC_UTILS::string_vector & log_format_items)
  : id_ (id),
    log_format_items_ (log_format_items),
    coverage_ (0),
    sorted_ (false)
{

}

//
// ~CUTS_Dmac_Log_Format
//
CUTS_Dmac_Log_Format::~CUTS_Dmac_Log_Format (void)
{

}

//
// add_varaible_values
//
void CUTS_Dmac_Log_Format::
add_varaible_values (CUTS_DMAC_UTILS::string_vector & trace)
{
  CUTS_DMAC_UTILS::s_iter it;
  std::string empty_str ("{}");

  // Keep the values for each log format variables
  int j = 1;
  for (unsigned int i = 0; i < this->log_format_items_.size (); i++)
  {
    if (this->log_format_items_ [i].compare (empty_str) == 0)
    {
      this->vars_ [j].push_back (trace [i]);
      j++;
    }
  }
}

//
// add_relation
//
void CUTS_Dmac_Log_Format::
add_relation (CUTS_Dmac_Relation & relation)
{
  this->relations_.push_back (relation);
}

// I will remove this commented code, if the new
// algorithm for calculating the variable relations
// succeed. - Manjula
//
// extract_variable_relations
//
//void CUTS_Dmac_Log_Format::
//extract_variable_relations (CUTS_Dmac_Log_Format * log_format)
//{
//  var_iterator it1;
//  var_iterator it2;
//
//  CUTS_Dmac_Relation relation (log_format);
//
//  // If the set of values for any two variables on the
//  // log format are the same then they have a possible
//  // cause-effect relationship
//  for (it1 = this->vars_.begin (); it1 != this->vars_.end (); it1++)
//  {
//    for (it2 = log_format->vars_.begin ();
//          it2 != log_format->vars_.end (); it2++)
//    {
//      if (this->match_item_set (it1->second, it2->second))
//      {
//        CUTS_DMAC_UTILS::int_pair p (it1->first, it2->first);
//        relation.add_cause_effect (p);
//      }
//    }
//  }
//  this->relations_.push_back (relation);
//}

//
// New version of extract variable relations
//
void CUTS_Dmac_Log_Format::
extract_variable_relations (CUTS_Dmac_Log_Format * log_format)
{
  std::map <int, std::string>::iterator it1;
  std::map <int, std::string>::iterator it2;
  std::vector <CUTS_DMAC_UTILS::int_pair> temp;
  CUTS_Dmac_Relation relation (log_format);

  for (it1 = this->msg_instances_ [0].var_table_.begin ();
       it1 != this->msg_instances_ [0].var_table_.end ();
       it1++)
  {
    for (it2 = log_format->msg_instances_ [0].var_table_.begin ();
         it2 != log_format->msg_instances_ [0].var_table_.end ();
         it2++)
    {
      CUTS_DMAC_UTILS::int_pair p (it1->first, it2->first);
      temp.push_back (p);
    }
  }

  std::vector <CUTS_DMAC_UTILS::int_pair>::iterator it3;
  std::vector <CUTS_Dmac_Log_Msg_Details>::iterator it4, it5;

  for (it3 = temp.begin (); it3 != temp.end (); it3++)
  {
    bool equal = false;
    for (it4 = this->msg_instances_.begin ();
         it4 != this->msg_instances_.end ();
         it4++)
    {
      equal = false;
      for (it5 = log_format->msg_instances_.begin ();
           it5 != log_format->msg_instances_.end ();
           it5++)
      {
        if (it4->time_val_ <= it5->time_val_)
        {
          if (it4->var_table_ [it3->first] ==
              it5->var_table_ [it3->second])
          {
            equal = true;
            break;
          }
        }
        else
          break;
      }
    }
    if (equal)
      relation.add_cause_effect (*it3);
  }
}


//
// match_item_set
//
bool CUTS_Dmac_Log_Format::
match_item_set (CUTS_DMAC_UTILS::string_vector & values1,
                CUTS_DMAC_UTILS::string_vector & values2)
{
  // Checking whether the two sets of variables
  // are the same

  int i;
  int j;
  int min_size;
  int max_size;

  CUTS_DMAC_UTILS::string_vector::size_type size1 = values1.size ();
  CUTS_DMAC_UTILS::string_vector::size_type size2 = values2.size ();

  CUTS_DMAC_UTILS::string_vector big_list;
  CUTS_DMAC_UTILS::string_vector small_list;

  // If the sizes of the two sets are differe we are
  // checking whether one set is a subset of the other.

  if (size1 > size2)
  {
    min_size = size2;
    max_size = size1;
    big_list = values1;
    small_list = values2;
  }
  else
  {
    min_size = size1;
    max_size = size2;
    big_list = values2;
    small_list = values1;
  }

  // We always need to check whether the values
  // of the small set contained in the big set.

  bool is_subset = false;

  for (i=0; i < min_size; i++)
  {
    for (j=0; j < max_size; j++)
    {
      is_subset = false;
      if (small_list [i] == big_list [j])
      {
        is_subset = true;
        break;
      }
    }
    if (!is_subset)
      return is_subset;
  }
  return true;
}

//
// log_format_items
//
CUTS_DMAC_UTILS::string_vector & CUTS_Dmac_Log_Format::
log_format_items ()
{
  return this->log_format_items_;
}

int CUTS_Dmac_Log_Format::id ()
{
  return this->id_;
}

//
// print_relations
//
void CUTS_Dmac_Log_Format::
print_relations ()
{
  std::vector <CUTS_Dmac_Relation>::iterator it;

  for (it = this->relations_.begin (); it != this->relations_.end (); it++)
    (*it).print_relation (this);
}


//
// serialize
//
void CUTS_Dmac_Log_Format::
serialize (std::ofstream & xml_content)
{

  // Name of the log format
  xml_content
    << "<logformat id=\"LF" << this->id_ << "\">" << std::endl
    << "<value>";

  CUTS_DMAC_UTILS::s_iter it1;
  int var_count = 0;

  // Value of the log format
  for (it1 = this->log_format_items_.begin ();
       it1 != (this->log_format_items_.end () - 1); it1++)
  {
    if ((*it1) == "{}")
      this->serialize_variable (xml_content, var_count);

    else
    {
      xml_content
        << (*it1);
    }
    xml_content
      <<" ";
  }

  if ((*it1) == "{}")
    this->serialize_variable (xml_content, var_count);
  else
  {
      xml_content
        << (*it1);
  }
  xml_content
    << "</value>" << std::endl;

  // Convert the relations to xml
  if (!this->relations_.empty ())
  {
    std::vector <CUTS_Dmac_Relation>::iterator it2;

    xml_content
      << "<relations>" << std::endl;

    for (it2 = this->relations_.begin ();
         it2 != this->relations_.end (); it2++)
    {
      (*it2).serialize (xml_content);
    }
    xml_content
      << "</relations>" << std::endl;
  }

  xml_content
    << " </logformat>" << std::endl;
}

//
// serialize_variable
//
void CUTS_Dmac_Log_Format::
serialize_variable (std::ofstream & xml_content,
                    int & count)
{
  count++;
  xml_content
    << "{STRING X" << count <<"}";
}

//
// coverage
//
long CUTS_Dmac_Log_Format::coverage ()
{
  return this->coverage_;
}

//
// increment_coverage
//
void CUTS_Dmac_Log_Format::increment_coverage ()
{
  this->coverage_++;
}

bool CUTS_Dmac_Log_Format::
is_reachable (CUTS_Dmac_Log_Format * lf)
{
  if (this->relations_.empty ())
    return false;

  std::vector <CUTS_Dmac_Relation>::iterator it;
  std::vector <CUTS_Dmac_Relation>::iterator first =
    this->relations_.begin ();
  std::vector <CUTS_Dmac_Relation>::iterator last =
    this->relations_.end ();

  for (it = first; it != last; it++)
  {
    if (it->effect_lf_->id () == lf->id ())
      return true;
    else if (it->effect_lf_->is_reachable (lf))
      return true;
  }
  return false;
}

void CUTS_Dmac_Log_Format::
insert_msg_instance (ADBC::SQLite::Record * record,
                     CUTS_DMAC_UTILS::string_vector & trace)
{
  CUTS_Dmac_Log_Msg_Details msg_details;
  long lid = 0;
  ACE_Date_Time date_time;

  record->get_data (0, lid);
  record->get_data (1, date_time);

  double time_val = CUTS_DMAC_UTILS::get_seconds_since_1970 (date_time);

  msg_details.lid_ = lid;
  msg_details.time_val_ = time_val;

  // Keep the values of variables

  CUTS_DMAC_UTILS::s_iter it;
  std::string empty_str ("{}");

  int j = 0;
  for (unsigned int i = 0; i < this->log_format_items_.size (); i++)
  {
    if (this->log_format_items_ [i].compare (empty_str) == 0)
    {
      j++;
      msg_details.var_table_.insert (std::pair <int, std::string>(j, trace [i]));
    }
  }

  this->msg_instances_.push_back (msg_details);
}

void CUTS_Dmac_Log_Format::
sort_msg_instances (void)
{
  if (!this->sorted_)
  {
    /*std::sort (this->msg_instances_.begin (),
               this->msg_instances_.end (),
               compare_time);*/
    this->sorted_ = true;
  }
}

std::vector <CUTS_Dmac_Log_Msg_Details> & CUTS_Dmac_Log_Format::
msg_instances (void)
{
  return this->msg_instances_;
}