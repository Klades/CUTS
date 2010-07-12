/**
 * @file        PeriodicTaskStrategy.java
 *
 * $Id$
 *
 * @author      James H. Hill
 */

package CUTS;

/**
 * @interface PeriodicTaskStrategy
 *
 * Interface for PeriodicTask strategies. It allow customization
 * of the PeriodicTask to generate events with different arrival
 * distributions.
 */
public interface PeriodicTaskStrategy
{
  /**
   * Get the delay (or interarrival time) for the next event
   * to enter the system.
   *
   * @return      Delay in milliseconds
   */
  public long getDelay ();

  /**
   * Set the hertz for generating events
   *
   * @param[in]         h         New hertz value
   */
  public void setHertz (long h);
  
  public long getHertz ();
}
