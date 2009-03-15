import java.lang.*;
import java.util.TimerTask;
import java.util.concurrent.locks.*;

/**
 * @class ExponentialPeriodicTaskTest
 *
 * Test for the ExponentialPeriodicTaskStrategy
 */
public class ExponentialPeriodicTaskTest
{
  private class TestEventHandler
    extends CUTS.PeriodicTaskHandler <ExponentialPeriodicTaskTest>
  {
    public TestEventHandler (CUTS.PeriodicTask<ExponentialPeriodicTaskTest> task)
    {
      super (task);
    }

    public void handleTimeout ()
    {
      this.task_.getOwner ().decrementEventCount ();
    }
  }

  private class TestEventHandlerFactory
    implements CUTS.PeriodicTaskHandlerFactory <ExponentialPeriodicTaskTest>
  {
    public TestEventHandlerFactory ()
    {

    }

    public TimerTask createTimerTask (CUTS.PeriodicTask<ExponentialPeriodicTaskTest> task)
    {
      return new TestEventHandler (task);
    }
  }

  public ExponentialPeriodicTaskTest (long events)
  {
    this.maxEvents_ = events;
  }

  public long getEventCount ()
  {
    return this.maxEvents_;
  }

  public void run (long hertz, long events)
  {
    // Set the max number of events.
    this.maxEvents_ = events;

    // Configure the periodic task.
    this.periodic_ = new CUTS.PeriodicTask<ExponentialPeriodicTaskTest> (this, new TestEventHandlerFactory ());
    this.periodic_.setPeriodicTaskStrategy (new CUTS.ExponentialPeriodicTaskStrategy (hertz));

    // Schedule the first timeout for the event.
    this.periodic_.scheduleNextTimeout ();
  }

  public void shutdown ()
  {
    this.periodic_.cancel ();
  }

  public void waitForCompletion ()
    throws InterruptedException
  {
    try
    {
      this.lock_.lock ();

      if (this.events_ < this.maxEvents_)
        this.isDone_.await ();
    }
    finally
    {
      this.lock_.unlock ();
    }
  }

  public void decrementEventCount ()
  {
    try
    {
      this.lock_.lock ();

      if (this.events_ < this.maxEvents_)
        ++ this.events_;

      System.out.println ((this.maxEvents_ - this.events_) + " event(s) remaining...");

      if (this.events_ == this.maxEvents_)
        this.isDone_.signal ();
    }
    finally
    {
      this.lock_.unlock ();
    }
  }

  private CUTS.PeriodicTask<ExponentialPeriodicTaskTest> periodic_;

  private final Lock lock_ = new ReentrantLock ();

  private final Condition isDone_ = this.lock_.newCondition ();

  private long events_ = 0;

  private long maxEvents_ = 0;

  /**
   * Main entry point for the application.
   *
   * @param[in]         args          Command-line arguments
   */
  public static void main (String [] args)
  {
    ExponentialPeriodicTaskTest test = new ExponentialPeriodicTaskTest (10000);

    try
    {
      // Instantiate a new test.
      System.out.println ("creating the test");

      // Set the strategy for the test.
      System.out.println ("running the test");
      long startTime = System.currentTimeMillis ();
      test.run (7, 10000);

      // Wait for the test to complete.
      System.out.println ("waiting for the test to complete");
      test.waitForCompletion ();
      long stopTime = System.currentTimeMillis ();

      double eventPerSecond = (double)test.getEventCount () / ((double)(stopTime - startTime) / 1000.0);

      System.out.println ("emulated " + eventPerSecond + " events / sec");
    }
    catch (Exception e)
    {
      e.printStackTrace ();
    }
    finally
    {
      test.shutdown ();
    }
  }
}
