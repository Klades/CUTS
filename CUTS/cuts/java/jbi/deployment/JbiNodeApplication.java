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
  private String deploymentPath_ = null;

  /// Reference to the node manager's callback interface.
  private NodeManagerCallback nmCallback_ = null;

  /// Reference to the RootPOA.
  private org.omg.PortableServer.POA poa_ = null;

  private NodeApplicationImpl naImpl_ = null;

  private NodeApplication naRef_ = null;

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
    // Get a reference to the node managers callback.
    this.nmCallback_ =
      NodeManagerCallbackHelper.narrow (
      this.orb_.resolve_initial_references ("NodeManager"));

    // Get a reference to the RootPOA.
    this.poa_ =
      org.omg.PortableServer.POAHelper.narrow (
      this.orb_.resolve_initial_references ("RootPOA"));

    // Activate the RootPOA.
    this.poa_.the_POAManager ().activate ();

    // Create a new NodeApplicationImpl, which is a server object.
    this.naImpl_ =
      new NodeApplicationImpl (this.processGroup_, this.deploymentPath_);

    this.naRef_ =
      NodeApplicationHelper.narrow (
      this.poa_.servant_to_reference (this.naImpl_));

    // Register the node application with the node manager.
    this.nmCallback_.registerNodeApplication (this.naRef_);

    // Run the ORB event loop.
    this.orb_.run ();
  }

  /**
   * Shutdown the application.
   */
  public void shutdownApp ()
  {
    // Unregister this node application with the node manager.
    this.nmCallback_.unregisterNodeApplication (this.naRef_);

    // Destroy the POA.
    if (this.poa_ != null)
      this.poa_.destroy (true, true);

    // Shutdown the ORB, but wait for it to complete all operations.
    if (this.orb_ != null)
      this.orb_.shutdown (true);
  }

  /**
   * Parse the command line arguments.
   *
   * @param       args        The programs command-line arguments
   */
  public void parseArgs (String [] args)
  {
    this.processGroup_ = System.getProperty ("jbi.process.groupname");
    this.deploymentPath_ = System.getProperty ("jbi.deployment.path", ".");
  }

  /////////////////////////////////////////////////////////////////////////////
  // static methods

  public static void main (String [] args)
  {
    try
    {
      // Initialze the CORBA infrastructure.
      org.omg.CORBA.ORB orb = org.omg.CORBA.ORB.init (args, null);

      // Create a node appliction object.
      JbiNodeApplication nodeApp = new JbiNodeApplication (orb);

      // Register the shutdown hook for the manager. This will
      // ensure the manager releases all it's resources.
      Runtime.getRuntime ().
        addShutdownHook (new JbiShutdownThread (nodeApp));

      // Parse the command line arguments, then run the application.
      nodeApp.parseArgs (args);
      nodeApp.run ();
    }
    catch (Exception e)
    {
      e.printStackTrace ();
    }
  }
}
