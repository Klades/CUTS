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
import java.util.Random;
import java.lang.Integer;

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

  private Random random_ = new Random ();

  public PeriodicTask (double probability)
  {
    this.probability_ = probability;
  }

  public void run ()
  {
    // Calculate the score for this timeout event.
    double score = (double)this.random_.nextInt () / (double)Integer.MAX_VALUE;

    // Execute the timeout handler, if applicable.
    if (score <= this.probability_)
      this.handleTimeout ();
  }

  public abstract void handleTimeout ();
}

