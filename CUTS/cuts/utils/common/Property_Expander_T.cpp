// $Id$

#include "boost/spirit/utility/confix.hpp"

//
// expand
//
template <typename IteratorT>
bool CUTS_Property_Expander::
expand (IteratorT begin, IteratorT end, bool use_env, std::ostream & out)
{
  CUTS_Property_Expander_i parser (this->prop_map_, use_env, out);

  boost::spirit::parse_info <IteratorT> info =
    boost::spirit::parse (begin, end, parser);

  return info.full;
}


//
// definition
//
template <typename ScannerT>
CUTS_Property_Expander::CUTS_Property_Expander_i::
definition <ScannerT>::definition (CUTS_Property_Expander_i const & self)
{
  this->property_name_ =
    boost::spirit::lexeme_d[
      *(boost::spirit::print_p - '}')];

  this->text_ =
    *(boost::spirit::anychar_p - '$');

  this->property_ =
    boost::spirit::confix_p ("${",
      this->property_name_[expand (self.prop_map_, self.use_env_, self.ostr_)],
      "}");

  this->content_ =
    this->text_[append (self.ostr_)] >>
    *(this->property_>> this->text_[append (self.ostr_)]);
}

//
// definition
//
template <typename ScannerT>
const boost::spirit::rule <ScannerT> &
CUTS_Property_Expander::CUTS_Property_Expander_i::
definition <ScannerT>::start (void) const
{
  return this->content_;
}
