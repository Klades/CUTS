// $Id$

//=============================================================================
/**
 * @file          Log_Message_Handler.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_LOG_MESSAGE_HANDLER_H_
#define _CUTS_LOG_MESSAGE_HANDLER_H_

#include "../loggingC.h"
#include "cuts/config.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL
namespace ACE_Utils
{
  class UUID;
}
ACE_END_VERSIONED_NAMESPACE_DECL

/**
 * @class CUTS_Log_Message_Handler
 *
 * Abstract class that defines the interface for an object that
 * handles log messages.
 */
class CUTS_Log_Message_Handler
{
public:
  /// Destructor.
  virtual ~CUTS_Log_Message_Handler (void);

  /**
   * Handle a log message.
   *
   * @param[in]       uuid        UUID associated with log message
   * @param[in]       logmsg      Log message to handle.
   */
  virtual int handle_log_message (const ACE_Utils::UUID & uuid,
                                  const ::CUTS::LogMessage & logmsg);
};

#if defined (__CUTS_INLINE__)
#include "Log_Message_Handler.inl"
#endif

#endif  // !defined _CUTS_LOG_MESSAGE_HANDLER_H_
