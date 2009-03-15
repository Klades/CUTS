//=============================================================================
/**
 * @file        PeriodicTaskHandler.java
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

package CUTS;
import java.util.TimerTask;

/**
 * @class PeriodicTaskHandler
 *
 * Base class for the periodic tasks of a component. The periodic task
 * will fire based on the specified probability at fixed schedule
 * intervals. Each task must override the handleTimeout () method,
 * which defines the workload that must execute during each timeout
 * interval.
 */
public abstract class PeriodicTaskHandler <T> extends TimerTask
{
  /**
   * Default constructor
   */
  public PeriodicTaskHandler (PeriodicTask <T> task)
  {
    this.task_ = task;
  }

  /**
   * Run the periodic task.
   */
  public void run ()
  {
    // Schedule the next timeout for this task.
    this.task_.scheduleNextTimeout ();

    // Handle the timeout/event.
    this.handleTimeout ();
  }

  /// Callback method for the timeout event.
  public abstract void handleTimeout ();

  /// Parent/owner of the object.
  protected PeriodicTask <T> task_;
}

