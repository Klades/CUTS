// -*- java -*-

import CUTS.Logger;

/**
 * @class TestLoggerTest
 */
public class TestLoggerTest
{
  public TestLoggerTest ()
  {

  }

  public void run (String [] args)
  {
    this.logger_.configure (10000);
    this.logger_.connect ("TestLogger");
    this.logger_.logMessage (Logger.LM_INFO, "This is an example message");
  }

  private Logger logger_ = new Logger ();

  public static void main (String [] args)
  {
    try
    {
      TestLoggerTest test = new TestLoggerTest ();
      test.run (args);
    }
    catch (Exception e)
    {
      e.printStackTrace ();
    }
  }
}
