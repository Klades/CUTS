//  -*- java -*-

//=============================================================================
/**
 * @file          JbiNodeManager.java
 *
 * $Id$
 *
 * @author        James H. Hill
 */
 //=============================================================================

package cuts.java.jbi.deployment;

import cuts.java.jbi.deployment.NodeManagerImpl;
import cuts.java.jbi.JbiShutdownInterface;
import cuts.java.jbi.JbiShutdownThread;
import org.omg.CORBA.*;
import org.omg.PortableServer.*;
import org.omg.CosNaming.*;
import java.net.InetAddress;
import java.io.*;

/**
 * @class JbiNodeManager
 *
 * Default implemenation of the NodeManager interface. This class also
 * serves as the main entry point for the node manager in the JBI deployment
 * framework.
 */
public class JbiNodeManager
  implements JbiShutdownInterface
{
  /// The main ORB assigned to this server.
  private ORB orb_ = null;

  /// Reference to the RootPOA.
  private POA poa_ = null;

  /// Determine if we need to register object with name service.
  private boolean registerNameService_ = false;

  /// Reference to the naming service.
  private NamingContextExt nameService_ = null;

  /// The target filename for storing the IOR.
  private String iorFilename_ = null;

  /**
   * Initializing constructor.
   *
   * @param           orb         The parent ORB.
   */
  public JbiNodeManager (ORB orb)
  {
    this.orb_ = orb;
  }

  /**
   * Run the manager. This will instantiate a new NodeManagerImpl
   * object, which is a CORBA object, and activate it.
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
    this.poa_.the_POAManager ().activate ();

    // Create a new JbiNodeManager, which is a server object.
    org.omg.CORBA.Object obj =
      this.poa_.servant_to_reference (new NodeManagerImpl ());

    if (this.iorFilename_ != null)
      this.writeIORToFile (obj);

    if (this.registerNameService_)
      this.registerWithNameService (obj);

    // Run the ORB's event loop.
    System.out.println ("node manager is active...");
    this.orb_.run ();
  }

  /**
   * Handle the shutdown signal.
   */
  public void shutdownApp ()
  {
    // Unregister the object with the naming service.
    if (this.registerNameService_)
      this.unregisterWithNameService ();

    // Destroy the POA.
    if (this.poa_ != null)
      this.poa_.destroy (true, true);

    // Shutdown the ORB, but wait for it to complete all operations.
    if (this.orb_ != null)
      this.orb_.shutdown (true);
  }

  /**
   * Write the object's IOR to a file.
   *
   * @param       obj         Target object to write.
   */
  private void writeIORToFile (org.omg.CORBA.Object obj)
  {
    try
    {
      PrintWriter ps =
        new PrintWriter (new FileOutputStream (this.iorFilename_));

      ps.println (this.orb_.object_to_string (obj));
      ps.close ();
    }
    catch (Exception e)
    {
      e.printStackTrace ();
    }
  }

  /**
   * Parse the command-line options.
   *
   * @param       args          The commandline options.
   */
  public void parseArgs (String [] args)
  {
    for (int i = 0; i < args.length; ++ i)
    {
      String arg = args[i];

      if (arg.equals ("-register-with-ns"))
      {
        this.registerNameService_ = true;
      }
      else if (arg.equals ("-o"))
      {
        this.iorFilename_ = args[++ i];
      }
    }
  }

  /**
   * Register the object with the naming service
   *
   * @param       obj           Target object to register.
   */
  public void registerWithNameService (org.omg.CORBA.Object obj)
  {
    try
    {
      // Request a reference to the naming service.
      this.nameService_ =
        NamingContextExtHelper.narrow (
        this.orb_.resolve_initial_references ("NameService"));

      // Get the hostname running this manager.
      InetAddress addr = InetAddress.getLocalHost ();
      String hostname = addr.getHostName ();

      this.nameService_.bind (
        this.nameService_.to_name (hostname + ".NodeManager"), obj);
    }
    catch (Exception e)
    {
      e.printStackTrace ();
    }
  }

  public void unregisterWithNameService ( )
  {
    try
    {
      if (this.nameService_ != null)
      {
        // Get the hostname running this manager.
        InetAddress addr = InetAddress.getLocalHost ();
        String hostname = addr.getHostName ();

        // Unbind this node manager.
        this.nameService_.unbind (
          this.nameService_.to_name (hostname + ".NodeManager"));

        System.out.
          println ("successfully removed node manager from name service");
      }
    }
    catch (Exception e)
    {
      e.printStackTrace ();
    }
  }

  /////////////////////////////////////////////////////////////////////////////
  // global (static) functions

  /**
   * Main entry point for the node manager.
   *
   * @param[in]       args        Command-line arguments.
   */
  public static void main (String [] args)
  {
    ORB orb = null;

    try
    {
      // Initialize the CORBA ORB.
      orb = ORB.init (args, null);

      // Create a new node manager.
      JbiNodeManager manager = new JbiNodeManager (orb);

      // Register the shutdown hook for the manager. This will
      // ensure the manager releases all it's resources.
      Runtime.getRuntime ().
        addShutdownHook (new JbiShutdownThread (manager));

      // Parse the command line arguments then run the manager.
      manager.parseArgs (args);
      manager.run ();
    }
    catch (Exception e)
    {
      e.printStackTrace ();
    }
    finally
    {
      // Destroy the ORB.
      if (orb != null)
        orb.destroy ();
    }
  }

}
