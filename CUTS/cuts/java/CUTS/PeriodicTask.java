/**
 * @file        PeriodicTask.java
 *
 * $Id$
 *
 * @author      James H. Hill
 */

package CUTS;
import java.util.Timer;
import java.util.TimerTask;

/**
 * @class PeriodicTask
 *
 * Base class for the periodic tasks of a component. The periodic task
 * will fire based on the specified probability at fixed schedule
 * intervals. Each task must override the handleTimeout () method,
 * which defines the workload that must execute during each timeout
 * interval.
 */
public class PeriodicTask <T>
{
  /**
   * Default constructor
   */
  public PeriodicTask (T owner, PeriodicTaskHandlerFactory <T> factory)
  {
    this.owner_ = owner;
    this.factory_ = factory;
  }

  /**
   * Set the strategy for the periodic task. This will determine
   * the event distribution for the task.
   *
   * @param[in]         strategy          Strategy for the task
   */
  public void setPeriodicTaskStrategy (PeriodicTaskStrategy strategy)
  {
    this.strategy_ = strategy;
  }

  /**
   * Set the hertz for generating events
   *
   * @param[in]         h         New hertz value
   */
  public void setHertz (long h)
  {
    if (this.strategy_ != null)
      this.strategy_.setHertz (h);
  }

  /**
   * Get the strategy for the periodic task.
   *
   * @return            Strategy for the task.
   */
  public PeriodicTaskStrategy getPeriodicTaskStrategy ()
  {
    return this.strategy_;
  }

  /**
   * Schedule the next timeout for the periodic task.
   */
  public void scheduleNextTimeout ()
  {
    long delay = this.strategy_.getDelay ();
    TimerTask task = this.factory_.createTimerTask (this);

    this.timer_.schedule (task, delay);
  }

  public void cancel ()
  {
    this.timer_.cancel ();
  }

  /**
   * Get the owner of the periodic event
   *
   * @return            Parent of the periodic event.
   */
  public T getOwner ()
  {
    return this.owner_;
  }

  /// The event distribution for the periodic task.
  private PeriodicTaskStrategy strategy_;

  /// The timer thread for the task.
  private Timer timer_ = new Timer ();

  /// Parent/owner of the object.
  private T owner_;

  /// Factory for creating timer task objects.
  private PeriodicTaskHandlerFactory <T> factory_;
}

