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
#include "ACE_Log_Interceptor_export.h"

// Forward decl.
class CUTS_Client_Logger;

/**
 * @class CUTS_ACE_Log_Callback
 */
class CUTS_ACE_Log_Callback : public ACE_Log_Msg_Callback
{

public:

  ///Constructor
  CUTS_ACE_Log_Callback (CUTS_Client_Logger & logger);

  ///Destructor
  virtual ~CUTS_ACE_Log_Callback (void);

  /**
   * Process a log record
   *
   * @param[in]        log_record        Number of arguments
   *
   * @retval          -1  ,  for faliure
   *                   number of bytes processed on success
   */
  virtual void log (ACE_Log_Record &log_record);

  /**
   * Saves the value of previous callback
   *
   * @param[in]    old_callback_obj      Old callback pointer.
   *
   */
  void old_callback (ACE_Log_Msg_Callback * old_callback_obj);

  /**
   * Returns the previous callback set for logging
   *
   * @retval    old_msg_callback
   *
   */
  ACE_Log_Msg_Callback * old_callback (void);

private:
  // Pointer to logger service for invoking log
  CUTS_Client_Logger & logger_;

  // Pointer to the callback that is replaced by this new callback
  ACE_Log_Msg_Callback * old_callback_;
};

#if defined (__CUTS_INLINE__)
#include "ACE_Log_Callback.inl"
#endif

#endif /* _CUTS_ACE_LOGGER_CALLBACK_H_ */
