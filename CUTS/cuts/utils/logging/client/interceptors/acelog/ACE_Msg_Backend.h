// -*- C++ -*-

//=============================================================================
/**
 * @file      ACE_Msg_Backend.h
 *
 * $Id$
 *
 * @author    Pooja Varshneya
 */
//=============================================================================


#ifndef _CUTS_ACE_MSG_BACKEND_H_
#define _CUTS_ACE_MSG_BACKEND_H_

#include "ace/Log_Msg_Backend.h"
#include "ace/Log_Record.h"

#include "cuts/workers/Test_Logger/Test_Logger.h"

#include "ace/SString.h"

#if !defined (CUTS_LOCAL_LOGGING_CLIENT_DEFAULT_PORT)
#  define CUTS_LOCAL_LOGGING_CLIENT_DEFAULT_PORT  30002
#endif

/**
 * @class CUTS_ACE_Msg_Backend
 *
 * 
 */
class CUTS_ACE_Msg_Backend : public ACE_Log_Msg_Backend
{
	public:

  /// Constructor
  CUTS_ACE_Msg_Backend (void);
  
  /// Destructor
  virtual ~CUTS_ACE_Msg_Backend (void);

  /**
   * Connects the backend to the test_logger 
   *   
   * @param[in]					The character string passed to ACE_Log_Msg::open(). 
   *										If the LOGGER logging destination is not being used, 
   *										any string can be passed through to the back end.
   *
   * @retval       -1	,	for faliure
   *									  0 , for success
   */
  virtual int open (const ACE_TCHAR *logger_key);
	
  /**
   * Reset the backend. 
   *   
   * @retval		       -1	,	for faliure
   *									  0 , for success
   */
  virtual int reset (void);
  
  /**
   * Close the backend completely. 
   *   
   * @retval		       -1	,	for faliure
   *									  0 , for success
   */
  virtual int close (void);
  
  /**
   * Process a log record
   *
   * @param[in]        log_record        Number of arguments
   *   
   * @retval		      -1	,	for faliure.
   *									 number of bytes processed on success.
   */
  virtual ssize_t log (ACE_Log_Record &log_record);
	
  /**
   * Saves the value of previous msg_backend
   *
   * @param[in]    old_msg_backend_obj		  Old callback pointer.       
   *   
   */
  void old_msg_backend (ACE_Log_Msg_Backend * old_msg_backend_obj);
  
   /**
   * Saves the connect_string for the logger
   *
   * @param[in]    connect_string_obj		  Connect string for logger connection.      
   *   
   */
  void connect_string (ACE_CString connect_string_obj);
  
  /**
   * Saves the connect_port for the logger
   *
   * @param[in]    connect_port_obj		  Connect port for the logger connection.      
   *   
   */
  void connect_port (short connect_port_obj);
  
  /**
   * Defines the connect method for the logger
   *
   * @param[in]    connect_name_status		true for logger connection using name.
   *   																		false for logger connection using 
   *																			location.
   */
  void is_connect_name (bool connect_name_status);
 
  /**
   * Returns the previous msg_backend set for logging
   *
   * @retval    old_msg_backend		
   *
   */
  ACE_Log_Msg_Backend * old_msg_backend(void);
  
private:
  
  /// Makes the connection to test-manager
  int make_connection(void);
  
  /// logger_ is used for to make connection with test_logger
  CUTS_Test_Logger logger_;		
	
  /// connect_string_ is used for connecting to the test_logger
  ACE_CString connect_string_;
	
  /// Port for connection
  short connect_port_;
  
  /** 
   * if is_connect_name = 1, logger connection made using name
   * if is_connect_name = 0, logger connection made using location
   */
  bool is_connect_name_;
  
  // old_msg_backend_ saves the value of old_backend
  ACE_Log_Msg_Backend * old_msg_backend_;
};

#endif /* _CUTS_ACE_MSG_BACKEND_H_ */

