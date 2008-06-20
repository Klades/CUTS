// -*- java -*-

//=============================================================================
/**
 * @file          NodeApplicationManagerCallbackImpl.java
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

package cuts.java.jbi.deployment;

import java.util.*;
import java.util.concurrent.locks.*;
import org.apache.log4j.Logger;

/**
 * @class NodeApplicationManagerCallbackImpl
 *
 * Implementation of the node manager callback interface.
 */
public class NodeApplicationManagerCallbackImpl
  extends NodeApplicationManagerCallbackPOA
{
  private NodeApplicationManagerImpl parent_ = null;

  private final Logger logger_ =
    Logger.getLogger ("NodeManager.NodeApplicationManagerCallback");

  /**
   * Initializing constructor.
   *
   * @param       orb         The parent ORB.
   */
  public NodeApplicationManagerCallbackImpl (NodeApplicationManagerImpl parent)
  {
    this.parent_ = parent;
  }

  /**
   * Register a node application with the callback. This is
   * called when the node application if first created.
   *
   * @param         nodeApp         Handle to the node application.
   */
  public void registerApplication (Application app)
  {
    try
    {
      this.logger_.debug ("received callback from " + app.groupName ());
 
      // Register the node application with its manager.
      NodeApplication nodeApp = NodeApplicationHelper.narrow (app);
      this.parent_.registerNodeApplication (nodeApp);
    }
    catch (Exception ex)
    {
      this.logger_.error (ex.getMessage (), ex);
    }
  }

  /**
   * Unregister a node application with the callback. This is
   * called when the node application exits.
   *
   * @param         app         Handle to the node application.
   */
  public void unregisterApplication (Application app)
  {

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

  }

  /**
   * Activate all the components in this node manager. This means calling
   * the activate method on all the node applications.
   */
  public void activateComponents ()
  {
    //for (Map.Entry <String, NodeApplicationItem> entry :
    //     this.jbiNodeApps_.entrySet ())
    //{
    //  entry.getValue ().nodeApp_.activateComponents ();
    //}
  }

  /**
   * Deactivate all the components in this node manager. This mean calling
   * the deactivate method on all the node applications.
   */
  public void deactivateComponents ()
  {
    //for (Map.Entry <String, NodeApplicationItem> entry :
    //     this.jbiNodeApps_.entrySet ())
    //{
    //  entry.getValue ().nodeApp_.deactivateComponents ();
    //}
  }

  /**
   * Remove all the components. This means calling the remove method
   * on all the node applications contained in this manager.
   */
  public void removeComponents ()
  {
    //for (Map.Entry <String, NodeApplicationItem> entry :
    //     this.jbiNodeApps_.entrySet ())
    //{
    //  entry.getValue ().nodeApp_.removeComponents ();
    //}
  }
}
