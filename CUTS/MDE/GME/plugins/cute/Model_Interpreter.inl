// $Id$

//
// CUTS_CUTE_Model_Interpreter
//
CUTS_INLINE
CUTS_CUTE_Model_Interpreter::
CUTS_CUTE_Model_Interpreter (CUTS_CUTE_Model_Interpreter_Action_List & actlist,
                             GME::Project & project,
                             GME::FCO & target,
                             GME::Collection_T <GME::FCO> & selected,
                             long flags)
: actlist_ (actlist),
  project_ (project),
  target_ (target),
  selected_ (selected),
  flags_ (flags)
{

}

//
// ~CUTS_CUTE_Model_Interpreter
//
CUTS_INLINE
CUTS_CUTE_Model_Interpreter::~CUTS_CUTE_Model_Interpreter (void)
{

}

//
// interpreter
//
CUTS_INLINE
void CUTS_CUTE_Model_Interpreter::
interpreter (const ACE_CString & interpreter)
{
  this->interpreter_ = interpreter;
}
