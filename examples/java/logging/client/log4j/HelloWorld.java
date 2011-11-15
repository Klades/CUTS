import org.apache.log4j.Logger;
import org.apache.log4j.LogManager;
import org.apache.log4j.Level;

public class HelloWorld
{
  public static void main (String [] args)
  {
    try
    {
      Logger logger = Logger.getLogger(HelloWorld.class);
      logger.log(Level.DEBUG, "Hello, World!!");

      logger.log(Level.DEBUG, "This is message 1 before sleep at " + System.currentTimeMillis());

      // sleep for 5 seconds
      Thread.sleep(5000);

      logger.log(Level.DEBUG, "This is message 1 after sleep at " + System.currentTimeMillis());

      // Make sure the shutdown the log manager.
      LogManager.shutdown();
    }
    catch (Exception ex)
    {
      ex.printStackTrace ();
    }
  }
}
