/**
 * @file        JbiClientApp.java
 *
 * $Id$
 *
 * @author      James H. Hill
 */

package cuts.java.jbi.deployment;

import cuts.java.jbi.JbiShutdownThread;
import cuts.java.jbi.JbiShutdownInterface;
import org.apache.log4j.Logger;
import org.apache.log4j.BasicConfigurator;
import java.util.ArrayList;

/**
 * @class JbiClientApp
 * 
 * Single process for hosting JbiClient objects.
 */
public class JbiClientApp
  implements JbiShutdownInterface
{
  // Collection of bean names managed by this process.
  private final ArrayList<String> beanNames_ =
      new ArrayList<String> ();

  private final Logger logger_ =
    Logger.getLogger (JbiClientApp.class);

  private ApplicationProcessImpl processImpl_ = null;

  private org.omg.CORBA.ORB orb_ = null;

  /// Reference to the RootPOA.
  private org.omg.PortableServer.POA poa_ = null;

  private ApplicationProcessManager processManager_ = null;

  private String name_ = null;

  /**
   * Default constructor.
   */
  public JbiClientApp ()
  {

  }

  /**
   * Run the application.
   */
  public void run (String [] args)
  {
    try
    {
      // Parse the command-line arguments.
      this.parseArgs (args);

      if (this.processManager_ != null)
      {
        // Get a reference to the RootPOA.
        this.logger_.debug ("getting a reference to RootPOA");

        this.poa_ =
          org.omg.PortableServer.POAHelper.narrow (
          this.orb_.resolve_initial_references ("RootPOA"));

        // Activate the RootPOA's manager.
        this.logger_.debug ("activating RootPOA's manager");
        this.poa_.the_POAManager ().activate ();
      }

      // Create a new application process.
      this.logger_.debug ("creating a new application process");
      this.processImpl_ = new ApplicationProcessImpl (this.orb_, this.name_);

      // Activate the application process's servant.
      ApplicationProcess process = null;
      
      if (this.processManager_ != null)
      {
        this.logger_.debug ("activating application process's remoting object");
        process = this.processImpl_._this (this.orb_);
      }

      // Load each of the clients (or beans).
      this.logger_.info ("loading " + this.beanNames_.size () + " client(s)");

      for (String beanName : this.beanNames_)
          this.processImpl_.installClient (beanName);

      if (this.processManager_ != null && process != null)
      {
        // Register this application with it's parent.
        this.logger_.debug ("registering application process with manager");
        this.processManager_.registerProcess (process);
      }

      // Run all the default clients.
      this.logger_.debug ("activating all the clients");
      this.processImpl_.start ();

      if (process != null)
      {
        // Run the ORB's main event loop since the client was started
        // by a node application (i.e., the deployment framework);
        this.logger_.debug ("running the ORB's main event loop");
        this.orb_.run ();

        // Unregister the application process with its parent.
        if (this.processManager_ != null)
          this.processManager_.unregisterProcess(process);
      }
    }
    catch (Exception e)
    {
      this.logger_.error (e.getMessage (), e);
    }
  }

  /**
   * Parse the command-line arguments. This method needs to be
   * enhanced to do more complex command-line argument parsing.
   *
   * @param[in]       args        The command-line arguments.
   */
  private void parseArgs (String [] args)
  {
    try
    {
      // Initialize the CORBA ORB.
      this.logger_.debug ("initializing CORBA ORB");
      this.orb_ = org.omg.CORBA.ORB.init (args, null);

      // Resolve the node application's callback interface. This will
      // let us know how the client application was started.
      org.omg.CORBA.Object obj =
        this.orb_.resolve_initial_references ("ProcessManager");

      this.processManager_ = ApplicationProcessManagerHelper.narrow (obj);
      this.logger_.debug ("client application spawned by deployment framework");
    } 
    catch (Exception ex)
    {
      this.logger_.error ("client application spawned manually", null);
    }

    // Parse the remaining arguments in the command-line. We are looking
    // for the name of this process, and the pre-loaded instances.
    for (int i = 0; i < args.length; ++ i)
    {
      String arg = args[i];

      if (arg.equals("-name"))
      {
        this.name_ = args[++i];
      }
      else if (arg.equals("-instances"))
      { 
        // Extract all the instances that are to be pre-loaded into 
        // this application process.
        String [] instances = args[++ i].split("\\p{Space}");

        for (String instance : instances) 
          this.beanNames_.add(instance);
      }
    }
  }

  /**
   * Shutdown the client application.
   */
  public void shutdownApp ()
  {
    // Shutdown the application process (and its clients).
    this.processImpl_.stop ();

    // Shutdown the ORB, if necessary.
    if (this.processManager_ != null)
      this.orb_.shutdown (true);
  }

  /**
   * Main entry point for the application.
   *
   * @param[in]     args        Command-line arguments.
   */
  public static void main (String [] args)
  {
    // Set up a simple configuration that logs on the console.
    BasicConfigurator.configure ();

    // Get the ExecutionManager logger.
    Logger logger = Logger.getLogger (JbiClientApp.class);

    try
    {
      logger.debug ("creating a new application");
      JbiClientApp jbiClientApp = new JbiClientApp ();

      // Register the shutdown hook for the client. This will
      // ensure the client releases all it's resources.
      logger.debug ("registering shutdown hook for application");
      Runtime.getRuntime ().addShutdownHook (new JbiShutdownThread (jbiClientApp));

      // Run the application.
      logger.debug ("running the application");
      jbiClientApp.run (args);
    }
    catch (Exception e)
    {
      logger.error ("exception", e);
    }
  }
}
