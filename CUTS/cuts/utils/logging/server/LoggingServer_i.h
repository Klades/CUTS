// -*- C++ -*-

//=============================================================================
/**
 * @file          LoggingServer_i.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_LOGGIGN_SERVER_I_H_
#define _CUTS_LOGGIGN_SERVER_I_H_

#include "cuts/config.h"
#include "LoggingServerS.h"
#include "ace/Unbounded_Set.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/RW_Thread_Mutex.h"
#include "ace/UUID.h"

/**
 * @class CUTS_LoggingServer_i
 *
 * Implementation of the ::CUTS::LoggingServer interface.
 */
class CUTS_LoggingServer_i :
  public ::POA_CUTS::LoggingServer
{
public:
  /// Default constructor.
  CUTS_LoggingServer_i (void);

  /// Destructor.
  virtual ~CUTS_LoggingServer_i (void);

  virtual ::CUTS::UUID *
    register_listener (const ::CUTS::UUID & test,
                       ::CUTS::LoggingServerListener_ptr listener);

  virtual void unregister_listener (const ::CUTS::UUID & test,
                                    const ::CUTS::UUID & cookie);

  virtual void handle_messages (const ::CUTS::LogMessagePacket & packet);

private:
  /**
   * @class reg_t
   *
   * Registration class for the listener map.
   */
  class reg_t
  {
  public:
    reg_t (void)
    {

    }

    reg_t (const reg_t & copy)
      : cookie_ (copy.cookie_),
        listener_ (::CUTS::LoggingServerListener::_duplicate (copy.listener_.in ()))
    {

    }

    const reg_t & operator = (const reg_t & rhs)
    {
      if (this == &rhs)
        return *this;

      this->cookie_ = rhs.cookie_;
      this->listener_ = ::CUTS::LoggingServerListener::_duplicate (rhs.listener_.in ());

      return *this;
    }

    bool operator == (const reg_t & rhs) const
    {
      return this->cookie_ == rhs.cookie_;
    }

    ACE_Utils::UUID cookie_;

    ::CUTS::LoggingServerListener_var listener_;
  };

  void handle_log_message (const char * hostname,
                           const ::CUTS::TestLogMessage & msg);

  /// Type definition of the listerner map.
  typedef
    ACE_Hash_Map_Manager <ACE_Utils::UUID,
                          ACE_Unbounded_Set <reg_t> *,
                          ACE_RW_Thread_Mutex> listener_map;

  /// Registered listeners.
  listener_map listeners_;

  /// Listeners that receives messages from all tests.
  ACE_Unbounded_Set <reg_t> global_listeners_;
};

#if defined (__CUTS_INLINE__)
#include "LoggingServer_i.inl"
#endif

#endif  // !defined _CUTS_LOGGIGN_SERVER_I_H_
