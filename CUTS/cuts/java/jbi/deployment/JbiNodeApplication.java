// -*- java -*-

//=============================================================================
/**
 * @file          JbiNodeApplication.java
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

package cuts.java.jbi.deployment;

import cuts.java.jbi.*;
import org.apache.log4j.Logger;
import org.apache.log4j.BasicConfigurator;

/**
 * @class JbiNodeApplication
 *
 * Node application daemon that is responsible for hosting client
 * objects of a specific process group.
 */
public class JbiNodeApplication
  implements JbiShutdownInterface
{
  /// The parent ORB for the application.
  private org.omg.CORBA.ORB orb_ = null;

  /// The applications process group.
  private String processGroup_ = null;

  /// The base directory that contains the deployment configurations.
  private String configPath_ = ".";

  private String managerCallbackIOR_ = null;

  /// Reference to the node manager's callback interface.
  private NodeApplicationManagerCallback nmCallback_ = null;

  /// Reference to the RootPOA.
  private org.omg.PortableServer.POA poa_ = null;

  private NodeApplicationImpl naImpl_ = null;

  private NodeApplication naRef_ = null;

  private final Logger logger_ = Logger.getLogger ("NodeApplication");

  /**
   * Default constructor.
   */
  public JbiNodeApplication (org.omg.CORBA.ORB orb)
  {
    this.orb_ = orb;
  }

  /**
   * Run the node application's main loop. This will bootstrap the
   * node application, and run its main event loop.
   */
  public void run ()
    throws org.omg.CORBA.ORBPackage.InvalidName,
           org.omg.PortableServer.POAManagerPackage.AdapterInactive,
           org.omg.PortableServer.POAPackage.ServantNotActive,
           org.omg.PortableServer.POAPackage.WrongPolicy
  {
    // Get a reference to the RootPOA.
    this.poa_ =
      org.omg.PortableServer.POAHelper.narrow (
      this.orb_.resolve_initial_references ("RootPOA"));

    // Activate the RootPOA.
    this.logger_.debug ("activating the RootPOA");
    this.poa_.the_POAManager ().activate ();

    // Create a new NodeApplicationImpl, which is a server object.
    this.logger_.debug ("creating new node application server");
    this.naImpl_ = new NodeApplicationImpl (this.orb_,
                                            this.processGroup_,
                                            this.configPath_);

    this.logger_.debug ("activating the node application server");
    this.naRef_ = this.naImpl_._this (this.orb_);

    // Register the application with the callback.
    this.registerWithCallback ();

    // Run the ORB event loop.
    this.logger_.debug ("running the node application's main event loop");
    this.orb_.run ();
  }

  /**
   * Register tha node application object with the node application
   * manager's callback object.
   */
  private void registerWithCallback ()
    throws org.omg.CORBA.ORBPackage.InvalidName
  {
    // Get a reference to the node managers callback.
    this.logger_.debug (
      "resolving reference to ManagerCallback (" +
      this.managerCallbackIOR_ + ")");

    try
    {
      this.nmCallback_ =
        NodeApplicationManagerCallbackHelper.narrow (
        this.orb_.string_to_object (this.managerCallbackIOR_));
    }
    catch (Exception ex)
    {
      this.logger_.error (ex.getMessage (), ex);
    }

    // Register the node application with the node manager.
    this.logger_.debug ("register the node application with its manager");

    this.nmCallback_.registerApplication (
      ApplicationHelper.narrow (this.naRef_));
  }

  /**
   * Shutdown the application.
   */
  public void shutdownApp ()
  {
    // Unregister this node application with the node manager.
    this.logger_.debug ("unregistering application with callback manager");
    this.nmCallback_.unregisterApplication (
      NodeApplicationHelper.narrow (this.naRef_));

    // Destroy the POA.
    this.logger_.debug ("destroying the RootPOA");
    if (this.poa_ != null)
      this.poa_.destroy (true, true);

    // Shutdown the ORB, but wait for it to complete all operations.
    this.logger_.debug ("destroying the ORB");
    if (this.orb_ != null)
      this.orb_.shutdown (true);
  }

  /**
   * Parse the command line arguments.
   *
   * @param       args        The programs command-line arguments
   */
  public void parseArgs (String [] args)
    throws Exception
  {
    for (int i = 0; i < args.length; ++ i)
    {
      String arg = args [i];

      if (arg.equals ("-process-group"))
      {
        this.processGroup_ = args [++i];
      }
      else if (arg.equals ("-config-path"))
      {
        this.configPath_ = args [++i];
      }
      else if (arg.equals ("-callback-ior"))
      {
        this.managerCallbackIOR_ = args [++i];
      }
    }

    if (this.processGroup_ == null)
      throw new Exception ("missing argument: -process-group <name>");
    
    if (this.managerCallbackIOR_ == null)
      throw new Exception ("missing argument: -callback-ior <name>");
  }

  /////////////////////////////////////////////////////////////////////////////
  // static methods

  public static void main (String [] args)
  {
    // Set up a simple configuration that logs on the console.
    BasicConfigurator.configure ();

    // Get the ExecutionManager logger.
    Logger logger = Logger.getLogger ("NodeApplication");

    try
    {
      // Initialze the CORBA infrastructure.
      logger.debug ("initializing CORBA ORB");
      org.omg.CORBA.ORB orb = org.omg.CORBA.ORB.init (args, null);

      // Create a node appliction object.
      logger.debug ("creating new node application");
      JbiNodeApplication nodeApp = new JbiNodeApplication (orb);

      // Register the shutdown hook for the manager. This will
      // ensure the manager releases all it's resources.

      logger.debug ("registering shutdown hook for application");
      Runtime.getRuntime ().
        addShutdownHook (new JbiShutdownThread (nodeApp));

      // Parse the command line arguments, then run the application.
      logger.debug ("parsing command-line arguments");
      nodeApp.parseArgs (args);
      nodeApp.run ();
    }
    catch (Exception ex)
    {
      logger.error (ex.getMessage (), ex);
    }
  }
}
