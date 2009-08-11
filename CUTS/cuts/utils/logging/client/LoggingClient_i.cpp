// $Id$

#include "LoggingClient_i.h"

#if !defined (__CUTS_INLINE__)
#include "LoggingClient_i.inl"
#endif

#include "Logger_i.h"
#include "cuts/UUID.h"

//
// CUTS_LoggingClient_i
//
CUTS_LoggingClient_i::
CUTS_LoggingClient_i (::PortableServer::POA_ptr parent,
                      CUTS_Log_Message_Handler * handler)
: handler_ (handler)
{
  // Construct the policy list for the TestLoggerFactory POA.
  CORBA::PolicyList policies (6);
  policies.length (6);

  policies[0] = parent->create_thread_policy (PortableServer::ORB_CTRL_MODEL);
  policies[1] = parent->create_servant_retention_policy (PortableServer::RETAIN);
  policies[2] = parent->create_id_assignment_policy (PortableServer::USER_ID);
  policies[3] = parent->create_id_uniqueness_policy (PortableServer::UNIQUE_ID);
  policies[4] = parent->create_lifespan_policy (PortableServer::TRANSIENT);
  policies[5] = parent->create_request_processing_policy (PortableServer::USE_ACTIVE_OBJECT_MAP_ONLY);

  // Create the child POA for the test logger factory servants.
  this->logger_poa_ = parent->create_POA ("LoggerPOA",
                                          ::PortableServer::POAManager::_nil (),
                                          policies);

  // Activate the POA manager.
  ::PortableServer::POAManager_var mgr = this->logger_poa_->the_POAManager ();
  mgr->activate ();

  // Destroy the POA policies
  for (::CORBA::ULong i = 0; i < policies.length (); ++ i)
    policies[i]->destroy ();
}

//
// get_logger
//
::CUTS::Logger_ptr CUTS_LoggingClient_i::get_logger (const ::CUTS::UUID & test)
{
  // Store the test id in an usable object.
  ACE_Utils::UUID uuid;
  test >>= uuid;

  // Convert the uuid to an object id.
  ::PortableServer::ObjectId_var oid =
    ::PortableServer::string_to_ObjectId (uuid.to_string ()->c_str ());

  ::CORBA::Object_var obj;

  try
  {
    // Locate a reference for the object id.
    obj = this->logger_poa_->id_to_reference (oid.in ());
  }
  catch (const ::PortableServer::POA::ObjectNotActive & )
  {
    // Allocate a new servant.
    CUTS_Logger_i * servant = 0;

    ACE_NEW_THROW_EX (servant,
                      CUTS_Logger_i (this->handler_, uuid),
                      ::CORBA::NO_MEMORY ());

    ACE_Auto_Ptr <CUTS_Logger_i> auto_clean (servant);

    // Activate the servant. The POA now has ownership.
    this->logger_poa_->activate_object_with_id (oid.in (), servant);
    auto_clean.release ();

    // Get a reference to the servant.
    obj = this->logger_poa_->id_to_reference (oid.in ());
  }

  // Narrow object to a logger and return.
  ::CUTS::Logger_var logger = ::CUTS::Logger::_narrow (obj.in ());
  return logger._retn ();
}

//
// release
//
void CUTS_LoggingClient_i::release (::CUTS::Logger_ptr logger)
{
  try
  {
    // Take ownership of the servant to decrement its reference.
    ::PortableServer::ServantBase_var servant_base = this->logger_poa_->reference_to_servant (logger);
    CUTS_Logger_i * servant = dynamic_cast <CUTS_Logger_i *> (servant_base.in ());
  }
  catch (const ::PortableServer::POA::ServantNotActive & )
  {

  }
}
