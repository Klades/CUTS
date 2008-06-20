//  -*- java -*-

//=============================================================================
/**
 * @file          NodeManagerImpl.java
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

package cuts.java.jbi.deployment;

import org.omg.PortableServer.*;
import java.util.*;
import org.apache.log4j.Logger;

/**
 * @class JbiNodeManager
 *
 * Default implemenation of the NodeManager interface. This class also
 * serves as the main entry point for the node manager in the JBI deployment
 * framework.
 */
public class NodeManagerImpl extends NodeManagerPOA
{
  /// The ORB assigned to the node manager.
  private org.omg.CORBA.ORB orb_ = null;

  /// Collection of node application managers.
  private HashMap <NodeApplicationManager,
                   NodeApplicationManagerImpl> managers_;

  private String hostName_ = null;

  private final Logger logger_ = Logger.getLogger ("NodeManager.NodeManagerImpl");

  /**
   * Default constructor.
   */
  public NodeManagerImpl (org.omg.CORBA.ORB orb, String hostName)
  {
    this.orb_ = orb;
    this.hostName_ = hostName;
  }

  /**
   * Prepare the deployment plan for deployment (or realization). This will
   * create a new node application manager for the plan, and return it
   * to the execution manager.
   */
  public NodeApplicationManager preparePlan (DeploymentPlan plan)
  {
    this.logger_.debug ("preparing plan " + plan.UUID + " for deployment");

    NodeApplicationManagerImpl namImpl =
      new NodeApplicationManagerImpl (this.orb_);

    // Activate the node application manager.
    this.logger_.debug ("activating a new node application manager");
    NodeApplicationManager manager = namImpl._this (this.orb_);

    // Iterate over the plan and instruct the application manager to 
    // allocate space for the appropriate number of node application. 
    // This will be based on the collocation group.

    for (ComponentInstanceDescriptor cid : plan.componentInstances)
    {
      try
      {
        if (cid.targetHost.equals (this.hostName_))
          namImpl.createNodeApplication (cid.processGroup);
      }
      catch (Exception ex)
      {
        // This exception handler shouldn't be here. We should be using
        // CORBA exception that will stop the deployment. So, this is 
        // just to keep Java from complaining so we can get the first
        // version of this framework completed.
        this.logger_.error (ex.getMessage (), ex);
      }
    }

    // Iterate over the plan and instruct the application manager to 
    // allocate space for the appropriate number of node application. 
    // This will be based on the collocation group.
    for (ComponentInstanceDescriptor cid : plan.componentInstances)
    {
      try
      {
        if (cid.targetHost.equals (this.hostName_))
          namImpl.installInstance (cid.processGroup, cid.instanceName);
      }
      catch (Exception ex)
      {
        // This exception handler shouldn't be here. We should be using
        // CORBA exception that will stop the deployment. So, this is 
        // just to keep Java from complaining so we can get the first
        // version of this framework completed.
        this.logger_.error (ex.getMessage (), ex);
      }
    }

    try
    {

    }
    catch (Exception ex)
    {
      // Save the node application manager.
      this.managers_.put (manager, namImpl);

      if (manager == null)
        this.logger_.error ("this should not happen!!");

    }
    finally
    {
      this.logger_.debug ("returning node application manager to execution manager");
      return manager;
    }
  }

  /**
   * Destroy the specified manager. This will force the manager to
   * release all its resources, which includes destoying all 
   * application and their instances.
   */
  public void destroyManager (NodeApplicationManager manager)
  {
    if (this.managers_.containsKey (manager))
    {
      // Get the actual implementation of the CORBA object.
      NodeApplicationManagerImpl namImpl = this.managers_.get (manager);

      // Explicitly destroy the node application manager. This
      // will force it to remove all its instances.
      namImpl.destroy ();

      // Remove the node application manager.
      this.managers_.remove (manager);
    }
  }
}
