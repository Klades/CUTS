// $Id$

#include "Where_Clause_Builder.h"

#if !defined (__CUTS_INLINE__)
#include "Where_Clause_Builder.inl"
#endif

#include "ace/SString.h"
#include <strstream>

//
// operator <<
//
std::ostream & operator << (std::ostream & ostr, const ::CUTS::XML::expressionType & expr)
{
  if (expr.negate_p () && expr.negate ())
    ostr << "NOT(";

  ostr << expr.format ()
       << "_"
       << expr.variable ()
       << expr.value ();

  if (expr.negate_p () && expr.negate ())
    ostr << ")";

  return ostr;
}

/**
 * @struct insert_expression
 *
 * Functor that helps build the expression string.
 */
struct insert_expression
{
  /// Type definition of the expression type.
  typedef ::CUTS::XML::conditionType::expression_iterator::value_type value_type;

  insert_expression (const char * join_str, std::ostream & ostr)
    : join_str_ (join_str),
      ostr_ (ostr)
  {

  }

  void operator () (const value_type & value) const
  {
    this->ostr_ << this->join_str_ << value;
  }

private:
  const char * join_str_;

  std::ostream & ostr_;
};

/**
 * @struct insert_condition
 *
 * Functor that helps build the sub-condition string.
 */
struct insert_condition
{
  /// Type definition of the expression type.
  typedef ::CUTS::XML::conditionType::condition_iterator::value_type value_type;

  insert_condition (const char * join_str, std::ostream & ostr)
    : join_str_ (join_str),
      ostr_ (ostr)
  {

  }

  void operator () (const value_type & value) const
  {
    this->ostr_ << this->join_str_ << "(" << value << ")";
  }

private:
  const char * join_str_;

  std::ostream & ostr_;
};

//
// operator <<
//
std::ostream & operator << (std::ostream & ostr, const ::CUTS::XML::conditionType & cond)
{
  const char * join_str =
    cond.type () == CUTS::XML::joinType::conjunction ? " AND " : " OR ";

  if (cond.negate_p () && cond.negate ())
    ostr << "NOT(";

  // There is ALWAYS at least one expression in the condition.
  ::CUTS::XML::conditionType::expression_const_iterator iter = cond.begin_expression ();
  ostr << *iter;

  // Build the SQL expression for the condition.
  if (cond.count_expression () > 1)
    std::for_each (++ iter,
                   cond.end_expression (),
                   insert_expression (join_str, ostr));

  std::for_each (cond.begin_condition (),
                 cond.end_condition (),
                 insert_condition (join_str, ostr));

  if (cond.negate_p () && cond.negate ())
    ostr << ")";

  return ostr;
}

//
// build
//
int CUTS_Where_Clause_Builder::
build (const ::CUTS::XML::conditionType & condition,
       ACE_CString & result,
       bool prepend_where)
{
  std::ostringstream ostr;

  // First, prepend the WHERE statement, if necessary.
  if (prepend_where)
    ostr << "WHERE ";

  ostr << condition;
  result = ostr.str ().c_str ();

  return 0;
}
