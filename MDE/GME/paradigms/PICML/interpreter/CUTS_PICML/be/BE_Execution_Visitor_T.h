// -*- C++ -*-

//=============================================================================
/**
 * @file      BE_Execution_Visitor_T.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_EXECUTION_VISITOR_H_
#define _CUTS_BE_EXECUTION_VISITOR_H_

#include "PICML/PICML.h"
#include "PICML/Visitor.h"
#include <stack>

//=============================================================================
/**
 * @class CUTS_BE_Execution_Visitor_T
 *
 * Visitor responsible for parsing the execution paths. It signals
 * the generators when to write the appropriate information.
 */
//=============================================================================

template <typename CONTEXT>
class CUTS_BE_Execution_Visitor_T : public PICML::Visitor
{
public:
  /// Type definition of the context type.
  typedef CONTEXT context_type;

  /**
   * Initializing constructor.
   *
   * @param[in]       generators      Reference to target generators.
   */
  CUTS_BE_Execution_Visitor_T (CONTEXT & context);

  /// Destructor.
  virtual ~CUTS_BE_Execution_Visitor_T (void);

  void generate (const PICML::SingleInputBase_in input);

  void generate (const PICML::MultiInputBase_in input);

protected:
  /// Visit an MultiInput element.
  void Visit_MultiInput (const PICML::MultiInput_in input);

  /// Visit an InputAction element.
  void Visit_Input (const PICML::Input_in input);

  /// Visit an MulitInputAction
  void Visit_MultiInputAction (const PICML::MultiInputAction_in);

  /// Visit an InputAction element.
  void Visit_InputAction (const PICML::InputAction_in);

  /// Visit an Effect element.
  void Visit_InputEffect (const PICML::InputEffect_in);

  /// Visit an Effect element.
  void Visit_Effect (const PICML::Effect_in);

  /// Visit a State element.
  void Visit_State (const PICML::State_in);

  /// Visit a BranchState connection.
  void Visit_BranchState (const PICML::BranchState_in);

  /// Visit a Transition element.
  void Visit_Transition (const PICML::Transition_in);

  /// Visit a BranchTransition element.
  void Visit_BranchTransition (const PICML::BranchTransition_in);

  /// Visit a DoWhileState element.
  void Visit_DoWhileState (const PICML::DoWhileState_in);

  void Visit_WhileState (const PICML::WhileState_in);

  void Visit_ForState (const PICML::ForState_in);

  /// Visit a Property element.
  void Visit_SimpleProperty (const PICML::SimpleProperty_in);

  /// Visit an Action element.
  void Visit_Action (const PICML::Action_in);

  /// Visit an OutputAction element.
  void Visit_OutputAction (const PICML::OutputAction_in);

  void Visit_RequestAction (const PICML::RequestAction_in);

  ///// Visit a CompositeAction element.
  //void Visit_CompositeAction (const PICML::CompositeAction &);

  void Visit_TerminalTransition (const PICML::TerminalTransition_in);

  void Visit_Terminal (const PICML::Terminal_in);

  void Visit_TerminalEffect (const PICML::TerminalEffect_in);

  void Visit_LoopTransition (const PICML::LoopTransition_in);

protected:
  void Visit_OutputAction_Property (const PICML::Property_in property);

private:
  void Visit_ActionBase (const PICML::ActionBase_in);

  void Visit_LoopState (const PICML::LoopState_in);

  void goto_to_terminal (void);

  CONTEXT & context_;

  /// Flag that determines if effects should be ignored.
  bool ignore_effects_;

  /// Current depth of the flow control.
  int depth_;

  /// Type definition for a ordered collection of return states
  typedef std::stack <PICML::Terminal> Terminal_State;

  /// Collection of ordered return states.
  Terminal_State terminal_state_;

  typedef std::stack <PICML::BehaviorInputAction> Action_Stack;

  Action_Stack action_stack_;

  typedef std::stack <PICML::StateBase> StateBase_Stack;

  StateBase_Stack statebase_stack_;

  std::stack <size_t> branches_;

  // prevent the following operations
  CUTS_BE_Execution_Visitor_T (CUTS_BE_Execution_Visitor_T &);
  const CUTS_BE_Execution_Visitor_T & operator = (const CUTS_BE_Execution_Visitor_T &);
};

#include "BE_Execution_Visitor_T.cpp"

#endif  // !defined _CUTS_BE_EXECUTION_VISITOR_H_
