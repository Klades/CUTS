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
#include "ace/SString.h"
#include "cuts/utils/logging/client/logger/Client_Logger.h"
#include "ACE_Log_Interceptor_export.h"

/**
 * @class CUTS_ACE_Msg_Backend
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
   * @param[in]          The character string passed to ACE_Log_Msg::open().
   *                    If the LOGGER logging destination is not being used,
   *                    any string can be passed through to the back end.
   *
   * @retval       -1  ,  for faliure
   *                    0 , for success
   */
  virtual int open (const ACE_TCHAR *logger_key);

  /**
   * Reset the backend.
   *
   * @retval           -1  ,  for faliure
   *                    0 , for success
   */
  virtual int reset (void);

  /**
   * Close the backend completely.
   *
   * @retval           -1  ,  for faliure
   *                    0 , for success
   */
  virtual int close (void);

  /**
   * Process a log record
   *
   * @param[in]        log_record        Number of arguments
   *
   * @retval          -1  ,  for faliure.
   *                   number of bytes processed on success.
   */
  virtual ssize_t log (ACE_Log_Record &log_record);

  /**
   * Saves the value of previous msg_backend
   *
   * @param[in]    old_msg_backend_obj      Old callback pointer.
   *
   */
  void old_msg_backend (ACE_Log_Msg_Backend * old_msg_backend_obj);

  /**
   * Returns the previous msg_backend set for logging
   *
   * @retval    old_msg_backend
   *
   */
  ACE_Log_Msg_Backend * old_msg_backend(void);

  /// Get the logger for the message backend.
  CUTS_Client_Logger & logger (void);

private:
  /// logger_ is used for to make connection with test_logger
  CUTS_Client_Logger logger_;

  // old_msg_backend_ saves the value of old_backend
  ACE_Log_Msg_Backend * old_msg_backend_;
};

#if defined (__CUTS_INLINE__)
#include "ACE_Msg_Backend.inl"
#endif

#endif /* _CUTS_ACE_MSG_BACKEND_H_ */

