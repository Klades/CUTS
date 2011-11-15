// -*- Java -*-

//=============================================================================
/**
 * @file        PeriodicTaskHandler.java
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

package cuts;
import java.util.TimerTask;

/**
 * @interface PeriodicTaskHandlerFactory
 */
public interface PeriodicTaskHandlerFactory <T>
{
  public TimerTask createTimerTask (PeriodicTask <T> task);
}
