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

package CUTS;

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

  /// The test number for the logger.
  private int testNumber_ = -1;

  /// The location of the test manager.
  private String testManagerLocation_ = "localhost";

  private String testManagerName_ = "(default)";

  /// ORB used by the logger to communicate with outside world.
  private org.omg.CORBA.ORB orb_ = null;

  private CUTS.TestLoggerClient loggerClient_ = null;

  private CUTS.TestLoggerFactory loggerFactory_ = null;

  private CUTS.TestLogger testLogger_ = null;

  private NamingContextExt naming_ = null;

  /// The default logging client port number.
  private int loggingClientPort_ = 10000;

  /**
   * Default constructor.
   */
  public Logger ()
  {
    final String CUTS_ROOT = System.getenv ("CUTS_ROOT");
    final String pathSeparator = System.getProperty ("file.seperator");

    ArrayList<String> args = new ArrayList ();
    args.add ("-Djava.endorsed.dirs=" + CUTS_ROOT + pathSeparator +
              "contrib" + pathSeparator + "java");
    args.add ("-Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB");
    args.add ("-Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton");

    // Initalize the CORBA ORB.
    this.orb_ = org.omg.CORBA.ORB.init (args.toArray (new String [0]), null);
    this.configure ();
  }

  /**
   * Configure the test logger. This will setup the location of the
   * test manager (ipaddress:port) and the port number of the logging
   * client on this local host.
   */
  private void configure ()
  {
    this.configure (this.loggingClientPort_);
  }

  /**
   * Configure the logger with the logger client. This primarily sets
   * the port number to connect to the logger client.
   */
  public void configure (int port)
  {
    // Construct the string location of the logging client.
    String location =
      "corbaloc:iiop:localhost:" + port + "/CUTS/TestLoggerClient";

    try
    {
      // Convert the string into an actual object.
      this.loggerClient_ =
        CUTS.TestLoggerClientHelper.narrow (
        this.orb_.string_to_object (location));

      this.loggingClientPort_ = port;
    }
    catch (Exception ex)
    {
      ex.printStackTrace ();
    }
  }

  /**
   * Connect the to the test manager at the specified location. The
   * test logger will cache the host name for later usage, such as
   * reconnecting to the test manager to get the latest test id.
   *
   * @param[in]         testManagerName     Location of the test manager.
   */
  public void connect (String testManagerName)
  {
    this.testManagerName_ = testManagerName;
    this.connect ();
  }

  /**
   * Connect to the cached test manager and get the test id. This is useful
   * if the same test manager starts a new test and the test logger needs to
   * updates its test id.
   */
  public void connect ()
  {
    // Save the old test number.
    int oldTestNumber = this.testNumber_;

    try
    {
      this.naming_ =
        NamingContextExtHelper.narrow (
        this.orb_.string_to_object (
        System.getProperty ("ORBInitRef.NameService")));

      String strName =
        "CUTS/TestManager/" + this.testManagerName_;

      // Resolve the location of the test manager using the naming service.
      CUTS.TestManager tm =
        CUTS.TestManagerHelper.narrow (
        this.naming_.resolve (this.naming_.to_name (strName)));

      // Get the current id of the test. We need to use this to identify
      // the test which the log message belongs.
      this.testNumber_ = tm.test_number ();
    }
    catch (Exception ex)
    {
      ex.printStackTrace ();
    }

    try
    {
      if (this.testLogger_ == null ||
          oldTestNumber != this.testNumber_)
      {
        // Instruct the logger client to create a new factory.
        this.loggerFactory_ = this.loggerClient_.create (this.testNumber_);

        // Create a new thread local test logger.
        this.testLogger_ = this.loggerFactory_.create ();
      }
    }
    catch (Exception ex)
    {
      ex.printStackTrace ();
    }
  }

  /**
   * Disconnect from the test manager.
   */
  public void disconnect ()
  {
    try
    {
      if (this.loggerFactory_ != null)
        this.loggerFactory_.destroy (this.testLogger_);

      if (this.loggerClient_ != null)
        this.loggerClient_.destroy (this.loggerFactory_);
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
      // Get the current time value for the message.
      CUTS.Time_Stamp tv = this.getTimeOfDay ();

      // Send the log message to the logger.
      this.testLogger_.log (tv, priority, message.toCharArray ());
    }
    catch (Exception ex)
    {
      ex.printStackTrace ();
    }
  }

  /**
   * Get the test number used by the logger.
   *
   * @return      The test number for the logger.
   */
  public int getTestNumber ()
  {
    return this.testNumber_;
  }

  /**
   * Get the current time of day.
   *
   * @return      Current time as a time value
   */
  private CUTS.Time_Stamp getTimeOfDay ()
  {
    long msec = System.currentTimeMillis ();

    // Convert millisecond units to seconds;
    long secs = msec / 1000;

    // Convert remainder to microseconds;
    long usec = (msec - (secs * 1000)) * 1000;

    return new CUTS.Time_Stamp ((int)secs, (int)usec);
  }
}
