#include "Dmac_Log_Format.h"



//
// CUTS_Dmac_Log_Format
//
CUTS_Dmac_Log_Format::CUTS_Dmac_Log_Format (
    int id,
    CUTS_DMAC_UTILS::string_vector & log_format_items)
  : id_ (id),
    log_format_items_ (log_format_items),
    coverage_ (0)
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
void CUTS_Dmac_Log_Format::add_varaible_values (CUTS_DMAC_UTILS::string_vector & trace)
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
// extract_variable_relations
//
void CUTS_Dmac_Log_Format::extract_variable_relations (CUTS_Dmac_Log_Format * log_format,
                                                       CUTS_Dmac_Execution * execution)
{
  var_iterator it1;
  var_iterator it2;

  // Add an execution containing this relation
  this->add_execution (execution);
  log_format->add_execution (execution);

  CUTS_Dmac_Relation relation (log_format, execution);

  // If the set of values for any two variables on the
  // log format are the same then they have a possible
  // cause-effect relationship
  for (it1 = this->vars_.begin (); it1 != this->vars_.end (); it1++)
  {
    for (it2 = log_format->vars_.begin ();
          it2 != log_format->vars_.end (); it2++)
    {
      if (this->match_item_set (it1->second, it2->second))
      {
        CUTS_DMAC_UTILS::int_pair p (it1->first, it2->first);
        relation.add_cause_effect (p);
      }
    }
  }
  this->relations_.push_back (relation);
}

//
// match_item_set
//
bool CUTS_Dmac_Log_Format::match_item_set (CUTS_DMAC_UTILS::string_vector & values1,
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
CUTS_DMAC_UTILS::string_vector & CUTS_Dmac_Log_Format::log_format_items ()
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
void CUTS_Dmac_Log_Format::print_relations (CUTS_Dmac_Execution * execution)
{
  std::vector <CUTS_Dmac_Relation>::iterator it;

  for (it = this->relations_.begin (); it != this->relations_.end (); it++)
    (*it).print_relation (this, execution);
}

//
// compare_relations
//
bool CUTS_Dmac_Log_Format::compare_relations (CUTS_Dmac_Log_Format * log_format)
{
  if (this->relations_.size () != log_format->relations_.size ())
      return false;

  std::vector <CUTS_Dmac_Relation>::iterator it1;
  std::vector <CUTS_Dmac_Relation>::iterator it2;

  for (it1 = this->relations_.begin ();
        it1 != this->relations_.end (); it1++)
  {
    for (it2 = log_format->relations_.begin ();
          it2 != log_format->relations_.end (); it2++)
    {
      if ((*it1) != (*it2))
        return false;
    }
  }
  return true;
}

//
// serialize
//
void CUTS_Dmac_Log_Format::serialize (std::ofstream & xml_content,
                                      CUTS_Dmac_Execution * ex)
{
  // Serialization is done only if the log format is in the
  // given execution
  if (!this->in_execution_list (ex))
    return;

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
      if (ex == (*it2).execution ())
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
void CUTS_Dmac_Log_Format::serialize_variable (std::ofstream & xml_content,
                                               int & count)
{
  count++;
  xml_content
    << "{STRING X" << count <<"}";
}

//
// add_execution
//
void CUTS_Dmac_Log_Format::add_execution (CUTS_Dmac_Execution * ex)
{
  if (!this->in_execution_list (ex))
    this->content_list_.push_back (ex);
}

//
// in_execution_list
//
bool CUTS_Dmac_Log_Format::in_execution_list (CUTS_Dmac_Execution * ex)
{
  // Check whether this log format is contained in the
  // execution
  std::vector <CUTS_Dmac_Execution *>::iterator it;

  for (it = this->content_list_.begin ();
       it != this->content_list_.end (); it++)
  {
    if ((*it) == ex)
      return true;
  }
  return false;
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