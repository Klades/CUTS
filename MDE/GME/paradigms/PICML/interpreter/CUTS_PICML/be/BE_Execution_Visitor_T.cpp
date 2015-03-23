// $Id$

#include "BE_algorithm.h"
#include "game/mga/modelgen.h"
#include "game/mga/utils/Position_Sort_T.h"
#include "game/mga/MetaModel.h"

// BOOST headers
#include "boost/bind.hpp"

// UDM headers
//#include "Uml.h"

// STL headers
#include <algorithm>
#include <sstream>

template <typename T, typename SORTER>
struct collection_sort
{
public:
std::vector <T> operator () (GAME::Mga::Collection_T <T> & collection, const std::string & aspect) const
{
  typedef GAME::Mga::Position_Sort_T <T, SORTER> sorter_t;
  sorter_t sorter (aspect, SORTER ());

  std::vector <T> result;

  for (T item : collection)
    result.push_back (item);

  std::sort (result.begin (), result.end (), sorter);
  return result;
}
};

/**
 * Functor used for sorting the branch transition. The sorting of
 * the branches is based on the position of its connecting action.
 * The actions are sorted from top to bottom, which corresponds to
 * the ordering of the statements. The bottom most action is the
 * only one that can have a branch transition with an empty condition.
 */
/*
struct CUTS_BE_BranchTransition_Sort
{
  struct Position
  {
    /// X-value of the position.
    long x;

    /// Y-value of the position
    long y;
*/
    /**
     * Extraction operator. This method takes a string and extracts
     * the coordinates from it. The format of the string should be
     * (x, y). If the source string does not have coordinates stored
     * in this format, it will cause unpredictable behavior.
     *
     * @param[in]     str     Source string with the x-,y-coordinates
     */
/*
    void operator <<= (const std::string & str)
    {
      char tmp;

      std::istringstream istr (str);

      istr >> tmp;
      istr >> this->x;
      istr >> tmp;
      istr >> this->y;
    }
  };
*/
  /**
   * Functor operation. This method will determine which object
   * is above the other object.
   */
/*
  bool operator () (const PICML::BranchTransition_in lhs,
                    const PICML::BranchTransition_in rhs)
  {
    PICML::ActionBase lhs_action (lhs->dst_ActionBase ());
    PICML::ActionBase rhs_action (rhs->dst_ActionBase ());

    Position lhs_pos;
    lhs_action->par
    lhs_pos <<= lhs_action->position ();

    Position rhs_pos;
    rhs_pos <<= rhs_action.position ();

    return lhs_pos.y < rhs_pos.y;
  }
};
*/

//
// CUTS_BE_Execution_Visitor_T
//
template <typename CONTEXT>
CUTS_BE_Execution_Visitor_T <CONTEXT>::
CUTS_BE_Execution_Visitor_T (CONTEXT & context)
: context_ (context),
  ignore_effects_ (false),
  depth_ (0)
{

}

//
// ~CUTS_BE_Execution_Visitor_T
//
template <typename CONTEXT>
CUTS_BE_Execution_Visitor_T <CONTEXT>::
~CUTS_BE_Execution_Visitor_T (void)
{

}

//
// generate
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
generate (const PICML::SingleInputBase_in base)
{
  if (base->has_src_of_Input ())
    CUTS_BE::visit <CONTEXT> (base->src_of_Input (),
      [this] (PICML::Input input) { input->accept (this);});
}


//
// generate
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
generate (const PICML::MultiInputBase_in base)
{
  for (auto input : base->src_of_MultiInput ())
    CUTS_BE::visit <CONTEXT> (inputs,
      [this] (PICML::MultiInput input) { input->accept (this);});
}

//
// visit_Input
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
visit_Input (PICML::Input_in input)
{
  CUTS_BE::visit <CONTEXT> (input->dst_InputAction (),
    [this] (PICML::InputAction action) { action->accept (this);});
}


