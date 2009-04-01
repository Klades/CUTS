// $Id$

#include "Log_Format.h"
#include "Log_Format_Compiler.h"
#include "Variable.h"
#include "ace/CORBA_macros.h"
#include "pcre.h"

//
// CUTS_Log_Format
//
CUTS_Log_Format::CUTS_Log_Format (const ACE_CString & name)
: name_ (name),
  expr_ (0),
  extra_ (0),
  captures_size_ (0)
{

}

//
// ~CUTS_Log_Format
//
CUTS_Log_Format::~CUTS_Log_Format (void)
{
  if (this->expr_ != 0)
    ::pcre_free (this->expr_);

  if (this->extra_ != 0)
    ::pcre_free (this->extra_);

  // Make sure to release the variable table resources.
  CUTS_Log_Format_Variable_Table::ITERATOR iter (this->vars_);

  for ( ; !iter.done (); ++ iter)
    delete iter->item ();
}

//
// compile
//
bool CUTS_Log_Format::compile (const ACE_CString & format)
{
  // Reset the log format.
  this->reset ();

  // First, convert the high-level expression into a PCRE.
  std::ostringstream expr;
  CUTS_Log_Format_Compiler compiler;

  if (!compiler.compile (format.c_str (), expr, this->vars_))
    return false;

  const char * error = 0;
  int error_offset;

  // Compile the PCRE version of the log format.
  this->expr_ = ::pcre_compile (expr.str ().c_str (),
                                0,
                                &error,
                                &error_offset,
                                0);

  // Let's try and study the expression.
  this->extra_ = ::pcre_study (this->expr_, 0, &error);

  if (this->expr_ != 0)
  {
    int * captures = 0;
    this->captures_size_ = (this->vars_.current_size ()  + 1) * 3;

    ACE_NEW_THROW_EX (captures,
                      int [this->captures_size_],
                      ACE_bad_alloc ());

    this->captures_.reset (captures);
  }

  return this->expr_ != 0;
}

//
// match
//
bool CUTS_Log_Format::match (const ACE_CString & message) const
{
  int retval = ::pcre_exec (this->expr_,
                            this->extra_,
                            message.c_str (),
                            message.length (),
                            0,
                            0,
                            this->captures_.get (),
                            this->captures_size_);

  if (retval > 1)
  {
    // Update the variables.
    CUTS_Log_Format_Variable * variable = 0;
    const char * msgrep = message.rep ();

    for (CUTS_Log_Format_Variable_Table::CONST_ITERATOR iter (this->vars_);
        !iter.done ();
        ++ iter)
    {
      variable = iter->item ();

      // Calculate the variables offset in the captures.
      size_t offset = (variable->index () + 1) * 2;
      int * capture = this->captures_.get () + offset;

      // Set the value of the variable.
      variable->value (msgrep + *capture, msgrep + *(capture + 1));
    }
  }

  return retval > 0;
}

//
// reset
//
void CUTS_Log_Format::reset (void)
{
  // Reset the state of the PCRE variables.
  if (this->expr_ != 0)
  {
    ::pcre_free (this->expr_);
    this->expr_ = 0;
  }

  if (this->extra_ != 0)
  {
    ::pcre_free (this->extra_);
    this->extra_ = 0;
  }

  if (this->captures_size_ > 0)
  {
    this->captures_.reset ();
    this->captures_size_ = 0;
  }

  // Make sure to release the variable table resources.
  CUTS_Log_Format_Variable_Table::ITERATOR iter (this->vars_);

  for ( ; !iter.done (); ++ iter)
    delete iter->item ();

  this->vars_.unbind_all ();
}

//
// name
//
const ACE_CString & CUTS_Log_Format::name (void) const
{
  return this->name_;
}

//
// variables
//
const CUTS_Log_Format_Variable_Table &
CUTS_Log_Format::variables (void) const
{
  return this->vars_;
}

//
// relations
//
CUTS_Log_Format::relations_type & CUTS_Log_Format::relations (void)
{
  return this->relations_;
}

//
// relations
//
const CUTS_Log_Format::relations_type & CUTS_Log_Format::relations (void) const
{
  return this->relations_;
}

//
// is_valid
//
bool CUTS_Log_Format::is_valid (void) const
{
  return this->expr_ != 0;
}
