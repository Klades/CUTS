// -*- C++ -*-

//=============================================================================
/**
 * @file          TestLoggerServer_i.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_LOGGER_SERVER_I_H_
#define _CUTS_TEST_LOGGER_SERVER_I_H_

#include "cuts/config.h"
#include "serverS.h"
#include "ace/Unbounded_Set.h"

/**
 * @class CUTS_TestLoggerServer_i
 */
class CUTS_TestLoggerServer_i :
  public POA_CUTS::TestLoggerServer
{
public:
  /// Default constructor.
  CUTS_TestLoggerServer_i (void);

  /// Destructor.
  virtual ~CUTS_TestLoggerServer_i (void);

  /**
   * Message packet sent from a logging client.
   *
   * @param[in]       packet        The message packet.
   */
  virtual void send_message_packet (const CUTS::LogMessagePacket & packet);

  int install_callback (CUTS::TestLoggerServerCallback_ptr callback);

private:
  /// Type definition of the array of callback objects.
  typedef ACE_Unbounded_Set <CUTS::TestLoggerServerCallback_ptr> callbacks_type;

  /// Collection of callback objects.
  callbacks_type callbacks_;
};

#if defined (__CUTS_INLINE__)
#include "TestLoggerServer_i.inl"
#endif

#endif  // !defined _CUTS_TEST_LOGGER_SERVER_I_H_
