// -*- Java -*-

//=============================================================================
/**
 * @file        ConstantPeriodicTaskStrategy.java
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

package cuts;

/**
 * @interface ConstantPeriodicTaskStrategy
 *
 * Interface for PeriodicTask strategies. It allow customization
 * of the PeriodicTask to generate events with different arrival
 * distributions.
 */
public class ConstantPeriodicTaskStrategy
  implements PeriodicTaskStrategy
{
  /**
   * Initializing constructor
   *
   * @param[in]       hertz         Hertz of the periodic task
   */
  public ConstantPeriodicTaskStrategy ()
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
    return this.delay_;
  }

  /**
   * Set the hertz for generating events
   *
   * @param[in]         h         New hertz value
   */
  public void setHertz (long h)
  {
    this.delay_ = 1000 / h;
  }

  public long getHertz ()
  {
    return 1000 / this.delay_;
  }

  /// The delay for the periodic task.
  private long delay_;
}
