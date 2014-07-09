// $Id$

#include "ace/OS_Memory.h"
#include "ace/OS_NS_stdio.h"
#include "Log_Format.h"
#include "Log_Format_Compiler.h"
#include "Variable.h"
#include "ace/CORBA_macros.h"
#include "pcre.h"
#include "Log_Format_Adapter.h"


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
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - log format is invalid\n")
                       ACE_TEXT ("  expr: %s\n")
                       ACE_TEXT ("  eval: %s\n"),
                       format.c_str (),
                       expr.str ().c_str ()),
                       false);

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
bool CUTS_Log_Format::match (const ACE_CString & message,
                             CUTS_Log_Format_Adapter * adapter)
{
  ACE_Guard <ACE_Thread_Mutex> guard (this->mutex_);

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
    // If adapter is set we will first allow the adapter to update,
    // Becasue for the variables added from the adapter we can't populate
    // from the message. Adpater will set a flag which tells whether this
    // variable is a one which needed to be populated from the message.
    // Depending on that flag the variable will be populated.

    CUTS_Log_Format_Variable * variable = 0;
    bool adapter_required = false;
    const char * msgrep = message.c_str ();
    int * capture = 0;

    for (CUTS_Log_Format_Variable_Table::CONST_ITERATOR iter (this->vars_);
        !iter.done ();
        ++ iter)
    {
      variable = iter->item ();
      size_t offset = (variable->index () + 1) * 2;
      capture = this->captures_.get () + offset;

      // Set the value of the variable.

      if (*capture < 0)
        adapter_required = true;
      else
        variable->value (msgrep + *capture, msgrep + *(capture + 1));
    }

    if (adapter && adapter_required)
      adapter->update_values (this->vars_, this);
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

CUTS_Log_Format_Variable_Table &
CUTS_Log_Format::variables (void)
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

//
// Set the captures_size
//
void CUTS_Log_Format::captures_size (size_t size)
{
  this->captures_size_ = size;

}

//
//  Get the captures_size
//
size_t CUTS_Log_Format::captures_size (void)
{
  return this->captures_size_;
}

//
//  Get the Captures array
//
ACE_Auto_Array_Ptr <int> & CUTS_Log_Format::captures (void)
{
  return this->captures_;
}