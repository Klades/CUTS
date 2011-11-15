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

#include "../../paradigms/CHAOS.h"
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
class CUTS_BE_Execution_Visitor_T : public CHAOS::Visitor
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

  void generate (const CHAOS::SingleInputBase & input);

  void generate (const CHAOS::MultiInputBase & input);

protected:
  /// Visit an MultiInput element.
  void Visit_MultiInput (const CHAOS::MultiInput & input);

  /// Visit an InputAction element.
  void Visit_Input (const CHAOS::Input & input);

  /// Visit an MulitInputAction
  void Visit_MultiInputAction (const CHAOS::MultiInputAction &);

  /// Visit an InputAction element.
  void Visit_InputAction (const CHAOS::InputAction &);

  /// Visit an Effect element.
  void Visit_InputEffect (const CHAOS::InputEffect &);

  /// Visit an Effect element.
  void Visit_Effect (const CHAOS::Effect &);

  /// Visit a State element.
  void Visit_State (const CHAOS::State &);

  /// Visit a BranchState connection.
  void Visit_BranchState (const CHAOS::BranchState &);

  /// Visit a Transition element.
  void Visit_Transition (const CHAOS::Transition &);

  /// Visit a BranchTransition element.
  void Visit_BranchTransition (const CHAOS::BranchTransition &);

  /// Visit a DoWhileState element.
  void Visit_DoWhileState (const CHAOS::DoWhileState & );

  void Visit_WhileState (const CHAOS::WhileState &);

  /// Visit a Property element.
  void Visit_Property (const CHAOS::Property &);

  /// Visit an Action element.
  void Visit_Action (const CHAOS::Action &);

  /// Visit an OutputAction element.
  void Visit_OutputAction (const CHAOS::OutputAction &);

  ///// Visit a CompositeAction element.
  //void Visit_CompositeAction (const CHAOS::CompositeAction &);

  void Visit_TerminalTransition (const CHAOS::TerminalTransition &);

  void Visit_Terminal (const CHAOS::Terminal &);

  void Visit_TerminalEffect (const CHAOS::TerminalEffect &);

  void Visit_LoopTransition (const CHAOS::LoopTransition &);

protected:
  void Visit_OutputAction_Property (const CHAOS::Property & property);

private:
  void Visit_StateBase (const CHAOS::StateBase &);

  void Visit_ActionBase (const CHAOS::ActionBase &);

  void Visit_LoopState (const CHAOS::LoopState &);

  void goto_to_terminal (void);

  CONTEXT & context_;

  /// Flag that determines if effects should be ignored.
  bool ignore_effects_;

  /// Current depth of the flow control.
  int depth_;

  /// Type definition for a ordered collection of return states
  typedef std::stack <CHAOS::Terminal> Terminal_State;

  /// Collection of ordered return states.
  Terminal_State terminal_state_;

  typedef std::stack <CHAOS::BehaviorInputAction> Action_Stack;

  Action_Stack action_stack_;

  typedef std::stack <CHAOS::StateBase> StateBase_Stack;

  StateBase_Stack statebase_stack_;

  std::stack <size_t> branches_;

  // prevent the following operations
  CUTS_BE_Execution_Visitor_T (CUTS_BE_Execution_Visitor_T &);
  const CUTS_BE_Execution_Visitor_T & operator = (const CUTS_BE_Execution_Visitor_T &);
};

#include "BE_Execution_Visitor_T.cpp"

#endif  // !defined _CUTS_BE_EXECUTION_VISITOR_H_
