// -*- Java -*-

//=============================================================================
/**
 * @file        LoggingClientAppender.java
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

package cuts.log4j;
import java.util.Hashtable;
import java.util.Arrays;
import org.apache.log4j.AppenderSkeleton;
import org.apache.log4j.Level;
import org.apache.log4j.spi.LoggingEvent;
import CUTS.client.logging.Logger;
import CUTS.client.TestManagerClient;

/**
 * @class LoggingClientAppender
 *
 * Log4j appender that logs data to the CUTS logging client.
 */
public class LoggingClientAppender extends AppenderSkeleton
{
  /**
   * Default constructor.
   */
  public LoggingClientAppender ()
  {
    // Use a NIL UUID as the current value.
    byte [] data4 = new byte [6];
    Arrays.fill (data4, (byte) 0);

    this.testUUID_ = new CUTS.UUID (0, (short) 0, (short) 0, data4);
  }

  /**
   * Activate the logger using the current options. The options are
   * typically set in the log4j.properties file.
   */
  public void activateOptions ()
  {
    this.logger_.connect (this.loggerClient_, this.testUUID_);
  }

  /**
   * Set the port for sending events to the logging client on the
   * localhost.
   *
   * @param[in]       port          Port number
   */
  public void setLoggerClient (String loggerClient)
  {
    this.loggerClient_ = loggerClient;
  }

  /**
   * Set the IOR for the test logger.
   *
   * @param[in]       ior           IOR of test logger.
   */
  public void setTestLocation (String testLocation)
  {
    try
    {
      // Resolve the location of the test manager.
      TestManagerClient testManagerClient = new TestManagerClient ();
      testManagerClient.connect (testLocation);

      // Get the current test UUID from the manager.
      CUTS.TestManager testManager = testManagerClient.getTestManager ();
      CUTS.TestDetails testDetails = testManager.details ();
      this.testUUID_ = testDetails.uid;
    }
    catch (Exception ex)
    {
      ex.printStackTrace ();
    }
  }

  /**
   * Append the logging event. This will send the event to the logging
   * client. The logging client will then send the event to the logging
   * server.
   */
  public void append (LoggingEvent event)
  {
    int level = LoggingClientAppender.translateLevel (event.getLevel ());
    this.logger_.logMessage (level, event.getRenderedMessage ());
  }

  /**
   * Determine if the appender requires a layout.
   */
  public boolean requiresLayout ()
  {
    return false;
  }

  /**
   * Close the logging client appender. This will disconnect the
   * appender from the logging client.
   */
  public void close ()
  {
    this.logger_.disconnect ();
  }

  /**
   * Helper method to translate a log4j priority to its corresponding
   * CUTS logger priority.
   *
   * @param[in]       level           Level to translate.
   */
  private static int translateLevel (Level level)
  {
    return LoggingClientAppender.levelTable_.get (level);
  }

  /**
   * Initialize routine for all the static section.
   */
  static
  {
    // Initialize the levelTable_ object.
    LoggingClientAppender.levelTable_ = new Hashtable<Level, Integer> ();
    LoggingClientAppender.levelTable_.put (Level.DEBUG, Logger.LM_DEBUG);
    LoggingClientAppender.levelTable_.put (Level.ERROR, Logger.LM_ERROR);
    LoggingClientAppender.levelTable_.put (Level.FATAL, Logger.LM_CRITICAL);
    LoggingClientAppender.levelTable_.put (Level.INFO, Logger.LM_INFO);
    LoggingClientAppender.levelTable_.put (Level.TRACE, Logger.LM_TRACE);
    LoggingClientAppender.levelTable_.put (Level.WARN, Logger.LM_WARNING);

    // The following our not directly mappable.
    LoggingClientAppender.levelTable_.put (Level.ALL, Logger.LM_DEBUG);
    LoggingClientAppender.levelTable_.put (Level.OFF, Logger.LM_SHUTDOWN);
  }

  /// The actual logger for the appender.
  private Logger logger_ = new Logger ();

  /// Port of the local logging client.
  private String loggerClient_ = null;

  /// Initialization state of the appender/logger.
  private boolean isInit_ = false;

  /// The current UUID for the test.
  private CUTS.UUID testUUID_;

  /// Table for tranlating Level objects to integer values.
  private static Hashtable<Level, Integer> levelTable_;
}
