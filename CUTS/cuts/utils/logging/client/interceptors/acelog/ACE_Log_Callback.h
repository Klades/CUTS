// -*- C++ -*-

//=============================================================================
/**
 * @file      ACE_Log_Callback.h
 *
 * $Id$
 *
 * @author    Pooja Varshneya
 */
//=============================================================================


#ifndef _CUTS_ACE_LOGGER_CALLBACK_H_
#define _CUTS_ACE_LOGGER_CALLBACK_H_

#include "ace/Log_Msg.h"
#include "ace/Log_Msg_Callback.h"
#include "ace/Log_Record.h"

#include "cuts/workers/Test_Logger/Test_Logger.h"

/**
 * @class CUTS_ACE_Log_Callback
 */ 
class CUTS_ACE_Log_Callback : public ACE_Log_Msg_Callback
{

public:

	///Constructor
	CUTS_ACE_Log_Callback (CUTS_Test_Logger &logger);

	///Destructor
	virtual ~CUTS_ACE_Log_Callback (void);
	
  virtual void log (ACE_Log_Record &log_record) ;
  
  // Saves the value of previous callback that has been replaced by this one
  void set_old_callback (ACE_Log_Msg_Callback * old_callback);
  
  // Returns the previous callback
  ACE_Log_Msg_Callback * get_old_callback(void);
  
private:

	// Pointer to logger service for invoking log
	CUTS_Test_Logger logger_;
	
	// Pointer to the callback that is replaced by this new callback
	ACE_Log_Msg_Callback * old_callback_;
};

#endif /* _CUTS_ACE_LOGGER_CALLBACK_H_ */
