// $Id$

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Property_Parser

//
// parse
//
template <typename IteratorT>
bool CUTS_Property_Parser::parse (IteratorT begin, IteratorT end)
{
  CUTS_Property_Parser_i parser (this->prop_map_);

  boost::spirit::parse_info <IteratorT> info =
    boost::spirit::parse (begin, end, parser, boost::spirit::space_p);

  return info.full;
}

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Property_Parser_i::definition

//
// definition
//
template <typename ScannerT>
CUTS_Property_Parser::CUTS_Property_Parser_i::definition <ScannerT>::
definition (CUTS_Property_Parser_i const & self)
{
  this->property_name_ =
    boost::spirit::lexeme_d [*(boost::spirit::print_p - '=')];

  this->property_value_ =
    *(boost::spirit::anychar_p - boost::spirit::eol_p);

  this->property_ =
    this->property_name_[boost::spirit::assign_a (this->name_)] >> '=' >>
    this->property_value_[boost::spirit::assign_a (this->value_)];

  this->property_list_ =
    boost::spirit::list_p (
      this->property_[
        actors::insert_property (self.prop_map_, this->name_, this->value_)],
          boost::spirit::eol_p);
}

//
// start
//
template <typename ScannerT>
const boost::spirit::rule <ScannerT> &
CUTS_Property_Parser::CUTS_Property_Parser_i::definition <ScannerT>::start (void) const
{
  return this->property_list_;
}
