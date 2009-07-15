// $Id$

//
// CUTS_CUTE_Model_Interpreter
//
CUTS_INLINE
CUTS_CUTE_Model_Interpreter::
CUTS_CUTE_Model_Interpreter (CUTS_CUTE_Model_Interpreter_Action_List & actlist,
                             CUTS_Property_Map & params,
                             GME::Project & project,
                             GME::FCO & target,
                             GME::Collection_T <GME::FCO> & selected,
                             long flags)
: actlist_ (actlist),
  params_ (params),
  project_ (project),
  target_ (target),
  selected_ (selected),
  flags_ (flags)
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