//
// visit_MultiInput
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
visit_MultiInput (PICML::MultiInput_in input)
{
  CUTS_BE::visit <CONTEXT> (input->dst_MultiInputAction (),
    [this] (PICML::MultiInputAction action) { action->accept (this);});
}

//
// visit_InputAction
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
visit_InputAction (PICML::InputAction_in action)
{
  // Add the <action> to the top of the stack.
  this->action_stack_.push (action);

  // Visit the effect.
  if (action->has_src_of_InputEffect ())
    CUTS_BE::visit <CONTEXT> (action->src_of_InputEffect (),
      [this] (PICML::InputEffect effect) { effect->accept (this);});

  // Remove the <action> from the stack since we have
  // completed its behavior.
  this->action_stack_.pop ();
}

//
// visit_MultiInputAction
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
visit_MultiInputAction (PICML::MultiInputAction_in action)
{
  // Add the <action> to the top of the stack.
  this->action_stack_.push (action);

  // Visit the effect.
  if (action->has_src_of_InputEffect ())
    CUTS_BE::visit <CONTEXT> (action->src_of_InputEffect (),
      [this] (PICML::InputEffect effect) { effect->accept (this);});

  // Remove the <action> from the stack since we have
  // completed its behavior.
  this->action_stack_.pop ();
}

//
// visit_InputEffect
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
visit_InputEffect (PICML::InputEffect_in effect)
{
  // Write the postcondition for this <effect>.
  std::string postcondition = effect->Postcondition ();

  if (!postcondition.empty ())
  {
    CUTS_BE_Postcondition_T <CONTEXT> postcondition_gen (this->context_);
    postcondition_gen.generate (postcondition);
  }

  // Visit the next state in the chain.
  effect->dst_StateBase ()->accept (this);
}

//
// visit_Effect
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
visit_Effect (PICML::Effect_in effect)
{
  // Write the postcondition for this <effect>.
  std::string postcondition = effect->Postcondition ();

  if (!postcondition.empty ())
  {
    CUTS_BE_Postcondition_T <CONTEXT> postcondition_gen (this->context_);
    postcondition_gen.generate (postcondition);
  }

  // Visit the next state in the chain.
  effect->dst_StateBase ()->accept (this);
}

//
// visit_DoWhileState
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
visit_DoWhileState (PICML::DoWhileState_in do_while)
{
  // Generate the implemenation for the do...while control block.
  CUTS_BE_Do_While_Begin_T <CONTEXT> do_while_begin (this->context_);
  do_while_begin.generate ();

  this->visit_LoopState (do_while);

  CUTS_BE_Do_While_End_T <CONTEXT> do_while_end (this->context_);
  do_while_end.generate ();

  // We are starting to generate the do...while condition.
  CUTS_BE_Do_While_Condition_Begin_T <CONTEXT> do_while_condition_begin (this->context_);
  do_while_condition_begin.generate ();

  CUTS_BE_Precondition_T <CONTEXT> precondition_gen (this->context_);
  precondition_gen.generate (do_while->LoopingCondition ());

  // We are done generating the do...while condition.
  CUTS_BE_Do_While_Condition_End_T <CONTEXT> do_while_condition_end (this->context_);
  do_while_condition_end.generate ();

  // Goto the terminal for this control block.
  this->goto_to_terminal ();
}

//
// visit_WhileState
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
visit_WhileState (PICML::WhileState_in while_state)
{
  // We are starting to generate the do...while condition.
  CUTS_BE_While_Condition_Begin_T <CONTEXT> while_condition_begin (this->context_);
  while_condition_begin.generate ();

  CUTS_BE_Precondition_T <CONTEXT> precondition_gen (this->context_);
  precondition_gen.generate (while_state->LoopingCondition ());

  // We are done generating the do...while condition.
  CUTS_BE_While_Condition_End_T <CONTEXT> while_condition_end (this->context_);
  while_condition_end.generate ();

  // Generate the implemenation for the do...while control
  // block.
  CUTS_BE_While_Begin_T <CONTEXT> while_begin_gen (this->context_);
  while_begin_gen.generate ();

  this->visit_LoopState (while_state);

  CUTS_BE_While_End_T <CONTEXT> while_end_gen (this->context_);
  while_end_gen.generate ();

  // Goto the terminal for this control block.
  this->goto_to_terminal ();
}

