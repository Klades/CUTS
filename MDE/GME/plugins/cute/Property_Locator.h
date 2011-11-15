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

#include "game/mga/FCO.h"
#include "game/mga/Visitor.h"
#include "cuts/utils/Property_Evaluator_T.h"
#include "cuts/utils/Property_Evaluator_List_Actor.h"
#include "Model_Interpreter_Action_List.h"

// Forward decl.
class CUTS_CUTE_Property_Locator_Handler;

/**
 * @class CUTS_CUTE_Property_Locator
 */
class CUTS_CUTE_Property_Locator : public GAME::Mga::Visitor
{
public:

  /// Default constructor.
  CUTS_CUTE_Property_Locator (CUTS_CUTE_Property_Locator_Handler & handler);

  /// Destructor.
  virtual ~CUTS_CUTE_Property_Locator (void);

  virtual void visit_Folder (GAME::Mga::Folder_in folder);

  virtual void visit_Model (GAME::Mga::Model_in model);

private:
  void visit_FCO (GAME::Mga::FCO_in fco);

  void visit_Attribute (GAME::Mga::Attribute_in attr);

  /// The handler for receiving notifications.
  CUTS_CUTE_Property_Locator_Handler & handler_;

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
