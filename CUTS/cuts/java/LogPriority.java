/**
 * @file        LogPriority.java
 * 
 * $Id$
 * 
 * @author      James H. Hill
 */
package cuts.java;

/**
 * Defines the priority of the log message. This priorities are
 * equivalent the priorities defined in the by the ACE_Log_Priority
 * class in ACE (please see ${ACE_ROOT}/ace/Log_Priority.h).
 */
public enum LogPriority
{
  /// Shutdown the logger (decimal 1).
  LM_SHUTDOWN (0x00000001),
 
  /// Messages indicating function-calling sequence (decimal 2).
  LM_TRACE (0x00000002),
 
  /// Messages that contain information normally of use only when
  /// debugging a program (decimal 4).
  LM_DEBUG (0x00000004),
  
  /// Informational messages (decimal 8).
  LM_INFO (0x00000010),
  
  /// Conditions that are not error conditions, but that may require
  /// special handling (decimal 16).
  LM_NOTICE (0x00000020),
  
  /// Warning messages (decimal 32).
  LM_WARNING (0x00000040),
  
  /// Initialize the logger (decimal 64).
  LM_STARTUP (0x00000100),
  
  /// Error messages (decimal 128).
  LM_ERROR (0x00000200),
  
  /// Critical conditions, such as hard device errors (decimal 256).
  LM_CRITICAL (0x00000400),
  
  /// A condition that should be corrected immediately, such as a
  /// corrupted system database (decimal 512).
  LM_ALERT (0x00001000),
  
  /// A panic condition.  This is normally broadcast to all users
  /// (decimal 1024).
  LM_EMERGENCY (0x00002000),
  
  /// The maximum logging priority.
  LM_MAX (LM_EMERGENCY.value ());
  
  /// Actual value of the log priority.
  private final int priority_;
    
  /**
   * Initializing constructor. This will set the value of the
   * log priority.
   * 
   * @param       priority          The value of the priority.
   */
  LogPriority (int priority)
  {
    this.priority_ = priority;
  }
    
  /**
   * Get the assigned value of the log priority.
   * 
   * @return      Value of the priority.
   */
  public int value ()
  {
    return this.priority_;
  }
}
  