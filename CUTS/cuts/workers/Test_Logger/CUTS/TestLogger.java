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

import java.util.ArrayList;

/**
 * @class TestLogger
 */
public class TestLogger
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

  /**
   * Default constructor.
   */
  public TestLogger ()
  {
    final String CUTS_ROOT = System.getenv ("CUTS_ROOT");
    final String pathSeparator = System.getProperty ("file.seperator");

    ArrayList<String> args = new ArrayList ();
    args.add ("-Djava.endorsed.dirs=" + CUTS_ROOT + pathSeparator + 
              "contrib" + pathSeparator + "java");
    args.add ("-Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB");
    args.add ("-Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton");

    this.orb_ = org.omg.CORBA.ORB.init (args.toArray (new String [0]), null);
  }

  /**
   * Destructor
   */
  protected void finalize () throws Throwable
  {
    // Destroy the ORB.
    this.orb_.destroy ();

    // Pass control to the base class.
    super.finalize (); 
  }

  /**
   * Configure the test logger. This will setup the location of the 
   * test manager (ipaddress:port) and the port number of the logging
   * client on this local host.
   */
  public void configure (short loggerClientPort)
  {
    // Construct the string location of the logging client.
    String corbalocLC = 
      "corbaloc:iiop:localhost";

    if (loggerClientPort > -1)
      corbalocLC += ":" + loggerClientPort;

    corbalocLC += "/CUTS/TestLoggerClient";

    // Convert the string into an actual object.
    this.loggerClient_ =
      CUTS.TestLoggerClientHelper.narrow (
      this.orb_.string_to_object (corbalocLC));
  }

  /**
   * Connect the to the test manager at the specified location. The 
   * test logger will cache the host name for later usage, such as
   * reconnecting to the test manager to get the latest test id.
   * 
   * @param[in]         hostName          Location of the test manager.
   */
  public void connect (String testManagerLocation, String testManagerName)
  {
    this.testManagerLocation_ = testManagerLocation;
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
    // Construct the corbaloc of the test manager.
    String corbalocTM =
      "corbaloc:iiop:" + this.testManagerLocation_ +
      "/CUTS/TestManager/" + this.testManagerName_;

    // Convert the location into the actual test manager.
    CUTS.TestManager tm =
      CUTS.TestManagerHelper.narrow (
      this.orb_.string_to_object (corbalocTM));

    // Get the current id of the test. We need to use this to identify
    // the test which the log message belongs.
    this.testNumber_ = tm.get_current_test_id ();
  }

  /**
   * Log a message to the database.
   * 
   * @param[in]           priority          Level of the message
   * @param[in]           message           Message to log
   */
  public void logMessage (int priority, String message)
  {
    this.loggerClient_.log_msg (this.testNumber_, priority, message);
  }
}
