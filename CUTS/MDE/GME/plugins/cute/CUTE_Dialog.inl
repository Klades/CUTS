//  -*- C++ -*-
// $Id$

//
// CUTS_CUTE_Dialog
//
CUTS_INLINE
CUTS_CUTE_Dialog::CUTS_CUTE_Dialog (CWnd * parent)
: CDialog (IDD_CUTE, parent),
  list_ (0)
{

}

//
// ~CUTS_CUTE_Dialog
//
CUTS_INLINE
CUTS_CUTE_Dialog::~CUTS_CUTE_Dialog (void)
{

}

//
// interpreter_list
//
CUTS_INLINE
void CUTS_CUTE_Dialog::interpreter_list (CUTS_CUTE_Interpreter_List * list)
{
  this->list_ = list;
}

//
// interpreter_list
//
CUTS_INLINE
CUTS_CUTE_Interpreter_List * CUTS_CUTE_Dialog::interpreter_list (void)
{
  return this->list_;
}

//
// selected_interpreter
//
CUTS_INLINE
const CString & CUTS_CUTE_Dialog::selected_interpreter (void) const
{
  return this->selected_interpeter_;
}

//
// configuation_filename
//
CUTS_INLINE
const CString & CUTS_CUTE_Dialog::configuration_filename (void) const
{
  return this->config_file_;
}

//
// parameters
//
CUTS_INLINE
const CString & CUTS_CUTE_Dialog::parameters (void) const
{
  return this->parameters_;
}
