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
import org.apache.log4j.AppenderSkeleton;
import org.apache.log4j.Level;
import org.apache.log4j.spi.LoggingEvent;

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

  }

  public void activateOptions ()
  {
    this.logger_.configure ((short)this.localPort_);
    this.logger_.connectIOR (this.testIOR_);
  }

  /**
   * Set the port for sending events to the logging client on the
   * localhost.
   *
   * @param[in]       port          Port number
   */
  public void setPort (int port)
  {
    this.localPort_ = port;
  }

  /**
   * Set the IOR for the test logger.
   *
   * @param[in]       ior           IOR of test logger.
   */
  public void setTestIOR (String ior)
  {
    this.testIOR_ = ior;
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
    LoggingClientAppender.levelTable_.put (Level.DEBUG, CUTS.Logger.LM_DEBUG);
    LoggingClientAppender.levelTable_.put (Level.ERROR, CUTS.Logger.LM_ERROR);
    LoggingClientAppender.levelTable_.put (Level.FATAL, CUTS.Logger.LM_CRITICAL);
    LoggingClientAppender.levelTable_.put (Level.INFO, CUTS.Logger.LM_INFO);
    LoggingClientAppender.levelTable_.put (Level.TRACE, CUTS.Logger.LM_TRACE);
    LoggingClientAppender.levelTable_.put (Level.WARN, CUTS.Logger.LM_WARNING);

    // The following our not directly mappable.
    LoggingClientAppender.levelTable_.put (Level.ALL, CUTS.Logger.LM_DEBUG);
    LoggingClientAppender.levelTable_.put (Level.OFF, CUTS.Logger.LM_SHUTDOWN);
  }

  /// The actual logger for the appender.
  private CUTS.Logger logger_ = new CUTS.Logger ();

  /// Port of the local logging client.
  private int localPort_;

  /// Initialization state of the appender/logger.
  private boolean isInit_ = false;

  /// Table for tranlating Level objects to integer values.
  private static Hashtable<Level, Integer> levelTable_;

  private String testIOR_;
}
