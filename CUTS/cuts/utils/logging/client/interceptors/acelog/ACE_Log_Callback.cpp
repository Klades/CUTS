// $Id$

#include "ACE_Log_Callback.h"

//
// Callback
//
CUTS_ACE_Log_Callback::CUTS_ACE_Log_Callback (CUTS_Test_Logger &logger)
: logger_ (logger),
  old_callback_(0)
{
}

//
// ~Callback
//
CUTS_ACE_Log_Callback::~CUTS_ACE_Log_Callback (void)
{
}

//
// log
//
void CUTS_ACE_Log_Callback::log (ACE_Log_Record &log_record)
{
	this->logger_.log (log_record.priority (),							  
                		 log_record.msg_data (),
										 log_record.length ());
	
	// Some callback was set previously, invoke it manually
	if (this->old_callback_ != 0)
		this->old_callback_->log (log_record);
}

ACE_Log_Msg_Callback *
CUTS_ACE_Log_Callback::get_old_callback (void)
{
	return this->old_callback_;
}

void CUTS_ACE_Log_Callback::set_old_callback (ACE_Log_Msg_Callback *old_callback)
{
	this->old_callback_ = old_callback_;
}