// -*- java -*-

//=============================================================================
/**
 * @file          ExecutionManagerImpl.java
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

package CUTS.jbi.deployment;

import org.omg.CosNaming.*;
import org.apache.log4j.Logger;
import java.util.*;

/**
 * @class ExecutionManagerImpl
 *
 * Implementation of the ExecutionManager interface.
 */
public class ExecutionManagerImpl
  extends ExecutionManagerPOA
{
  /// Collection of domain application managers.
  private final HashMap <
    DomainApplicationManager, DomainApplicationManagerImpl> domainAppMgrs_ =
    new HashMap<DomainApplicationManager, DomainApplicationManagerImpl>();

  /// ORB associated with this object.
  private org.omg.CORBA.ORB orb_ = null;

  /// Collection of resolved node managers.
  private HashMap <String, NodeManager> nodeMgrs_ =
    new HashMap <String, NodeManager> ();

  private NamingContextExt ns_ = null;

  private final Logger logger_ =
    Logger.getLogger(ExecutionManagerImpl.class);

  /**
   * Initializing constructor.
   */
  public ExecutionManagerImpl (org.omg.CORBA.ORB orb)
  {
    this.orb_ = orb;
  }

  /**
   * Prepare the specified plan for deployment.
   */
  public DomainApplicationManager preparePlan (DeploymentPlan plan)
  {
    this.logger_.debug ("preparing plan " + plan.UUID + " for deployment");
    DomainApplicationManager manager = null;

    try
    {
      // Create a new domain application manager for the plan.
      this.logger_.debug ("creating domain application manager for plan " +
                          plan.UUID);

      // Create a new domain application manager and activate it.
      DomainApplicationManagerImpl damImpl =
        new DomainApplicationManagerImpl (this.orb_, plan);
      manager = damImpl._this (this.orb_);

      // Contact each of the node managers in the deployment plan. Each
      // one is responsible for returns a NodeApplicationManager for this
      // deployment plan.

      this.logger_.debug ("resolving node manager(s) for plan " + plan.UUID);

      for (ComponentInstanceDescriptor cid : plan.componentInstances)
        this.getNodeManager (cid.targetHost, "(default)");

      this.logger_.debug ("sending local plan to node manager(s) for plan " +
                          plan.UUID);

      for (Map.Entry <String, NodeManager> entry : this.nodeMgrs_.entrySet ())
      {
        // Invoke the preparePlan () method on each NodeManager.
        String alias = entry.getKey ();
        NodeManager nodeManager = entry.getValue ();

        NodeApplicationManager nam = nodeManager.preparePlan (plan);

        if (nam != null)
          damImpl.registerManager (nam, nodeManager);
      }

      // Store the domain application manager.
      this.domainAppMgrs_.put(manager, damImpl);
    }
    catch (Exception ex)
    {
      this.logger_.error (ex.getMessage (), ex);
    }
    finally
    {
      return manager;
    }
  }

  /**
   * Destroy the specified manager.
   */
  public void destroyManager (DomainApplicationManager manager)
  {
    DeploymentPlan plan = manager.getPlan ();

    this.logger_.debug ("destroying domain application manager for plan [" +
                        plan.UUID + "]");

    DomainApplicationManagerImpl damImpl = this.domainAppMgrs_.get(manager);

    if (damImpl == null)
      return;

    // Finish destroying the manager (and its resources).
    damImpl.destroy();

    // Remove the manager from the listing.
    this.logger_.debug ("removing domain application manger for plan [" +
                        plan.UUID + "]");

    this.domainAppMgrs_.remove(manager);
  }

  /**
   * Get the domain application managers owned by this execution
   * manager.
   */
  public DomainApplicationManager [] getManagers ()
  {
    return this.domainAppMgrs_.keySet().
      toArray (new DomainApplicationManager [0]);
  }

  /**
   * Helper method for locating the appropriate node manager. If
   * the node manager is not cached, then the execution manager
   * will try to resolve its location using the name service.
   */
  private NodeManager getNodeManager (String alias, String kindName)
    throws org.omg.CosNaming.NamingContextPackage.NotFound,
           org.omg.CosNaming.NamingContextPackage.InvalidName,
           org.omg.CosNaming.NamingContextPackage.CannotProceed
  {
    String keyName = alias + "." + kindName;
    NodeManager nodeManager = null;

    if (this.nodeMgrs_.containsKey (keyName))
    {
      nodeManager = this.nodeMgrs_.get (keyName);
    }
    else
    {
      // There is a good chance the target context does not exist. So, we
      // need to try and ensure it exists.
      String bindingName = "NodeManager/" + keyName;

      NameComponent [] name = this.ns_.to_name (bindingName);
      nodeManager = NodeManagerHelper.narrow (this.ns_.resolve (name));

      // Save the node manager.
      this.nodeMgrs_.put (keyName, nodeManager);
    }

    return nodeManager;
  }

  /**
   * Set the name context for the execution manager. It will use
   * this context when trying to resolve the node managers.
   */
  public void setNameContext (NamingContextExt nameContext)
  {
    this.ns_ = nameContext;
  }
}
