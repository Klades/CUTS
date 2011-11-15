// $Id$

#if !defined (__CUTS_INLINE__)
#include "Property_Evaluator_T.inl"
#endif

//
// evaluate
//
template <typename ACTOR>
bool CUTS_Property_Evaluator_T <ACTOR>::evaluate (const char * str)
{
  boost::spirit::parse_info < > info =
    boost::spirit::parse (str, this->grammar_);

  return info.full;
}

//
// evaluate
//
template <typename ACTOR>
template <typename IteratorT>
bool CUTS_Property_Evaluator_T <ACTOR>::
evaluate (IteratorT begin, IteratorT end)
{
  boost::spirit::parse_info <IteratorT> info =
    boost::spirit::parse (begin, end, this->grammar_);

  return info.full;
}
