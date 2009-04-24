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
void CUTS_CUTE_Dialog::interpreter_list (ACE_Unbounded_Set <ACE_CString> * list)
{
  this->list_ = list;
}

//
// interpreter_list
//
CUTS_INLINE
ACE_Unbounded_Set <ACE_CString> * CUTS_CUTE_Dialog::interpreter_list (void)
{
  return this->list_;
}
