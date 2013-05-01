// $Id$

#include "Portico_Servant.h"

#if !defined (__CUTS_INLINE__)
#include "Portico_Servant.inl"
#endif

namespace iCCM
{

//
// advance_time
//
void Portico_Servant::advance_time (const RTIfedTime & amt)
{
  // Update the flag so we know we are advancing time.
  this->is_advancing_ = true;

  // Request a time advice to the new time.
  RTIfedTime new_time = this->federate_time_ + amt;
  this->rtiamb_.timeAdvanceRequest (new_time);

  // Wait until we are granted the time advance.
  while (this->is_advancing_)
    this->rtiamb_.tick ();
}

//
// configure
//
int Portico_Servant::
install (const std::string & fed, const std::string & exec)
{
  try
  {
    // Use the FED information to create the execution. If it already
    // exists, then we just swallow the exception and keep moving!
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - creating <%s> federate execution\n"),
                exec.c_str ()));

    this->rtiamb_.createFederationExecution (exec.c_str (), fed.c_str ());
  }
  catch (const RTI::FederationExecutionAlreadyExists & )
  {
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - <%s> federate execution already exists\n"),
                exec.c_str ()));
  }

  try
  {
    // Join the federation. If we fail to join the federation, then there
    // is no reason to start this servant.
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - <%s> is joining execution <%s>\n"),
                this->name_.c_str (),
                exec.c_str ()));

    this->rtiamb_.joinFederationExecution (this->name_.c_str (),
                                           exec.c_str (),
                                           this);

    // Save the execution name.
    this->execname_ = exec;
    return 0;
  }
  catch (const RTI::Exception & )
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to join <%s> execution\n"),
                exec.c_str ()));

  }

  return -1;
}

//
// remove
//
void Portico_Servant::remove (void)
{
  try
  {
    // Resign from the federation.
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - <%s> is resigning from <%s>\n"),
                this->name_.c_str (),
                this->execname_.c_str ()));

    this->rtiamb_.resignFederationExecution (RTI::DELETE_OBJECTS_AND_RELEASE_ATTRIBUTES);

    // Destroy the execution, if possible.
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - destroying federation execution <%s>\n"),
                this->execname_.c_str ()));

    this->rtiamb_.destroyFederationExecution (this->execname_.c_str ());
  }
  catch (const RTI::FederationExecutionDoesNotExist &)
  {

  }
  catch (const RTI::FederatesCurrentlyJoined &)
  {

  }
}

//
// discoverObjectInstance
//
void Portico_Servant::
discoverObjectInstance (RTI::ObjectHandle obj,
                        RTI::ObjectClassHandle obj_class,
                        const char * obj_name)
                       throw (RTI::CouldNotDiscover,
                              RTI::ObjectClassNotKnown,
                              RTI::FederateInternalError)
{
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - <%s> discovered <%s> [handle=%d; class=%d]\n"),
              this->name_.c_str (),
              obj_name,
              obj,
              obj_class));

  // Notify all waiting threads of a new object has been discovered.
  ACE_GUARD (ACE_Thread_Mutex, guard, this->obj_discovery_mutex_);
  this->obj_discovery_.broadcast ();
}

//
// announceSynchronizationPoint
//
void Portico_Servant::
announceSynchronizationPoint (const char *label, const char *tag) throw (RTI::FederateInternalError)
{

}

//
// timeAdvanceGrant
//
void Portico_Servant::
timeAdvanceGrant (const RTI::FedTime & the_time)
                 throw (RTI::InvalidFederationTime,
                        RTI::TimeAdvanceWasNotInProgress,
                        RTI::FederateInternalError)
{
  this->is_advancing_ = false;
  this->federate_time_ = the_time;
}

//
// wait_for_object_discovery
//
void Portico_Servant::
wait_for_object_discovery (const ACE_Time_Value * abstime)
{
  ACE_GUARD (ACE_Thread_Mutex, guard, this->obj_discovery_mutex_);
  this->obj_discovery_.wait (abstime);
}

}
