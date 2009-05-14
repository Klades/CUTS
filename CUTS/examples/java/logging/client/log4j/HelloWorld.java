import org.apache.log4j.Logger;
import org.apache.log4j.Level;

public class HelloWorld
{
  public static void main (String [] args)
  {
    Logger logger = Logger.getLogger (HelloWorld.class);
    logger.log (Level.DEBUG, "Hello, World!!");
  }
}
