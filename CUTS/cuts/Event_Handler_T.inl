// -*- C++ -*-
// $Id$

//
// CUTS_Event_Handler_T
//
template <typename COMPONENT, typename EVENTTYPE>
CUTS_INLINE
CUTS_Event_Handler_T <COMPONENT, EVENTTYPE>::
CUTS_Event_Handler_T (void)
{
  CUTS_TRACE ("CUTS_Event_Handler_T <COMPONENT, EVENTTYPE>::CUTS_Event_Handler_T");
}

//
// CUTS_Event_Handler_T
//
template <typename COMPONENT, typename EVENTTYPE>
CUTS_INLINE
CUTS_Event_Handler_T <COMPONENT, EVENTTYPE>::
~CUTS_Event_Handler_T (void)
{
  CUTS_TRACE ("CUTS_Event_Handler_T <COMPONENT, EVENTTYPE>::~CUTS_Event_Handler_T");
}

//
// dispatch_event
//
template <typename COMPONENT, typename EVENTTYPE>
CUTS_INLINE
bool CUTS_Event_Handler_Config_T <COMPONENT, EVENTTYPE>::
dispatch_event (EVENTTYPE * ev) const
{
  CUTS_TRACE ("CUTS_Event_Handler_Config_T <COMPONENT, EVENTTYPE>::dispatch_event (EVENTTYPE *) const");

  if (this->component_ != 0 && this->method_ != 0)
    {
      (this->component_->*this->method_) (ev);
      return true;
    }
  else
    {
      ACE_ERROR ((LM_CRITICAL,
                  "%T (%t) - %M - callback component and method are NIL\n"));
    }

  return false;
}

//=============================================================================
// @@ CUTS_Event_Handler_Base_T <COMPONENT, EVENTTYPE>

//
// port_agent
//
template <typename COMPONENT, typename EVENTTYPE>
CUTS_INLINE
CUTS_Port_Agent &
CUTS_Event_Handler_Base_T <COMPONENT, EVENTTYPE>::
port_agent (void)
{
  return this->config_.port_agent_;
}

//
// name
//
template <typename COMPONENT, typename EVENTTYPE>
CUTS_INLINE
const char *
CUTS_Event_Handler_Base_T <COMPONENT, EVENTTYPE>::name (void) const
{
  return this->config_.port_agent_.name ().c_str ();
}

//=============================================================================
// @@ CUTS_Event_Handler_Base_T <COMPONENT, ::CUTS::Empty_Event>

//
// port_agent
//
template <typename COMPONENT>
CUTS_INLINE
CUTS_Port_Agent &
CUTS_Event_Handler_Base_T <COMPONENT, ::CUTS::Empty_Event>::
port_agent (void)
{
  return this->config_.port_agent_;
}

//
// name
//
template <typename COMPONENT>
CUTS_INLINE
const char *
CUTS_Event_Handler_Base_T <COMPONENT, ::CUTS::Empty_Event>::
name (void) const
{
  return this->config_.port_agent_.name ().c_str ();
}

//=============================================================================
// @@ CUTS_Event_Handler_Base_T <COMPONENT, ::CUTS::Payload_Event>

//
// port_agent
//
template <typename COMPONENT>
CUTS_INLINE
CUTS_Port_Agent &
CUTS_Event_Handler_Base_T <COMPONENT, ::CUTS::Payload_Event>::
port_agent (void)
{
  return this->config_.port_agent_;
}

//
// name
//
template <typename COMPONENT>
CUTS_INLINE
const char *
CUTS_Event_Handler_Base_T <COMPONENT, ::CUTS::Payload_Event>::
name (void) const
{
  return this->config_.port_agent_.name ().c_str ();
}
