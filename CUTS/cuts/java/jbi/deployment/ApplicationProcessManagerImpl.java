// -*- JAVA -*-

package cuts.java.jbi.deployment;

import cuts.java.ProcessHandler;
import org.apache.log4j.Logger;
import java.util.*;
import java.util.concurrent.locks.*;
import java.util.concurrent.TimeUnit;

/**
 * @class ApplicationProcessManagerImpl
 * 
 * Implementation of the ApplicationProcessManager interface.
 */
public class ApplicationProcessManagerImpl
  extends ApplicationProcessManagerPOA
{
  private class Item
  {
    ProcessHandler processHandler_;

    ApplicationProcess appProcess_;
  }

  private final HashMap<String, Item> processMap_ =
    new HashMap<String, Item> ();

  private final Logger logger_ =
    Logger.getLogger (ApplicationProcessManagerImpl.class);

  private final Lock lock_ = new ReentrantLock ();

  private final Condition processRegistered_ = this.lock_.newCondition ();

  /**
   * Default constructor.
   */
  public ApplicationProcessManagerImpl ()
  {

  }

  /**
   * Register a process with the manager.
   */
  public void registerProcess (ApplicationProcess process)
  {
    this.logger_.debug ("registering process group [" + process.name () + "]");

    // Store the process in the process map.
    Item item = new Item ();
    item.appProcess_ = process;

    this.processMap_.put (process.name (), item);

    // Signal all processes that the application registered itself.
    this.logger_.debug ("notifying all waiting threads of registration");
    this.lock_.lock ();

    try
    {
      this.processRegistered_.signalAll ();
    }
    finally
    {
      this.lock_.unlock ();
    }
  }

  /**
   * Remove a process for the manager.
   */
  public void unregisterProcess (ApplicationProcess process)
  {
    // Remove the application process reference, but not the actual 
    // process. We need to eventually wait for the process to exit. Or,
    // we can assume the process exits.
    this.lock_.lock ();

    try
    {
      String name = process.name ();
      this.logger_.debug ("unregistering process " + name);
      this.processMap_.remove (name);
    }
    finally
    {
      this.lock_.unlock ();
    }
  }

    public void start ()
    {
        this.lock_.lock ();

        try
            {
                this.logger_.debug ("starting each of the application processes");
                for (Map.Entry <String, Item> entry : this.processMap_.entrySet ())
                    {
                        ApplicationProcess appProcess = entry.getValue ().appProcess_;
                        appProcess.start ();
                    }
            }
        finally
            {
                this.lock_.unlock ();
            }
    }

  /**
   * Get the process with the specified name.
   */
  public ApplicationProcess getProcess (String name)
  {
    ApplicationProcess process = null;

    Item item = this.processMap_.get (name);

    if (item != null)
      process = item.appProcess_;

    return process;
  }

  /**
   * Wait for the process to register itself with the manager.
   */
  public void waitForProcessRegistered ()
    throws InterruptedException
  {
    try
    {
      this.lock_.lock ();
      this.processRegistered_.await ();
    }
    finally
    {
      this.lock_.unlock ();
    }
  }

  /**
   * Wait for the process to register itself with the manager.
   */
  public boolean waitForProcessRegistered (long time, TimeUnit units)
    throws InterruptedException
  {
    boolean retval = false;

    try
    {
      this.lock_.lock ();
      retval = this.processRegistered_.await (time, units);
    }
    finally
    {
      this.lock_.unlock ();
      return retval;
    }
  }

  /**
   * Store the actual process with its application process.
   */
  public void setProcess (String name, ProcessHandler process)
  {
    Item item = this.processMap_.get (name);

    if (item != null)
    {
      this.logger_.debug ("associating " + name +
                          " process handler with its application process");
                    
      item.processHandler_ = process;
      this.processMap_.put (name, item);
    }
    else
    {
      this.logger_.error ("process " + name + " is not registered");
    }
  }

  /**
   * Shutdown the application process manager.
   */
  public void shutdown ()
  {
    // Get the names of the processes. We have to do it this way since the 
    // unregisterProcess () will change the structure of the process map
    // and will cause an exception to be thrown.
    ArrayList <String> processNames = new ArrayList <String> ();

    for (String processName : this.processMap_.keySet ())
      processNames.add (processName);

    // Signal each of the application process to shutdown their operations. 
    // This will cause them to remove all the client instances.
    for (String processName : processNames)
    {
      this.lock_.lock ();
      Item item = null;

      try
      {
        // Get the next item in the process map.
        this.logger_.debug ("getting process " + processName + 
                            " from the process manager's listing");
        item = this.processMap_.get (processName);
      }
      finally
      {
        this.lock_.unlock ();
      }

      if (item != null)
      {
        try
        {
          // Shutdown the application process.
          this.logger_.debug ("signaling process " + processName + " to shutdown");
          item.appProcess_.shutdown ();

          // Wait for the process to exit. We don't have to remove it from the
          // process map because unregisterProcess () does that for us.
          this.logger_.debug ("waiting for process " + processName + " to exit");
          item.processHandler_.getProcess ().waitFor ();
          
          if (this.processMap_.containsKey (processName))
            this.logger_.error (processName + " failed to unregister itself");
        }
        catch (Exception ex)
        {
          this.logger_.error (ex.getMessage (), ex);
        }
      }
    }
  }
}
