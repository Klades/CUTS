// -*- java -*-

//=============================================================================
/**
 * @file          NodeManagerCallbackImpl.java
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

package cuts.java.jbi.deployment;

import java.util.*;
import java.util.concurrent.locks.*;

/**
 * @class NodeManagerCallbackImpl
 *
 * Implementation of the node manager callback interface.
 */
public class NodeManagerCallbackImpl
  extends NodeManagerCallbackPOA
{
  /**
   * @class NodeApplicationItem
   */
  private class NodeApplicationItem
  {
    /// Node application's process.
    public Process jbiNodeApp_;

    /// Reference to the node application's CORBA object.
    public NodeApplication nodeApp_;
  };

  /// Spawned node applications.
  private Hashtable <String, NodeApplicationItem> jbiNodeApps_ =
    new Hashtable <String, NodeApplicationItem> ();

  /// Mutex for the hashtables.
  private final ReentrantLock nodeAppLock_ = new ReentrantLock ();

  /// List of pending instances to deploy by process group.
  private Hashtable <String, HashSet <String> > pendingInstances_ =
    new Hashtable <String, HashSet <String> > ();

  /// Mutex for the hashtables.
  private final ReentrantLock pendingLock_ = new ReentrantLock ();

  /// The target ORB.
  private org.omg.CORBA.ORB orb_ = null;

  /// Directory that contains the deployment configurations.
  private String deploymentPath_ =
    System.getProperty ("jbi.deployment.path", ".");

  /**
   * Initializing constructor.
   *
   * @param       orb         The parent ORB.
   */
  public NodeManagerCallbackImpl (org.omg.CORBA.ORB orb)
  {
    this.orb_ = orb;
  }

  /**
   * Register a node application with the callback. This is
   * called when the node application if first created.
   *
   * @param         nodeApp         Handle to the node application.
   */
  public void registerNodeApplication (NodeApplication nodeApp)
  {
    String processGroup = nodeApp.getProcessGroup ();

    this.nodeAppLock_.lock ();

    try
    {
      if (this.jbiNodeApps_.containsKey (processGroup))
      {
        // Associate the node application with the located item.
        NodeApplicationItem naItem = this.jbiNodeApps_.get (processGroup);
        naItem.nodeApp_ = nodeApp;

        // Iterate over all the pending instances. We may have some that
        // need to be deployed within this node application.

        this.pendingLock_.lock ();

        try
        {
          Set <String> pendingInstances =
            this.pendingInstances_.get (processGroup);

          for (String pendingInstance : pendingInstances)
            nodeApp.installComponent (pendingInstance);

          // Delete all the items in the pending instances.
          this.pendingInstances_.remove (processGroup);
        }
        finally
        {
          this.pendingLock_.unlock ();
        }
      }
      else
      {
        // This case should never happen. If this happens, then this it means
        // somehow we did not create an item in the hashtable for this node
        // application's process!!

        System.err.println ("TODO : throw a CORBA exception");
      }
    }
    finally
    {
      this.nodeAppLock_.unlock ();
    }
  }

  /**
   * Unregister a node application with the callback. This is
   * called when the node application exits.
   *
   * @param         nodeApp         Handle to the node application.
   */
  public void unregisterNodeApplication (NodeApplication nodeApp)
  {
    this.nodeAppLock_.lock ();

    try
    {
      this.jbiNodeApps_.remove (nodeApp.getProcessGroup ());
    }
    finally
    {
      this.nodeAppLock_.unlock ();
    }
  }

  /**
   * Install the specified component instance in the specified process
   * group. If the process group does not exist, i.e., the node
   * application hasn't been spawned, it will place it in the pending
   * list. Once a node application for the process group has been
   * spawned, it will install the component.
   */
  public void installComponent (String processGroup, String instanceName)
  {
    this.nodeAppLock_.lock ();

    try
    {
      if (!this.jbiNodeApps_.containsKey (processGroup))
      {
        // Since the node application is not ready, we need to insert
        // the instance into the pending instance table.

        this.pendingLock_.lock ();

        try
        {
          HashSet <String> pendingInstances = null;

          if (!this.pendingInstances_.contains (processGroup))
          {
            pendingInstances = new HashSet <String> ();
            this.pendingInstances_.put (processGroup, pendingInstances);
          }
          else
          {
            pendingInstances = this.pendingInstances_.get (processGroup);
          }

          // Insert the instance in the pending instances.
          pendingInstances.add (instanceName);
        }
        finally
        {
          this.pendingLock_.unlock ();
        }

        // Now, we need to spawn a new node application. Convert the callback
        // object to a IOR. This will be passed to the spawned NodeApplication
        // so it can callback to the NodeManager.

        String iorString = this.orb_.object_to_string (this._this ());

        // 1. Get the current CLASSPATH.
        String classPath = System.getProperty ("java.class.path");

        // 2. Construct the command line for the node application.
        String commandLine =
          "java -Djbi.deployment.path=" + this.deploymentPath_ +
          " -Djbi.process.groupname=" + processGroup +
          " -cp " + classPath +
          " cuts.java.jbi.deployment.NodeApplication" +
          " -ORBInitRef NodeManager=" + iorString;

        System.err.println ("command line : " + commandLine);

        // 3. Spawn a new Java process, which will start a new node
        // application.
        try
        {
          NodeApplicationItem nodeAppItem = new NodeApplicationItem ();
          this.jbiNodeApps_.put (processGroup, nodeAppItem);

          nodeAppItem.jbiNodeApp_ = Runtime.getRuntime ().exec (commandLine);
        }
        catch (Exception e)
        {
          this.jbiNodeApps_.remove (processGroup);
        }
      }
      else
      {
        // Since we already have a node application for this process group,
        // we can just tell it to install the new component.

        NodeApplicationItem naItem = this.jbiNodeApps_.get (processGroup);
        naItem.nodeApp_.installComponent (instanceName);
      }
    }
    finally
    {
      this.nodeAppLock_.unlock ();
    }
  }

  /**
   * Activate all the components in this node manager. This means calling
   * the activate method on all the node applications.
   */
  public void activateComponents ()
  {
    for (Map.Entry <String, NodeApplicationItem> entry :
         this.jbiNodeApps_.entrySet ())
    {
      entry.getValue ().nodeApp_.activateComponents ();
    }
  }

  /**
   * Deactivate all the components in this node manager. This mean calling
   * the deactivate method on all the node applications.
   */
  public void deactivateComponents ()
  {
    for (Map.Entry <String, NodeApplicationItem> entry :
         this.jbiNodeApps_.entrySet ())
    {
      entry.getValue ().nodeApp_.deactivateComponents ();
    }
  }

  /**
   * Remove all the components. This means calling the remove method
   * on all the node applications contained in this manager.
   */
  public void removeComponents ()
  {
    for (Map.Entry <String, NodeApplicationItem> entry :
         this.jbiNodeApps_.entrySet ())
    {
      entry.getValue ().nodeApp_.removeComponents ();
    }
  }
}
