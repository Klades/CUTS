// $Id$

#include "ACE_Msg_Backend.h"
#include "ace/Log_Msg.h"
#include "ace/OS_Memory.h"

//
// CUTS_ACE_Msg_Backend_Interceptor
//
CUTS_ACE_Msg_Backend::CUTS_ACE_Msg_Backend (void)
{	
}

//
// ~CUTS_ACE_Msg_Backend_Interceptor
//
CUTS_ACE_Msg_Backend::~CUTS_ACE_Msg_Backend (void)
{
}

//
// open
//
int CUTS_ACE_Msg_Backend::open (const ACE_TCHAR *logger_key)
{
	if (this->make_connection () == -1)
    ACE_ERROR_RETURN ((LM_ERROR, 
    									"%T (%t) - %M - connection to CUTS_Logger failed."),
    									-1);
  return 0;
}

//
// reset
//
int CUTS_ACE_Msg_Backend::reset (void)
{
	this->logger_.disconnect();
  return 0;
}

//
// close
//
int CUTS_ACE_Msg_Backend::close (void)
{
	this->logger_.disconnect();
	return 0;
}

//
// log
//
ssize_t CUTS_ACE_Msg_Backend::log (ACE_Log_Record &log_record)
{
	this->logger_.log (log_record.priority (),							  
                		 log_record.msg_data (),
										 log_record.length ());
	
	// Manually invoke the old message callback
	if (this->old_msg_backend_ != 0)
		this->old_msg_backend_->log (log_record);
		
	return log_record.length ();
}

//
// make_connection
//
int CUTS_ACE_Msg_Backend::make_connection ()
{
	this->logger_.configure (this->connect_port_);

  if ( this->is_connect_name_ )
    this->logger_.connect_using_name (this->connect_string_);
  else 
    this->logger_.connect_using_location (this->connect_string_);

  return 0;
}

//
// get_old_msg_backend
//
ACE_Log_Msg_Backend *
CUTS_ACE_Msg_Backend::old_msg_backend (void)
{
	return this->old_msg_backend_;
}

//
// set_old_msg_backend
//
void 
CUTS_ACE_Msg_Backend::old_msg_backend
(ACE_Log_Msg_Backend * old_msg_backend_obj)
{
	this->old_msg_backend_ = old_msg_backend_obj;
}

//
// connect_string
// 
void 
CUTS_ACE_Msg_Backend::connect_string (ACE_CString connect_string_obj)
{
	this->connect_string_ = connect_string_obj;
}

//
// connect_port
// 
void 
CUTS_ACE_Msg_Backend::connect_port (short connect_port_obj)
{
	this->connect_port_ = connect_port_obj;
}

//
// is_connect_name
// 
void 
CUTS_ACE_Msg_Backend::is_connect_name (bool connect_name_status)
{
	this->is_connect_name_ = connect_name_status;
}