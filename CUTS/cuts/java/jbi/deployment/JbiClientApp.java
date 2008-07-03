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
  private final ArrayList <String> beanNames_ =
      new ArrayList <String>();

  private final Logger logger_ =
    Logger.getLogger(JbiClientApp.class);

  private ApplicationProcessImpl processImpl_ = null;

  private org.omg.CORBA.ORB orb_ = null;

  private NodeApplicationCallback callback_ = null;

  /**
   * Default constructor.
   */
  public JbiClientApp()
  {

  }

  public void run (String[] args)
  {
    // Parse the command-line arguments.
    this.parseArgs (args);

    // Register the shutdown hook for the client. This will
    // ensure the client releases all it's resources.
    Runtime.getRuntime ().addShutdownHook (new JbiShutdownThread (this));

    // Create a new application process.
    this.processImpl_ = new ApplicationProcessImpl (this.orb_);

    // Load each of the clients (or beans).
    this.logger_.info ("loading " + this.beanNames_.size () + " client(s)");

    for (String beanName : this.beanNames_)
        this.processImpl_.installClient (beanName);

    ApplicationProcess process = null;

    if (this.callback_ != null)
    {
      // Activate the application process's servant.
      process = this.processImpl_._this (this.orb_);

      // Register this application with it's parent.
      this.callback_.registerProcess (process);
    }

    // Run all the default clients.
    this.processImpl_.start ();

    if (this.callback_ != null)
    {
      // Run the ORB's main event loop since the client was started
      // by a node application (i.e., the deployment framework);
      this.orb_.run ();

      // Unregister the application process with its parent.
      this.callback_.unregisterProcess(process);
    }
  }

  /**
   * Parse the command-line arguments. This method needs to be
   * enhanced to do more complex command-line argument parsing.
   *
   * @param[in]       args        The command-line arguments.
   */
  private void parseArgs(String[] args)
  {
    // Initialize the CORBA ORB.
    this.orb_ = org.omg.CORBA.ORB.init (args, null);

    try
    {
      // Resolve the node application's callback interface. This will
      // let us know how the client application was started.
      org.omg.CORBA.Object obj =
        this.orb_.resolve_initial_references ("NodeApplication");

      this.callback_ = NodeApplicationCallbackHelper.narrow (obj);
    } 
    catch (org.omg.CORBA.ORBPackage.InvalidName ex)
    {

    }

    // Get instances to be loaded from the via the command-line.
    for (String beanName : args)
        this.beanNames_.add (beanName);
  }

  /**
   * Shutdown the client application.
   */
  public void shutdownApp()
  {
    // Shutdown the application process (and its clients).
    this.processImpl_.stop ();
    
    // Shutdown the ORB, if necessary.
    if (this.callback_ != null)
      this.orb_.shutdown (true);
  }

  /**
   * Main entry point for the application.
   *
   * @param[in]     args        Command-line arguments.
   */
  public static void main(String[] args)
  {
    // Set up a simple configuration that logs on the console.
    BasicConfigurator.configure();

    // Get the ExecutionManager logger.
    Logger logger = Logger.getLogger(JbiClientApp.class);

    try
    {
      JbiClientApp jbiClientApp = new JbiClientApp();
      jbiClientApp.run(args);
    }
    catch (Exception e)
    {
      e.printStackTrace();
    }
  }
}