//
// visit_ForState
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
visit_ForState (PICML::ForState_in for_state)
{
  // We are starting to generate the for (init; condition; final).
  CUTS_BE_For_Condition_Begin_T <CONTEXT> for_condition_begin (this->context_);
  for_condition_begin.generate ();

  CUTS_BE_Precondition_T <CONTEXT> initialcondition_gen (this->context_);
  initialcondition_gen.generate (for_state->InitialCondition ());

  CUTS_BE_For_Condition_Delimiter_T <CONTEXT> for_condition_delimiter (this->context_);
  for_condition_delimiter.generate ();

  CUTS_BE_Precondition_T <CONTEXT> precondition_gen (this->context_);
  precondition_gen.generate (for_state->LoopingCondition ());

  for_condition_delimiter.generate ();

  CUTS_BE_Precondition_T <CONTEXT> incrementalexpr_gen (this->context_);
  incrementalexpr_gen.generate (for_state->IncrementExpr ());

  // We are done generating the for (init; condition; final condition).
  CUTS_BE_For_Condition_End_T <CONTEXT> for_condition_end (this->context_);
  for_condition_end.generate ();

  // Generate the implemenation for the for control block.
  CUTS_BE_For_Begin_T <CONTEXT> for_begin_gen (this->context_);
  for_begin_gen.generate ();

  this->visit_LoopState (for_state);

  CUTS_BE_For_End_T <CONTEXT> for_end_gen (this->context_);
  for_end_gen.generate ();

  // Goto the terminal for this control block.
  this->goto_to_terminal ();
}

//
// goto_to_terminal
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
goto_to_terminal (void)
{
  // Since we have finished the branching, we can continue generating
  // the remainder of the behavior that occurs after the branching.
  if (!this->terminal_state_.empty ())
  {
    PICML::Terminal terminal = this->terminal_state_.top ();
    this->terminal_state_.pop ();

    terminal->accept (this);
  }
}

//
// visit_LoopTransition
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
visit_LoopTransition (PICML::LoopTransition_in transition)
{
  this->visit_ActionBase (transition->dst_ActionBase ());
}

//
// visit_LoopState
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
visit_LoopState (PICML::LoopState_in loop_state)
{
  if (loop_state->has_src_of_LoopTransition ())
    loop_state->src_of_LoopTransition ()->accept (this);
}

//
// visit_State
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
visit_State (PICML::State_in state)
{
  // Generate information about the state.
  CUTS_BE_State_T <CONTEXT> state_gen (this->context_);
  state_gen.generate (state);

  // Check to see if this state has any finish connections. If it
  // does, then we need to see if any of the finish connections is
  // for the current input action.
  PICML::Finish finish;

  if (GAME::contains <GAME::Mga_t> (
    [this] (PICML::Finish finish) -> bool { return this->action_stack.top () == finish->dst_BehaviorInputAction ();})
    (state->src_of_Finish (), finish))
  {
    return;
  }

  // Visit the transition that connected to this state.
  if (state->has_src_of_Transition ())
    state->src_of_Transition ()->accept (this);
  else
  {
    // Ok, so we are at a terminal transition.
    PICML::TerminalTransition term = state.dstTerminalTransition ();

    CUTS_BE::visit <CONTEXT> (state->src_of_TerminalTransition (),
      [this] (PICML::TerminalTransition t) { t->accept (this); });
  }
}

