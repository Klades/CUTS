package cuts.java;

import org.apache.log4j.Logger;
import java.io.*;

/**
 * @class ProcessStreamReader
 */
public class ProcessStreamReader implements Runnable
{
  private BufferedReader bufferedReader_;

  private PrintStream printStream_;

  public ProcessStreamReader (InputStream inputStream, String type)
  {
    this.bufferedReader_ = 
      new BufferedReader (new InputStreamReader (inputStream));

    if (type.equals ("input"))
      this.printStream_ = System.out;
    else if (type.equals ("error"))
      this.printStream_ = System.err;
    else
      this.printStream_ = System.out;
  }

  public void run ()
  {
    try
    {
      String line;

      while ((line = this.bufferedReader_.readLine ()) != null)
        this.printStream_.println (line);
    }
    catch (Exception e)
    {
      e.printStackTrace ();
    }
    finally
    {
      try
      {
        this.bufferedReader_.close ();
      }
      catch (Exception e)
      {
        e.printStackTrace ();
      }
    }
  }
}

