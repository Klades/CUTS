// -*- java -*-

//=============================================================================
/**
 * @file        NodeApplicationManagerImpl
 * 
 * $Id$
 * 
 * @author      James H. Hill
 */
//=============================================================================

package cuts.java.jbi.deployment;

import java.util.*;
import java.io.*;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.*;
import java.util.concurrent.atomic.*;
import org.apache.log4j.Logger;

/**
 * @class NodeApplicationManagerImpl
 * 
 * Default implementation of the NodeApplicationManager interface. This
 * object is responsible for managing NodeApplication objects.
 */
public class NodeApplicationManagerImpl
  extends NodeApplicationManagerPOA
{
  class Item
  {
    public NodeApplication nodeApp_;

    public Process jbiNodeApp_;
  }

  /// ORB associate with this object.
  private org.omg.CORBA.ORB orb_ = null;

  /// Callback handle for the node manager. This is passed to the
  /// node application so it can keep the node manager up-to-date
  /// with its status.
  private final NodeApplicationManagerCallbackImpl callbackImpl_ =
    new NodeApplicationManagerCallbackImpl (this);

  private NodeApplicationManagerCallback callback_ = null;

  /// IOR for the callback object.
  private String callbackIOR_ = null;

  /// Collection of known node applications managed by this object.
  private HashMap <String, Item> jbiNodeApps_ =
    new HashMap <String, Item> ();

  private final Lock mapLock_ = new ReentrantLock ();

  private final 
    HashMap <String, ArrayList <String> > instanceInstallMap_ =
    new HashMap <String, ArrayList <String> > ();

  /// The location of the instance configurations.
  private String configPath_ = ".";

  private final Logger logger_ = 
    Logger.getLogger ("NodeManager.NodeApplicationManagerImpl");

  /**
   * Initailizing constructor.
   * 
   * @param           orb       Parent ORB for the object.
   */
  public NodeApplicationManagerImpl (org.omg.CORBA.ORB orb)
  {
    // Cache the ORB.
    this.orb_ = orb;

    // Stringfy the callback reference.
    this.callback_ = this.callbackImpl_._this (this.orb_);
    this.callbackIOR_ = this.orb_.object_to_string (this.callback_);
  }

  /**
   * Get the contained applications.
   */
  public Application [] getApplications ()
  {
    ArrayList <Application> nodeApps = new ArrayList<Application> (jbiNodeApps_.size ());

    for (Map.Entry <String, Item> entry :
         this.jbiNodeApps_.entrySet ())
    {
      Item item = entry.getValue ();
      nodeApps.add (NodeApplicationHelper.narrow (item.nodeApp_));
    }

    this.logger_.debug ("returning the node applications");

    return nodeApps.toArray (new NodeApplication [0]);
  }

  /**
   * Destroy the specified application.
   */
  public void destroyApplication (Application app)
  {
    try
    {
      // Extract the node application and get its group name.
      NodeApplication nodeApp = NodeApplicationHelper.narrow (app);
      String processGroup = nodeApp.groupName ();

      if (this.jbiNodeApps_.containsKey (processGroup))
      {
        // Shutdown the node application.
        nodeApp.shutdown ();

        // Wait for the node application process to exit.
        Item item = this.jbiNodeApps_.get (processGroup);
        item.jbiNodeApp_.waitFor ();

        // Remove the obsolete information.
        this.jbiNodeApps_.remove (processGroup);
      }
      else
      {
        // We don't own this application; we shouldn't do anything
        // to it.
      }
    }
    catch (Exception e)
    {
      e.printStackTrace ();
    }
  }

  /**
   * Register the a newly spawned node application with the node 
   * application manager. At this point, we can assume the node 
   * application does not need to be shutdown.
   */
  public void registerNodeApplication (NodeApplication app)
  {
    String groupName = app.groupName ();
    this.logger_.debug ("registering node application " + groupName);

    // Create and initialize a Item.
    this.mapLock_.lock ();

    try
    {
      // Get the existing item, or create a new one.
      Item item = this.jbiNodeApps_.get (groupName);

      if (item == null)
        item = new Item ();

      // Update the item and store it back into the map.
      item.nodeApp_ = app;
      this.jbiNodeApps_.put (groupName, item);
    }
    catch (Exception ex)
    {
      this.logger_.error (ex.getMessage (), ex);
    }
    finally
    {
      this.mapLock_.unlock ();
    }
  }

  /**
   * Unregister the an existing node application from the node 
   * application manager.
   */
  public void unregisterNodeApplication (NodeApplication app)
  {
    try
    {
      String groupName = app.groupName ();

      if (this.jbiNodeApps_.containsKey (groupName))
      {
        // Wait for the node application's process to exit.
        Item item = this.jbiNodeApps_.get (groupName);

        item.jbiNodeApp_.waitFor ();

        // Remove the node application's information.
        this.jbiNodeApps_.remove (groupName);
      }
    }
    catch (Exception ex)
    {
      this.logger_.error (ex.getMessage (), ex);
    }
  }

  /**
   * Create a new node application. This will spawn a new JbiNodeApplication
   * process for hosting JbiClient objects.
   */
  public void createNodeApplication (String processGroup)
    throws IOException
  {
    if (this.jbiNodeApps_.containsKey (processGroup))
      return;

    // Instantiate a new node application. This means create a new Java 
    // process for hosting component instances.

    // 1. Get the current CLASSPATH.
    String classPath = System.getProperty ("java.class.path");

    // 2. Construct the command line for the node application.
    String commandLine =
      "java -cp " + classPath +
      " -Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB" +
      " -Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton" +
      " cuts.java.jbi.deployment.JbiNodeApplication" +
      " -ORBInitRef NodeApplicationManager=" + this.callbackIOR_ +
      " -config-path " + this.configPath_ +
      " -process-group " + processGroup;

    // 3. Spawn a new Java process, which will start a new node 
    // application. We are going to wait here until the node 
    // application has registered itself with us.

    this.logger_.debug ("spawning node application for <" + 
                        processGroup + "> process group");

    Process jbiNodeApp = Runtime.getRuntime ().exec (commandLine);

    if (jbiNodeApp == null)
      return;

    // Locate the item for the node application.
    this.mapLock_.lock ();

    try
    {
      // Get the existing item, or create a new one.
      Item item = this.jbiNodeApps_.get (processGroup);

      if (item == null)
        item = new Item ();

      // Save the item back to the hashmap.
      this.logger_.debug ("updating the node application map with its process");
      item.jbiNodeApp_ = jbiNodeApp;
      this.jbiNodeApps_.put (processGroup, item);
    }
    catch (Exception ex)
    {
      this.logger_.error (ex.getMessage (), ex);
    }
    finally
    {
      this.mapLock_.unlock ();
    }
  }

  /**
   * Start the launch seqeunce for the node application manager. 
   */
  public Application [] startLaunch ()
  {
    for (Map.Entry <String, ArrayList <String> > entry :
         instanceInstallMap_.entrySet ())
    {
      Item item = this.jbiNodeApps_.get (entry.getKey ());

      if (item != null)
      {
        // Locate the node application object.
        NodeApplication nodeApp = item.nodeApp_;

        if (nodeApp != null)
        {
          for (String instanceName : entry.getValue ())
            nodeApp.installInstance (instanceName);        
        }
        else
        {
          // We need to throw a CORBA user exception here...
        }
      }
      else
      {
        // We should define a CORBA exception and throw it if 
        // we can't locate a NodeApplication.
      }

      // Release all the install map.
      this.instanceInstallMap_.clear ();
    }


    return this.getApplications ();
  }

  /**
   * Install the specified instance into one of the node application
   * managed by this manager.
   * 
   * @param           cid           Component instance descriptor
   */
  public void installInstance (String processGroup, String instanceName)
    throws Exception
  {
    ArrayList <String> instances = 
      this.instanceInstallMap_.get (processGroup);

    if (instances == null)
      instances = new ArrayList <String> ();

    this.logger_.debug ("placing <" + instanceName +
                        "> in <" + processGroup + "> set");

    // Update the listing for the process group.
    instances.add (instanceName);
    this.instanceInstallMap_.put (processGroup, instances);
  }

  /**
   * Clear the node application manager. This method releases all the
   * resource (i.e., the node applications) owned by this manager.
   */
  public void clear ()
  {
    for (Map.Entry <String, Item> entry : this.jbiNodeApps_.entrySet ())
    {
      // Get the node application interface from the item.
      Item item = entry.getValue ();

      if (item == null)
        continue;
      
      NodeApplication nodeApp = item.nodeApp_;
      Process jbiNodeApp = item.jbiNodeApp_;
      String groupName = entry.getKey ();

      if (nodeApp != null)
      {
        // Shutdown the node application.
        this.logger_.debug ("shutting down node application <" + groupName + ">");
        nodeApp.shutdown();
        

        try
        {
          // Wait for the node application process to exit.
          this.logger_.debug ("waiting for the node application <" + 
                              groupName + "> to exit");

          jbiNodeApp.waitFor();
        }
        catch (Exception ex)
        {
          this.logger_.error (ex.getMessage (), ex);
        }
      }
      else
      {
        // Forcefully, shutdown the process.
        this.logger_.warn ("<" + groupName + "> does not have a node " +
                           "application object associated with its process; " +
                           "forcefully destroying its process");

        try
        {
          jbiNodeApp.destroy ();
        }
        catch (Exception ex)
        {
          this.logger_.error (ex.getMessage (), ex);
        }
      }
    }

    // Remove all the items from the collection.
    this.logger_.debug ("removing all node application references");
    this.jbiNodeApps_.clear ();
  }
}
