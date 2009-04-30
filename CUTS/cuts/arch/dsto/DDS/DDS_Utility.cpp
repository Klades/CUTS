#include "DDS_Utility.h"

DDS_Utility::DDS_Utility (void)
  : domain_ (0)
{
}

DDS_Utility::~DDS_Utility (void)
{
  ReturnCode_t status = RETCODE_OK;
  
  try
    {
      if (! CORBA::is_nil (participant_.in ()))
        {
          status =
            participant_->delete_contained_entities ();
          this->check_status (status,
                              "delete_contained_entities()");
        }
      
      if (! CORBA::is_nil (factory_.in ()))
        {
          status =
            factory_->delete_participant (participant_.in ());
          this->check_status (status, "delete_participant()");
        }
    }
  catch (const CORBA::Exception& ex)
    {
      ex._tao_print_exception ("Exception caught in cleanup.");
    }
}

bool
DDS_Utility::init (DomainId_t domain)
{
  bool status = true;
  
  factory_ = DomainParticipantFactory::get_instance ();
  this->check_objref (factory_.in (), "TheParticipantFactory");
  
  participant_ =
    factory_->create_participant (domain,
                                  PARTICIPANT_QOS_DEFAULT,
                                  0,
                                  ANY_STATUS);
  this->check_objref (participant_.in (),
                      "create_participant()");
                      
  if (CORBA::is_nil (participant_.in ()))
    {
      ACE_ERROR ((LM_EMERGENCY,
                  ACE_TEXT ("Info repo daemon not running\n")));
      status = false;
    }
  else
    {
      domain_ = domain;
    }
    
  return status;
}

void
DDS_Utility::check_status (ReturnCode_t status,
                           const char * info)
{
  if (status != RETCODE_OK && status != RETCODE_NO_DATA)
    {
      ACE_ERROR ((LM_EMERGENCY,
                  ACE_TEXT ("Error in %s: %s\n"),
                  info,
                  this->get_error_name (status)));
    }
}

void
DDS_Utility::check_objref (CORBA::Object_ptr obj,
                           const char * info)
{
  if (CORBA::is_nil (obj))
    {
      ACE_ERROR ((LM_EMERGENCY,
                  ACE_TEXT ("Error in %s: null objref returned\n"),
                  info));
    }
}

char *
DDS_Utility::get_error_name (ReturnCode_t status)
{
  static char * RetCodeName[13] =
    { 
      "DDS_RETCODE_OK",
      "DDS_RETCODE_ERROR",
      "DDS_RETCODE_UNSUPPORTED",
      "DDS_RETCODE_BAD_PARAMETER",
      "DDS_RETCODE_PRECONDITION_NOT_MET",
      "DDS_RETCODE_OUT_OF_RESOURCES",
      "DDS_RETCODE_NOT_ENABLED",
      "DDS_RETCODE_IMMUTABLE_POLICY",
      "DDS_RETCODE_INCONSISTENT_POLICY",
      "DDS_RETCODE_ALREADY_DELETED",
      "DDS_RETCODE_TIMEOUT",
      "DDS_RETCODE_NO_DATA",
      "DDS_RETCODE_ILLEGAL_OPERATION"
    };

  return RetCodeName[status];
}