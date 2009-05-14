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
import org.apache.log4j.AppenderSkeleton;
import org.apache.log4j.spi.LoggingEvent;

/**
 * @class TestAppender
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

  /**
   * Append the logging event. This will send the event to the logging
   * client. The logging client will then send the event to the logging
   * server.
   */
  public void append (LoggingEvent event)
  {

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

  }
}
