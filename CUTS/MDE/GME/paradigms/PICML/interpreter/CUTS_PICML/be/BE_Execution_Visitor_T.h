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

  void generate (const PICML::SingleInputBase & input);

  void generate (const PICML::MultiInputBase & input);

protected:
  /// Visit an MultiInput element.
  void Visit_MultiInput (const PICML::MultiInput & input);

  /// Visit an InputAction element.
  void Visit_Input (const PICML::Input & input);

  /// Visit an MulitInputAction
  void Visit_MultiInputAction (const PICML::MultiInputAction &);

  /// Visit an InputAction element.
  void Visit_InputAction (const PICML::InputAction &);

  /// Visit an Effect element.
  void Visit_InputEffect (const PICML::InputEffect &);

  /// Visit an Effect element.
  void Visit_Effect (const PICML::Effect &);

  /// Visit a State element.
  void Visit_State (const PICML::State &);

  /// Visit a BranchState connection.
  void Visit_BranchState (const PICML::BranchState &);

  /// Visit a Transition element.
  void Visit_Transition (const PICML::Transition &);

  /// Visit a BranchTransition element.
  void Visit_BranchTransition (const PICML::BranchTransition &);

  /// Visit a DoWhileState element.
  void Visit_DoWhileState (const PICML::DoWhileState & );

  void Visit_WhileState (const PICML::WhileState &);

  /// Visit a Property element.
  void Visit_Property (const PICML::Property &);

  /// Visit an Action element.
  void Visit_Action (const PICML::Action &);

  /// Visit an OutputAction element.
  void Visit_OutputAction (const PICML::OutputAction &);

  ///// Visit a CompositeAction element.
  //void Visit_CompositeAction (const PICML::CompositeAction &);

  void Visit_TerminalTransition (const PICML::TerminalTransition &);

  void Visit_Terminal (const PICML::Terminal &);

  void Visit_TerminalEffect (const PICML::TerminalEffect &);

  void Visit_LoopTransition (const PICML::LoopTransition &);

protected:
  void Visit_OutputAction_Property (const PICML::Property & property);

private:
  void Visit_StateBase (const PICML::StateBase &);

  void Visit_ActionBase (const PICML::ActionBase &);

  void Visit_LoopState (const PICML::LoopState &);

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
