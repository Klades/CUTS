package CUTS;

import org.apache.log4j.Logger;

/**
 * @class ProcessHandler
 *
 * Helper class for handling spawned process. It will ensure that
 * the input/error buffers periodically emptied.
 */
public class ProcessHandler extends Thread
{
  private Process process_;

  private final Logger logger_ = Logger.getLogger (ProcessHandler.class);

  /**
   * Initializing constructor.
   */
  public ProcessHandler (Process process)
  {
    this.process_ = process;
  }

  /**
   * Run the thread.
   */
  public void run ()
  {
    try
    {
      // Create threads for reading the process input and error stream.
      this.logger_.debug ("creating threads to read input streams");
      Thread errorThread =
        new Thread (new ProcessStreamReader (this.process_.getErrorStream (), "error"));

      Thread inputThread =
        new Thread (new ProcessStreamReader (this.process_.getInputStream (), "input"));

      // Start each of the threads.
      this.logger_.debug ("starting threads to read input streams");
      inputThread.start ();
      errorThread.start ();

      // Wait for the threads to exit.
      this.logger_.debug ("waiting for threads to exit");
      inputThread.join ();
      errorThread.join ();
    }
    catch (Exception e)
    {
      this.logger_.error (e.getMessage (), e);
    }
  }

  public Process getProcess ()
  {
    return this.process_;
  }
}

