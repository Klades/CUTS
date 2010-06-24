// -*- C++ -*-

//=============================================================================
/**
 * @file        Property_Locator.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CUTE_PROPERTY_LOCATOR_H_
#define _CUTS_CUTE_PROPERTY_LOCATOR_H_

#include "game/FCO.h"
#include "game/Visitor.h"
#include "cuts/utils/Property_Evaluator_T.h"
#include "cuts/utils/Property_Evaluator_List_Actor.h"
#include "Model_Interpreter_Action_List.h"

/**
 * @class CUTS_CUTE_Property_Locator
 */
class CUTS_CUTE_Property_Locator : public GAME::Visitor
{
public:

  /// Default constructor.
  CUTS_CUTE_Property_Locator (CUTS_CUTE_Model_Interpreter_Action_List & actions);

  /// Destructor.
  virtual ~CUTS_CUTE_Property_Locator (void);

  virtual void visit_Folder (GAME::Folder & folder);

  virtual void visit_Model (GAME::Model & model);

  virtual void visit_FCO (GAME::FCO & fco);

private:
  void visit_Attribute (GAME::Attribute & attr);

  /// Map that holds located items.
  CUTS_CUTE_Model_Interpreter_Action_List & actions_;

  CUTS_Property_Map prop_map_;

  CUTS_Property_Evaluator_List_Actor actor_;

  typedef CUTS_Property_Evaluator_List_Actor::list_type list_type;

  typedef
    CUTS_Property_Evaluator_T <CUTS_Property_Evaluator_List_Actor>
    evaluator_type;

  evaluator_type evaluator_;
};

#if defined (__CUTS_INLINE__)
#include "Property_Locator.inl"
#endif

#endif  // !defined _CUTS_CUTE_PROPERTY_LOCATOR_H_
