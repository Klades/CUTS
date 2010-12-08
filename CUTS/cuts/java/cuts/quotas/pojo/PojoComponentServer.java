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
import cuts.datamodel.DataModel;
import cuts.datamodel.DataModelFile;

import java.util.TimerTask;
import java.util.Timer;

import org.springframework.beans.factory.ListableBeanFactory;
import org.springframework.context.support.FileSystemXmlApplicationContext;

import org.apache.log4j.Logger;

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
      Logger logger = Logger.getLogger (PojoComponentServer.class.getName ());
      
      // Parse the command-line arguments.
      if (this.parseArgs (args) != 0)
        return;
      
      // Register the shutdown thread with the runtime.
      logger.debug ("registering shutdown hook with VM");
      Thread shutdownThread = new ShutdownThread (this);
      Runtime.getRuntime ().addShutdownHook (shutdownThread);
      
      // Create a container for the specified descriptor file.
      //ListableBeanFactory beanFactory = new FileSystemXmlApplicationContext (this.descriptorFile_);
      //this.pojoContainer_ = new PojoContainer (beanFactory);

      // Load the data model for the server.
      logger.debug ("loading data model [file=" + this.dataModelFile_ + "]");
      DataModel dm = DataModelFile.readFile (this.dataModelFile_);
      System.err.println (dm);
      
      // Install the component instances
      Component [] components =  this.pojoContainer_.installComponentInstances ();
 
      // Set the data model for each installed component.
      for (Component c : components)
        c.setDataModel (dm);
      
      // Activate all the installed components.
      for (Component c : components)
        c.activate ();
      
      Timer timer = new Timer (false);
  
      if (this.testTimeout_ > 0)
      {
        long delay = this.testTimeout_ * 1000;
        timer.schedule (new TestTimer (this), delay);
      }
      
      // Wait for the user to exit the application.
      System.out.println ("Press Ctrl+C to exit...");
      
      synchronized (this) {
        this.wait ();
      }

      // Remove the shutdown hook.
      Runtime.getRuntime ().removeShutdownHook (shutdownThread);
      
      // Passivate then remove all components in the container.
      this.pojoContainer_.passivateAll ();
      this.pojoContainer_.removeAll ();
    }
    catch (Exception e)
    {
      e.printStackTrace ();
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
      else if (arg.equals ("-timeout"))
        this.testTimeout_ = Integer.parseInt (args[++ i]);
      else if (arg.equals ("-datamodel"))
        this.dataModelFile_ = args[++ i];
    }
    
    // Validate the REQUIRED command-line arguments.
    if (this.descriptorFile_.length () == 0)
    {
      System.err.println ("missing descriptor file name");
      return -1;
    }
    
    if (this.dataModelFile_.length () == 0)
    {
      System.err.println ("missing data model file");
      return -1;
    }
    
    return 0;
  }

 
  /////////////////////////////////////////////////////////////////////////////
  // private data
    
  private String descriptorFile_ = "";
  
  private int testTimeout_ = -1;
  
  private String dataModelFile_ = "";

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

class TestTimer extends TimerTask
{
  public TestTimer (PojoComponentServer pojoServer)
  {
    this.pojoServer_ = pojoServer;
  }
  
  public void run ()
  {
    System.err.println ("Testing time is complete; shutting down test...");

    synchronized (this.pojoServer_) {
      this.pojoServer_.notifyAll ();
    }   
  }

  private PojoComponentServer pojoServer_;
}