//
// visit_BranchState
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
visit_BranchState (PICML::BranchState_in state)
{
  // We use the greater than comparison so that empty string,
  // aspect = BehaviorState
  GAME::Mga::Collection_T <PICML::BranchTransition> transitions = 
    state->src_of_BranchTransition ();

  // Signal the backend we are starting a branch state.
  CUTS_BE_Branches_Begin_T <CONTEXT> branches_begin_gen (this->context_);
  branches_begin_gen.generate (transitions.count ());

  typedef collection_sort <PICML::BranchTransition, GAME::Mga::PS_Top_To_Bottom> sorter;
  CUTS_BE::visit <CONTEXT> (sorter () (transitions, "BehaviorState"),
    [this] (PICML::BranchTransition item) {item->accept (this);});

  // Signal the backend we are starting a branch state.
  CUTS_BE_Branches_End_T <CONTEXT> branches_end_gen (this->context_);
  branches_end_gen.generate ();

  // Since we have finished the branching, we can continue generating
  // the remainder of the behavior that occurs after the branching.
  this->goto_to_terminal ();
}

//
// visit_TerminalTransition
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
visit_TerminalTransition (PICML::TerminalTransition_in transition)
{
  PICML::Terminal terminal = transition->dst_Terminal ();

  if (this->terminal_state_.empty () ||
      this->terminal_state_.top () != terminal)
  {
    this->terminal_state_.push (terminal);
  }
}

//
// visit_Terminal
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
visit_Terminal (PICML::Terminal_in terminal)
{
  if (terminal->has_src_of_TerminalEffect ())
    terminal->src_of_TerminalEffect ()->accept (this);
}

//
// visit_TerminalEffect
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
visit_TerminalEffect (PICML::TerminalEffect_in effect)
{
  effect->dst_StateBase ()->accept (this);
}

//
// visit_Transition
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
visit_Transition (PICML::Transition_in transition)
{
  this->visit_ActionBase (transition->dst_ActionBase ());
}

//
// visit_BranchTransition
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
visit_BranchTransition (PICML::BranchTransition_in transition)
{
  std::string condition = transition->Condition ();

  if (!condition.empty ())
  {
    // We first need to write the condition for the branch before
    // we can start writing the actual branch statements.
    CUTS_BE_Branch_Condition_Begin_T <CONTEXT> branch_condition_begin (this->context_);
    branch_condition_begin.generate ();

    CUTS_BE_Precondition_T <CONTEXT> precondition_gen (this->context_);
    precondition_gen.generate (condition);

    CUTS_BE_Branch_Condition_End_T <CONTEXT> branch_condition_end (this->context_);
    branch_condition_end.generate ();
  }
  else
  {
    // This is an *else* branch. There should only be one of these
    // and it should be the last one in the listing.
    CUTS_BE_Branch_No_Condition_T <CONTEXT> branch_no_condition (this->context_);
    branch_no_condition.generate ();
  }

  // We are now ready to write the branch statements.
  CUTS_BE_Branch_Begin_T <CONTEXT> branch_begin_gen (this->context_);
  branch_begin_gen.generate ();

  this->visit_ActionBase (transition->dst_ActionBase ());

  CUTS_BE_Branch_End_T <CONTEXT> branch_end_gen (this->context_);
  branch_end_gen.generate ();
}

//
// visit_ActionBase
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
visit_ActionBase (PICML::ActionBase_in action_base)
{
  std::string metaname = action_base->meta ()->name ();

  // We are placing the order of the action types in fast path
  // order. We know there will be far more <Action> elements
  // than any type.
  if (metaname == PICML::Action::impl_type::metaname)
    action_base->accept (this);
  else if (metaname == PICML::OutputAction::impl_type::metaname)
    action_base->accept (this);
  else if (metaname == PICML::RequestAction::impl_type::metaname)
    action_base->accept (this);
  else
    return;

  // Continue down the chain.
  action_base->src_of_Effect ()->accept (this);
}

