// -*- JAVA -*-

package cuts.java.jbi.deployment;

import org.apache.log4j.Logger;
import java.util.HashMap;
import java.util.concurrent.locks.*;

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
    Process process_;

    ApplicationProcess appProcess_;
  }

  private final HashMap<String, Item> processMap_ =
    new HashMap<String, Item>();

  private final Logger logger_ = 
    Logger.getLogger(ApplicationProcessManagerImpl.class);

  private final Lock lock_ = new ReentrantLock();

  private final Condition processRegistered_ = this.lock_.newCondition();

  /**
   * Default constructor.
   */
  public ApplicationProcessManagerImpl()
  {

  }

  /**
   * Register a process with the manager.
   */
  public void registerProcess(ApplicationProcess process)
  {
    this.logger_.debug("registering process group [" +
                       process.name() + "]");

    // Store the process in the process map.
    Item item = new Item();
    item.appProcess_ = process;

    this.processMap_.put(process.name(), item);

    // Signal all processes that the application registered itself.
    this.processRegistered_.signal();
  }

  /**
   * Remove a process for the manager.
   */
  public void unregisterProcess(ApplicationProcess process)
  {
    String name = process.name();
    this.logger_.debug("unregistering process group [" + name + "]");

    // Remove the application process reference, but not the actual 
    // process. We need to eventually wait for the process to exit. Or,
    // we can assume the process exits.
    this.processMap_.remove(name);
  }

  /**
   * Get the process with the specified name.
   */
  public ApplicationProcess getProcess(String name)
  {
    ApplicationProcess process = null;

    Item item = this.processMap_.get(name);

    if (item != null)
      process = item.appProcess_;

    return process;
  }

  /**
   * Wait for the process to register itself with the manager.
   */
  public void waitForProcessRegistered()
    throws InterruptedException
  {
    this.processRegistered_.await();
  }

  /**
   * Store the actual process with its application process.
   */
  public void setProcess(String name, Process process)
  {
    Item item = this.processMap_.get(name);

    if (item != null)
    {
      item.process_ = process;
      this.processMap_.put(name, item);
    }
  }
}
