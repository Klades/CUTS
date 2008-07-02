/**
 * @file        Logger.java
 *
 * $Id$
 *
 * @author      James H. Hill
 */

package cuts.java;

//import cuts.java.LogPriority;

/**
 * Basic logger class for integrating with ACE logging framework. This
 * class define the minimum methods needed to interface with ACE.
 * Currently, there is only one log (...) method, which simplifies and
 * minimizes the amount to data/variables that must be converted from
 * managed to unmanaged code.
 */
public class Logger
{
  /// Shutdown the logger (decimal 1).
  public static final int LM_SHUTDOWN  = 0x00000001;

  /// Messages indicating function-calling sequence (decimal 2).
  public static final int LM_TRACE     = 0x00000002;

  /// Messages that contain information normally of use only when
  /// debugging a program (decimal 4).
  public static final int LM_DEBUG     = 0x00000004;

  /// Informational messages (decimal 8).
  public static final int LM_INFO      = 0x00000010;

  /// Conditions that are not error conditions, but that may require
  /// special handling (decimal 16).
  public static final int LM_NOTICE    = 0x00000020;

  /// Warning messages (decimal 32).
  public static final int LM_WARNING   = 0x00000040;

  /// Initialize the logger (decimal 64).
  public static final int LM_STARTUP   = 0x00000100;

  /// Error messages (decimal 128).
  public static final int LM_ERROR     = 0x00000200;

  /// Critical conditions, such as hard device errors (decimal 256).
  public static final int LM_CRITICAL  = 0x00000400;

  /// A condition that should be corrected immediately, such as a
  /// corrupted system database (decimal 512).
  public static final int LM_ALERT     = 0x00001000;

  /// A panic condition.  This is normally broadcast to all users
  /// (decimal 1024).
  public static final int LM_EMERGENCY = 0x00002000;

  /**
   * Default constructor.
   */
  public Logger ()
  {

  }

  /**
   * Native function that calls the ACE_Log_Msg::log (...). The
   * implementation of this function using the logging singleton provided
   * by ACE. It is also possible to use some formating options, such as
   * thread/process id and timestamp, which will be inserted into the
   * final log message generated by the client.
   *
   * The following is list of valid options when proceeded by an percent
   * sign (%):
   *
   * 'M': print the name of the message priority
   * 'P': print the current process id
   * 'T': print timestamp in hour:minute:sec:usec format
   * 'D': print timestamp as Weekday Month Day Year hour:minute:sec.usec
   * 't': print thread id (1 if single-threaded)
   * 'I': indent according to nesting depth
   *
   * @param[in]         priority        Priority of the message.
   * @param[in]         message         The actual log message.
   */
  public void log (int priority, String message)
  {
  
  }
}
