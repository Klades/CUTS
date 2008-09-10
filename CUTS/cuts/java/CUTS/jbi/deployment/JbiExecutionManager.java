// -*- java -*-

//=============================================================================
/**
 * @file          JbiExecutionManager.java
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

package CUTS.jbi.deployment;

import CUTS.jbi.JbiShutdownInterface;
import CUTS.jbi.JbiShutdownThread;
import org.omg.CORBA.*;
import org.omg.PortableServer.*;
import org.omg.CosNaming.*;
import org.apache.log4j.Logger;
import org.apache.log4j.BasicConfigurator;

/**
 * @class JbiExecutionManager
 *
 * Main server application for the execution manager.
 */
public class JbiExecutionManager
  implements JbiShutdownInterface
{
  /// The main ORB assigned to this server.
  private ORB orb_ = null;

  /// Reference to the RootPOA.
  private POA poa_ = null;

  /// Reference to the naming service.
  private NamingContextExt rootContext_ = null;

  /// The CORBA implementation for the execution manager.
  private ExecutionManagerImpl emImpl_ = null;

  /// The CORBA reference to the execution manager.
  private ExecutionManager em_;

  private final String bindingName_ = "ExecutionManager.JBI";

  private final Logger logger_ = Logger.getLogger(JbiExecutionManager.class);

  /**
   * Initializing constructor.
   */
  public JbiExecutionManager (org.omg.CORBA.ORB orb)
  {
    this.orb_ = orb;
  }

  /**
   * Parse the command-line arguments.
   */
  public void parseArgs (String [] args)
  {

  }

  /**
   * Run the execution manager.
   */
  public void run ()
    throws org.omg.CORBA.ORBPackage.InvalidName,
           org.omg.PortableServer.POAManagerPackage.AdapterInactive,
           org.omg.CosNaming.NamingContextPackage.InvalidName,
           org.omg.CosNaming.NamingContextPackage.NotFound,
           org.omg.CosNaming.NamingContextPackage.CannotProceed
  {
    // Get a reference to the RootPOA.
    this.logger_.debug ("getting a reference to the RootPOA");
    this.poa_ =
      org.omg.PortableServer.POAHelper.narrow (
      this.orb_.resolve_initial_references ("RootPOA"));

    // Activate the RootPOA.
    this.logger_.debug ("activating the RootPOA");
    this.poa_.the_POAManager ().activate ();

    // Instantiate a new execution manager and activate it.
    this.logger_.debug ("create new instance of execution manager object");
    this.emImpl_ = new ExecutionManagerImpl (this.orb_);
    this.em_ = this.emImpl_._this (this.orb_);

    // Register the execution manager with the name service.
    this.registerWithNameService (this.em_);
    this.emImpl_.setNameContext (this.rootContext_);

    // Run the main event loop.
    this.logger_.debug ("running the execution manager's event loop");
    this.orb_.run ();
  }

  /**
   * Shutdown the application.
   */
  public void shutdownApp ()
  {
    try
    {
      // Unregister the execution manager with the name service.
      this.logger_.debug ("unregistering execution manager with name service");
      this.unregisterWithNameService ();
    }
    catch (Exception ex)
    {
      this.logger_.error (ex.getMessage (), ex);
    }

    // Destroy the POA.
    if (this.poa_ != null)
      this.poa_.destroy (true, true);

    // Shutdown the ORB, but wait for it to complete all operations.
    if (this.orb_ != null)
      this.orb_.shutdown (true);
  }

  /**
   * Register the execution manager with the name service.
   */
  private void registerWithNameService (org.omg.CORBA.Object obj)
    throws org.omg.CORBA.ORBPackage.InvalidName,
           org.omg.CosNaming.NamingContextPackage.InvalidName,
           org.omg.CosNaming.NamingContextPackage.NotFound,
           org.omg.CosNaming.NamingContextPackage.CannotProceed
  {
    // Request a reference to the naming service.
    this.rootContext_ =
      NamingContextExtHelper.narrow (
      this.orb_.resolve_initial_references (
      System.getProperty ("ORBInitRef.NameService")));

    this.logger_.debug ("registering execution manager with name service");
    this.rootContext_.rebind (
      this.rootContext_.to_name (this.bindingName_), obj);
  }

  /**
   * Unregister the execution manager with the name service.
   */
  private void unregisterWithNameService ()
    throws org.omg.CosNaming.NamingContextPackage.InvalidName,
           org.omg.CosNaming.NamingContextPackage.NotFound,
           org.omg.CosNaming.NamingContextPackage.CannotProceed
  {
    if (this.rootContext_ != null)
    {
      this.rootContext_.unbind (
        this.rootContext_.to_name (this.bindingName_));
    }
  }

  /**
   * Main entry point for the application.
   */
  public static void main (String [] args)
  {
    org.omg.CORBA.ORB orb = null;

    // Set up a simple configuration that logs on the console.
    BasicConfigurator.configure ();

    // Get the ExecutionManager logger.
    Logger logger = Logger.getLogger(JbiExecutionManager.class);

    try
    {
      // Initialize the CORBA ORB.
      logger.debug ("initializing the CORBA ORB");
      orb = ORB.init (args, null);

      // Instantiate a new exeuction manager.
      logger.debug ("creating a new execution manager object");
      JbiExecutionManager executionManager = new JbiExecutionManager (orb);

      // Register a shutdown hook.
      logger.debug ("registering application shutdown hook");
      Runtime.getRuntime ().
        addShutdownHook (new JbiShutdownThread (executionManager));

      // Parse command-line arguments then run execution manager.
      logger.debug ("parsing command-line arguments");
      executionManager.parseArgs (args);
      executionManager.run ();
    }
    catch (Exception ex)
    {
      logger.error (ex.getMessage (), ex);
    }
  }
}
