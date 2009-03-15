/**
 * @file        ExponentialPeriodicTaskStrategy.java
 *
 * $Id$
 *
 * @author      James H. Hill
 */

package CUTS;
import java.util.Random;
import java.lang.Math;

/**
 * @interface ExponentialPeriodicTaskStrategy
 *
 * Interface for PeriodicTask strategies. It allow customization
 * of the PeriodicTask to generate events with different arrival
 * distributions.
 */
public class ExponentialPeriodicTaskStrategy
  implements PeriodicTaskStrategy
{
  /**
   * Default constuctor
   */
  public ExponentialPeriodicTaskStrategy ()
  {

  }

  /**
   * Get the delay (or interarrival time) for the next event
   * to enter the system.
   *
   * @return      Delay in milliseconds
   */
  public long getDelay ()
  {
    // Determine the next arrival in seconds.
    double secs = -1.0 / this.hertz_ * Math.log (1.0 - this.random_.nextDouble ());

    // Convert the seconds to milliseconds
    return (long)Math.ceil (secs * 1000.0);
  }

  /**
   * Set the hertz for generating events
   *
   * @param[in]         h         New hertz value
   */
  public void setHertz (long hertz)
  {
    this.hertz_ = (double) hertz;
  }

  /// The delay for the periodic task.
  private double hertz_;

  /// Random number generator.
  private Random random_ = new Random ();
}
