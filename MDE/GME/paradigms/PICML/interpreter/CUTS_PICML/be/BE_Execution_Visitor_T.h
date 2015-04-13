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
  void visit_MultiInput (PICML::MultiInput_in input);

  /// Visit an InputAction element.
  void visit_Input (PICML::Input_in input);

  /// Visit an MulitInputAction
  void visit_MultiInputAction (PICML::MultiInputAction_in);

  /// Visit an InputAction element.
  void visit_InputAction (PICML::InputAction_in);

  /// Visit an Effect element.
  void visit_InputEffect (PICML::InputEffect_in);

  /// Visit an Effect element.
  void visit_Effect (PICML::Effect_in);

  /// Visit a State element.
  void visit_State (PICML::State_in);

  /// Visit a BranchState connection.
  void visit_BranchState (PICML::BranchState_in);

  /// Visit a Transition element.
  void visit_Transition (PICML::Transition_in);

  /// Visit a BranchTransition element.
  void visit_BranchTransition (PICML::BranchTransition_in);

  /// Visit a DoWhileState element.
  void visit_DoWhileState (PICML::DoWhileState_in);

  void visit_WhileState (PICML::WhileState_in);

  void visit_ForState (PICML::ForState_in);

  /// Visit a Property element.
  void visit_SimpleProperty (PICML::SimpleProperty_in);

  /// Visit an Action element.
  void visit_Action (PICML::Action_in);

  /// Visit an OutputAction element.
  void visit_OutputAction (PICML::OutputAction_in);

  void visit_RequestAction (PICML::RequestAction_in);

  ///// Visit a CompositeAction element.
  //void visit_CompositeAction (PICML::CompositeAction_in);

  void visit_TerminalTransition (PICML::TerminalTransition_in);

  void visit_Terminal (PICML::Terminal_in);

  void visit_TerminalEffect (PICML::TerminalEffect_in);

  void visit_LoopTransition (PICML::LoopTransition_in);

protected:
  void visit_OutputAction_Property (PICML::Property_in property);

private:
  void visit_ActionBase (PICML::ActionBase_in);

  void visit_LoopState (PICML::LoopState_in);

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
