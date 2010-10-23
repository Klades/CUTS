// $Id$

//
// CUTS_CUTE_Model_Interpreter
//
CUTS_INLINE
CUTS_CUTE_Model_Interpreter::
CUTS_CUTE_Model_Interpreter (const CUTS_CUTE_Model_Interpreter_Action_List & actlist,
                             const CUTS_Property_Map & params,
                             GAME::Project project,
                             GAME::FCO target,
                             const std::vector <GAME::FCO> & selected,
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
