// -*- Java -*-

//=============================================================================
/**
 *  @file       PojoComponentServer.java
 *  
 *  $Id$
 *  
 *  @author     James H. Hill
 */
//=============================================================================

package cuts.quotas.pojo;
import org.springframework.beans.factory.ListableBeanFactory;
import org.springframework.context.support.FileSystemXmlApplicationContext;

/**
 * @class PojoComponentServer
 * 
 * Implementation of the component server for the Pojo. This
 * class also serves as the main entry point.
 */
public class PojoComponentServer 
{
  /**
   * Default constructor
   */
  public PojoComponentServer () 
  {
    
  }
  
  /**
   * Main entry point for the container. This is where all the
   * processing starts...
   * 
   * @param[in]       args        The command-line arguments.
   */
  public void runMain (String [] args)
  {
    try
    {
      // Parse the command-line arguments.
      if (this.parseArgs (args) != 0)
        return;
      
      // Register the shutdown thread with the runtime.
      Runtime.getRuntime ().addShutdownHook (new ShutdownThread (this));
      
      // Create a container for the specified descriptor file.
      ListableBeanFactory beanFactory = new FileSystemXmlApplicationContext (this.descriptorFile_);
      this.pojoContainer_ = new PojoContainer (beanFactory);
      
      // Install the component instances
      Component [] components =  this.pojoContainer_.installComponentInstances ();
      
      // Activate each of the returned components.
      for (Component c : components)
        c.activate ();
      
      // Wait for the user to exit the application.
      System.out.println ("Press Ctrl+C to exit...");
      synchronized (this) {
        this.wait ();
      }
      
      // Passivate all the components in the container.
      this.pojoContainer_.passivateAll ();
      
      // Destroy all the components in the container.
      this.pojoContainer_.removeAll ();
    }
    catch (InterruptedException ex)
    {
      ex.printStackTrace ();
    }
  }
  
  /**
   * Help method to parse the command-line arguments.
   * 
   * @param[in]       args        The command-line arguments
   */
  private int parseArgs (String [] args)
  {
    // Iterate over each command-line argument.    
    for (int i = 0; i < args.length; ++ i)
    {
      final String arg = args[i];

      if (arg.equals ("-descriptor"))
        this.descriptorFile_ = args[++ i];
    }
    
    // Validate the REQUIRED command-line arguments.
    if (this.descriptorFile_.length () == 0)
    {
      System.err.println ("missing descriptor file name");
      return -1;
    }
    
    return 0;
  }

 
  /////////////////////////////////////////////////////////////////////////////
  // private data
    
  private String descriptorFile_;
  
  private PojoContainer pojoContainer_;
  
  /////////////////////////////////////////////////////////////////////////////
  // entryPoint
  
  public static void main (String [] args) 
  {
    try
    {
      PojoComponentServer componentServer = new PojoComponentServer ();
      componentServer.runMain (args);
    }
    catch (Exception ex)
    {
      ex.printStackTrace ();
    }
  }
}

/**
 * @class ShutdownThread
 * 
 * Help thread to shutdown the component server.
 */
class ShutdownThread extends Thread
{
  public ShutdownThread (PojoComponentServer pojoServer)
  {
    this.pojoServer_ = pojoServer;
  }
  
  /**
   * Run the shutdown thread. This will notify all the threads
   * synchronized on the Pojo server to wake-up.
   */
  public void run ()
  {
    synchronized (this.pojoServer_) {
      this.pojoServer_.notifyAll ();
    }
  }
  
  private PojoComponentServer pojoServer_;
}