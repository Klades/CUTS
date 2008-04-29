/**
 * @file        PeriodicTask.java
 * 
 * $Id$
 * 
 * @author      James H. Hill
 */

package cuts.java;

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
public abstract class PeriodicTask extends TimerTask
{
  /// The probability of the timer firing.
  private double probability_;
  
  public PeriodicTask (double probability)
  {
    this.probability_ = probability;
  }
  
  public void run ()
  {
    this.handleTimeout ();
  }

  abstract void handleTimeout ();
}