//
// visit_RequestAction
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
visit_RequestAction (PICML::RequestAction_in action)
{
  CUTS_BE_RequestAction_Begin_T <CONTEXT> req_begin (this->context_);
  req_begin.generate (action);

  // Generate the parameters for the action.
  GAME::Mga::Collection_T <PICML::Property> properties =
    action->children <PICML::Property> ();

  typedef std::set <PICML::Property, Sort_By_Position <PICML::Property> > Property_Set;
  Property_Set properties = action.Property_kind_children_sorted (Sort_By_Position <PICML::Property> ());

  if (properties.count ())
  {
    CUTS_BE_Action_Properties_Begin_T <CONTEXT> action_props_begin_gen (this->context_);
    action_props_begin_gen.generate (properties.size ());

    typedef collection_sort <PICML::Property, GAME::Mga::PS_Left_To_Right> sorter;
    CUTS_BE::visit <CONTEXT> (sorter () (properties, "BehaviorAction"),
      [this] (PICML::Property item) {item->accept (this);});

    CUTS_BE_Action_Properties_End_T <CONTEXT> action_props_end_gen (this->context_);
    action_props_end_gen.generate ();
  }

  CUTS_BE_RequestAction_End_T <CONTEXT> output_action_end (this->context_);
  output_action_end.generate (action);
}

//
// visit_SimpleProperty
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
visit_SimpleProperty (PICML::SimpleProperty_in prop)
{
  CUTS_BE_Action_Property_T <CONTEXT> action_property_gen (this->context_);
  action_property_gen.generate (prop);
}

//
// visit_Action
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
visit_Action (PICML::Action_in action)
{
  // Let's tell the <traits_> to begin generating an action.
  CUTS_BE_WorkerAction_Begin_T <CONTEXT> worker_action_begin (this->context_);
  worker_action_begin.generate (action);

  // Generate the parameters for the action. Right now, we only
  // support SimpleProperty elements.
  GAME::Mga::Collection_T <PICML::SimpleProperty> properties =
    action->get_SimplePropertys ();

  if (properties.count ())
  {
    CUTS_BE_Action_Properties_Begin_T <CONTEXT> action_props_begin_gen (this->context_);
    action_props_begin_gen.generate (properties.size ());

    typedef collection_sort <PICML::SimpleProperty, GAME::Mga::PS_Left_To_Right> sorter;
    CUTS_BE::visit <CONTEXT> (sorter () (properties, "BehaviorAction"),
      [this] (PICML::SimpleProperty item) {item->accept (this);});

    CUTS_BE_Action_Properties_End_T <CONTEXT> action_props_end_gen (this->context_);
    action_props_end_gen.generate ();
  }

  // Let's tell the <traits_> to end generating an action.
  CUTS_BE_Action_End_T <CONTEXT> action_end (this->context_);
  action_end.generate ();
}

//
// visit_OutputAction
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
visit_OutputAction (PICML::OutputAction_in action)
{
  CUTS_BE_OutputAction_Begin_T <CONTEXT> output_action_begin (this->context_);
  output_action_begin.generate (action);

  typedef std::vector <PICML::Property> Property_Set;
  Property_Set properties = action.Property_kind_children ();

  CUTS_BE::visit <CONTEXT> (action->children <PICML::Property> (),
    [this] (PICML::Property p) { this->visit_OutputAction_Property (p); });

  CUTS_BE_OutputAction_End_T <CONTEXT> output_action_end (this->context_);
  output_action_end.generate (action);
}

//
// visit_OutputAction_Property
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
visit_OutputAction_Property (PICML::Property_in prop)
{
  PICML::OutputAction parent = PICML::OutputAction::_narrow (prop->parent_ActionBase ());
  CUTS_BE_OutputAction_Property_T <CONTEXT> output_action_property (this->context_);
  output_action_property.generate (parent, prop);
}
