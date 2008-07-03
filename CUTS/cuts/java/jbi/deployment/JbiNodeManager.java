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
import org.apache.log4j.Logger;
import org.apache.log4j.BasicConfigurator;
import java.net.*;
import java.io.*;
import java.util.*;

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
  private NamingContextExt rootContext_ = null;

  /// The target filename for storing the IOR.
  private String iorFilename_ = null;

  private String bindingName_ = new String ();

  private final Logger logger_ = Logger.getLogger(JbiNodeManager.class);

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
           org.omg.PortableServer.POAPackage.WrongPolicy,
           UnknownHostException
  {
    // Get a reference to the RootPOA.
    this.poa_ =
      org.omg.PortableServer.POAHelper.narrow (
      this.orb_.resolve_initial_references ("RootPOA"));

    // Get the hostname running this manager.
    InetAddress addr = InetAddress.getLocalHost ();
    String hostName = addr.getCanonicalHostName ();

    // Activate the RootPOA.
    this.poa_.the_POAManager ().activate ();

    // Create a new JbiNodeManager, which is a server object.
    org.omg.CORBA.Object obj =
      this.poa_.servant_to_reference (
      new NodeManagerImpl (this.orb_, hostName));

    if (this.iorFilename_ != null)
      this.writeIORToFile (obj);

    if (this.registerNameService_)
      this.registerWithNameService (obj, hostName);

    // Run the ORB's event loop.
    this.logger_.debug ("running the node manager's event loop");
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
    for (int i = 0; i < args.length; ++i)
    {
      String arg = args [i];

      if (arg.equals ("-register-with-ns"))
      {
        this.registerNameService_ = true;
      }
      else if (arg.equals ("-o"))
      {
        this.iorFilename_ = args [++i];
      }
    }
  }

  /**
   * Register the object with the naming service
   *
   * @param       obj           Target object to register.
   */
  private void registerWithNameService (org.omg.CORBA.Object obj, 
                                        String hostName)
  {
    try
    {
      // Request a reference to the naming service.
      this.rootContext_ =
        NamingContextExtHelper.narrow (
        this.orb_.resolve_initial_references ("NameService"));

      String [] nameParts = hostName.split ("\\.");

      if (nameParts.length > 0)
      {
        // Reverse the contents of the array.
        for (int left = 0, right = nameParts.length - 1;
             left < right;
             left ++, right --)
        {
          String temp = nameParts[left];

          nameParts[left] = nameParts[right];
          nameParts[right] = temp;
        }

        // Construct the final binding name, for later usage.
        this.bindingName_ += nameParts[0];

        for (int i = 1; i < nameParts.length; ++ i)
          this.bindingName_ += "/" + nameParts[i];
      }
      else
      {
        nameParts = new String [1];
        nameParts[0] = hostName;

        // Save the binding name for later usage.
        this.bindingName_ = hostName;
      }

      // There is a good chance the target context does not exist. So, we
      // need to try and ensure it exists.
      NamingContextExt currContext = this.rootContext_;
      StringBuffer nameBuffer = new StringBuffer ();

      for (String name : nameParts)
      {
        boolean duplicateName = false;
        nameBuffer.append (name);

        try
        {
          currContext =
            NamingContextExtHelper.narrow (
            currContext.bind_new_context (
            currContext.to_name (nameBuffer.toString ())));
        }
        catch (org.omg.CosNaming.NamingContextPackage.AlreadyBound e)
        {
          duplicateName = true;
        }

        if (!duplicateName)
          nameBuffer.setLength (0);
        else
          nameBuffer.append ("/");
      }

      // Bind the node manager under this context. We are going to use
      // the rebind () method instead of bind () to ensure the object
      // is registered with the name service.

      this.bindingName_ += "/NodeManager.(default)";

      this.logger_.debug ("registering node manager with name service");
      this.rootContext_.rebind (
        this.rootContext_.to_name (this.bindingName_), obj);
    }
    catch (Exception ex)
    {
      this.logger_.error (ex.getMessage (), ex);
    }
  }

  /**
   * Unregister the NodeManager with the naming service.
   */
  private void unregisterWithNameService ()
  {
    try
    {
      if (this.rootContext_ != null)
      {
        this.logger_.debug ("unregistering node manager from name service");

        this.rootContext_.unbind (
          this.rootContext_.to_name (this.bindingName_));
      }
    }
    catch (Exception ex)
    {
      this.logger_.error (ex.getMessage (), ex);
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

    // Set up a simple configuration that logs on the console.
    BasicConfigurator.configure ();

    // Get the ExecutionManager logger.
    Logger logger = Logger.getLogger(JbiNodeManager.class);

    try
    {
      // Initialize the CORBA ORB.
      logger.debug ("initializing the CORBA ORB");
      orb = ORB.init (args, null);

      // Create a new node manager.
      logger.debug ("creating a new node manager object");
      JbiNodeManager manager = new JbiNodeManager (orb);

      // Register the shutdown hook for the manager. This will
      // ensure the manager releases all it's resources.
      logger.debug ("registering application shutdown hook");

      Runtime.getRuntime ().
        addShutdownHook (new JbiShutdownThread (manager));

      // Parse the command line arguments then run the manager.
      logger.debug ("parsing command-line arguments");
      manager.parseArgs (args);
      manager.run ();
    }
    catch (Exception ex)
    {
      logger.error (ex.getMessage (), ex);
    }
    finally
    {
      // Destroy the ORB.
      if (orb != null)
        orb.destroy ();
    }
  }

}
