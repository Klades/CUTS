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
 * @class TestLogger
 */
public class TestLogger extends Thread
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

  private NamingContextExt naming_ = null;

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

    // Register ourselves with the runtime framework to ensure we exit
    // gracefully. :-)
    Runtime.getRuntime ().addShutdownHook (this);

    // Finish the configuration.
    this.configure ();
  }

  protected void finalize () throws Throwable
  {
    try
    {
      if (this.orb_ != null)
        this.unconfigure ();
    }
    catch (Exception ex)
    {
      ex.printStackTrace ();
    }
    finally
    {
      super.finalize ();
    }
  }

  /**
   * Run method called by the virtual machine when the application
   * is ready to shutdown. This allows use to gracefully unregister
   * the logger with the client server.
   */
  public void run ()
  {
    try
    {
      if (this.orb_ != null)
        this.unconfigure ();
    }
    catch (Exception ex)
    {
      ex.printStackTrace ();
    }
  }

  /**
   * Configure the test logger. This will setup the location of the 
   * test manager (ipaddress:port) and the port number of the logging
   * client on this local host.
   */
  private void configure ()
  {
    String propertyFile = "CUTS.TestLogger.configuration";

    propertyFile = 
      System.getProperty ("CUTS.TestLogger.configuration", propertyFile);

    int loggerClientPort = -1;

    try
    {
      // Load the properties file that contains the configuration.
      FileInputStream fileInput = new FileInputStream (propertyFile);
      Properties loggerProperties = new Properties ();
      loggerProperties.load (fileInput);

      if (loggerProperties.containsKey ("cuts.testlogger.client.logger.port"))
      {
        try
        {
          loggerClientPort =
            Integer.parseInt (
            loggerProperties.getProperty ("cuts.testlogger.client.logger.port"));
        }
        catch (Exception ex)
        {
          ex.printStackTrace ();
        }
      }

      if (loggerProperties.containsKey ("cuts.testlogger.testmanager.name"))
      {
        this.testManagerName_ =
          loggerProperties.getProperty ("cuts.testlogger.testmanager.name");
      }
    }
    catch (FileNotFoundException ex)
    {
      // ingore this exception; configuration is optional
    }
    catch (Exception ex)
    {
      ex.printStackTrace ();
    }

    // Construct the string location of the logging client.
    String corbalocLC = "corbaloc:iiop:localhost";

    if (loggerClientPort != -1)
      corbalocLC += ":" + loggerClientPort;

    corbalocLC += "/CUTS/TestLoggerClient";

    // Convert the string into an actual object.
    this.loggerClient_ =
      CUTS.TestLoggerClientHelper.narrow (
      this.orb_.string_to_object (corbalocLC));
  }

  /**
   * Unconfigure the test logger.
   */
  private void unconfigure ()
  {
    if (this.testNumber_ != -1)
    {
      // Unregister the test with the logging client.
      this.loggerClient_.unregister_test (this.testNumber_);
      this.testNumber_ = -1;
    }

    // Destroy the ORB.
    this.orb_.destroy ();
    this.orb_ = null;
  }

  /**
   * Connect the to the test manager at the specified location. The 
   * test logger will cache the host name for later usage, such as
   * reconnecting to the test manager to get the latest test id.
   * 
   * @param[in]         hostName          Location of the test manager.
   */
  public void connect (String testManagerLocation)
  {
    this.connect (testManagerLocation, this.testManagerName_);
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
    // Get a reference to the naming service.
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
      int oldTestNumber = this.testNumber_;
      this.testNumber_ = tm.test_number ();

      // Register the test with the client.
      this.loggerClient_.register_test (this.testNumber_, oldTestNumber);
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
      // Create a new log message.
      CUTS.LogMessage msg = new CUTS.LogMessage ();

      // Initialize the contents of the log message.
      msg.test = this.testNumber_;
      msg.timestamp = (int) System.currentTimeMillis ();
      msg.priority = priority;
      msg.message = message;

      // Send the message to the logger client.
      System.out.println (message);
      this.loggerClient_.log (msg);
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
}
