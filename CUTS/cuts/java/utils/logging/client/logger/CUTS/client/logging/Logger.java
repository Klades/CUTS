//-*- java -*-

//=============================================================================
/**
 * @file        Logger.java
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

package CUTS.client.logger;
import org.omg.CosNaming.*;
import java.util.ArrayList;
import java.util.Properties;
import java.io.*;

/**
 * @class Logger
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
    final String CUTS_ROOT = System.getenv ("CUTS_ROOT");
    final String pathSeparator = System.getProperty ("file.seperator");

    ArrayList<String> args = new ArrayList ();
    args.add ("-Djava.endorsed.dirs=" + CUTS_ROOT + pathSeparator + "contrib" + pathSeparator + "java");
    args.add ("-Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB");
    args.add ("-Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton");

    // Initalize the CORBA ORB.
    this.orb_ = org.omg.CORBA.ORB.init (args.toArray (new String [0]), null);
  }

  /**
   * Connect to the local logging client.
   */
  public void connect (String str)
  {
    try
    {
      // Get a reference to the logging client.
      org.omg.CORBA.Object obj = this.orb_.string_to_object (str);
      this.loggingClient_ = CUTS.LoggingClientHelper.narrow (obj);

      // Set the UUID for the logger.
    }
    catch (Exception ex)
    {
      ex.printStackTrace ();
    }
  }

  /**
   * Set the UUID for the logger. This will force the logger to request
   * a new object for the logging client.
   *
   * @param[in]         uuid            UUID for the client logger.
   */
  public void setUUID (CUTS.UUID uuid)
  {
    // Release the existing logger object, if applicable.
    if (this.logger_ != null)
      this.release ();

    // Request a new logger object.
    this.logger_ = this.loggingClient_.get_logger (uuid);
  }

  /**
   * Get the UUID associated with this client logger.
   *
   * @return            UUID associated with logger.
   */
  public CUTS.UUID getUUID ()
  {
    return this.logger_.uuid ();
  }

  /**
   * Disconnect from the test manager.
   */
  public void disconnect ()
  {
    try
    {
      if (this.loggingClient_ != null)
      {
        // Release existing logging before destoying logging client object.
        if (this.logger_ != null)
          this.release ();

        // We are now officially disconnected.
        this.loggingClient_ = null;
      }
    }
    catch (Exception ex)
    {
      ex.printStackTrace ();
    }
  }

  /**
   * Log a message to the database.
   *
   * @param[in]           priority          Level of the message
   * @param[in]           message           Message to log
   */
  public void logMessage (int priority, String message)
  {
    try
    {
      // Construct log message to send to logger.
      CUTS.LogMessage msg = new CUTS.LogMessage ();
      msg.timestamp = this.getTimeOfDay ();
      msg.severity = priority;
      msg.message = message.toCharArray ();

      // Send the message to the logger.
      this.logger_.log (msg);
    }
    catch (Exception ex)
    {
      ex.printStackTrace ();
    }
  }

  /**
   * Helper method that releases the current logger object.
   */
  private void release ()
  {
    this.loggingClient_.release (this.logger_);
    this.logger_ = null;
  }

  /**
   * Get the current time of day.
   *
   * @return      Current time as a time value
   */
  private CUTS.TimeValue getTimeOfDay ()
  {
    long msec = System.currentTimeMillis ();

    // Convert millisecond units to seconds;
    long secs = msec / 1000;

    // Convert remainder to microseconds;
    long usec = (msec - (secs * 1000)) * 1000;

    return new CUTS.TimeValue ((int)secs, (int)usec);
  }

  /// ORB used by the logger to communicate with outside world.
  private org.omg.CORBA.ORB orb_ = null;

  /// Local logging client object.
  private CUTS.LoggingClient loggingClient_ = null;

  /// Logger responsible for collecting messages.
  private CUTS.Logger logger_ = null;
}
