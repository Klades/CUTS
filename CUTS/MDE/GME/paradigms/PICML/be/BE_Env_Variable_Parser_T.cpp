// $Id$

#include "boost/spirit/utility/confix.hpp"
#include "boost/spirit/actor.hpp"

struct append_a
{
  append_a (std::string & str)
    : str_ (str)
  {

  }

  template <typename IteratorT>
  void operator () (IteratorT begin, IteratorT end) const
  {
    std::string temp (begin, end);
    this->str_.append (temp);
  }

private:
  std::string & str_;
};

//
// CUTS_BE_Env_Variable_Parser_T
//
template <typename T>
CUTS_BE_Env_Variable_Parser_T <T>::
CUTS_BE_Env_Variable_Parser_T (std::string & out)
: out_ (out)
{

}

//
// definition
//
template <typename T>
template <typename ScannerT>
CUTS_BE_Env_Variable_Parser_T <T>::
definition <ScannerT>::definition (CUTS_BE_Env_Variable_Parser_T const & self)
{
  this->var_name_ = 
    *(boost::spirit::print_p - ')');

  this->text_ = 
    *(boost::spirit::print_p - '$');

  this->env_var_ = 
    boost::spirit::lexeme_d [
      boost::spirit::str_p ("$(") >> this->var_name_[T (self.out_)] >> ')'];

  this->content_ =
    this->text_ [append_a (self.out_)] >> 
    *(this->env_var_ >> this->text_ [append_a (self.out_)]);
}

//
// start
//
template <typename T>
template <typename ScannerT>
const boost::spirit::rule <ScannerT> &
CUTS_BE_Env_Variable_Parser_T <T>::definition <ScannerT>::start (void) const
{
  return this->content_;
}
