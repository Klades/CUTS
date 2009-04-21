// -*- C++ -*-
// $Id$

//
// CUTS_Property_Evaluator_Config
//
CUTS_INLINE
CUTS_Property_Evaluator_Config::CUTS_Property_Evaluator_Config (void)
: use_env_ (true),
  open_tag_ ("${"),
  close_tag_ ("}")
{

}

//
// CUTS_Property_Evaluator
//
template <typename ACTOR>
CUTS_INLINE
CUTS_Property_Evaluator_T <ACTOR>::
CUTS_Property_Evaluator_T (const CUTS_Property_Map & map, ACTOR & actor)
: grammar_ (map, config_, actor)
{

}

//
// ~CUTS_Property_Evaluator
//
template <typename ACTOR>
CUTS_INLINE
CUTS_Property_Evaluator_T <ACTOR>::~CUTS_Property_Evaluator_T (void)
{

}

//
// config
//
template <typename ACTOR>
CUTS_INLINE
CUTS_Property_Evaluator_Config &
CUTS_Property_Evaluator_T <ACTOR>::config (void)
{
  return this->config_;
}

//
// config
//
template <typename ACTOR>
CUTS_INLINE
const CUTS_Property_Evaluator_Config &
CUTS_Property_Evaluator_T <ACTOR>::config (void) const
{
  return this->config_;
}

//
// config
//
template <typename ACTOR>
CUTS_INLINE
const CUTS_Property_Map &
CUTS_Property_Evaluator_T <ACTOR>::property_map (void) const
{
  return this->grammar_.property_map ();
}
