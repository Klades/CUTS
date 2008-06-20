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

package cuts.java.jbi.deployment;

import org.omg.CosNaming.*;
import org.apache.log4j.Logger;
import java.util.*;

/**
 * @class ExecutionManagerImpl
 * 
 * Implementation of the ExecutionManager interface.
 */
public class ExecutionManagerImpl extends ExecutionManagerPOA
{
  /**
   * @class Item
   * 
   * Information about a domain application manager.
   */
  private class Item
  {
    private DomainApplicationManager dam_;

    private DomainApplicationManagerImpl damImpl_;

    public Item (DomainApplicationManager dam,
                 DomainApplicationManagerImpl damImpl)
    {
      this.dam_ = dam;
      this.damImpl_ = damImpl;
    }

    public DomainApplicationManager getDAM ()
    {
      return this.dam_;
    }

    public DomainApplicationManagerImpl getDAMImpl ()
    {
      return this.damImpl_;
    }
  }

  /// Collection of domain application managers.
  private final HashMap <String, Item>  managers_ = 
    new HashMap <String, Item> ();

  private final HashMap <NodeApplicationManager, NodeManager> namParentMap_ =
    new HashMap <NodeApplicationManager, NodeManager> ();

  /// ORB associated with this object.
  private org.omg.CORBA.ORB orb_ = null;

  /// Collection of resolved node managers.
  private HashMap <String, NodeManager> nodeMgrs_ = 
    new HashMap <String, NodeManager> ();

  private NamingContextExt ns_ = null;

  private final Logger logger_ = 
    Logger.getLogger ("ExecutionManager.ExecutionManagerImpl");

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
    this.logger_.debug ("preparing the deploy " + plan.UUID);

    DomainApplicationManager manager = null;

    try
    {
      // Create a new domain application manager for the plan.
      this.logger_.debug ("creating a new domain application manager");

      DomainApplicationManagerImpl damImpl = 
        new DomainApplicationManagerImpl (this.orb_, plan);

      // Contact each of the node managers in the deployment plan. Each
      // one is responsible for returns a NodeApplicationManager for this
      // deployment plan.
      
      this.logger_.debug ("resolving node manager(s) for this plan");

      for (ComponentInstanceDescriptor cid : plan.componentInstances)
        this.getNodeManager (cid.targetHost, "Default");
      
      for (Map.Entry <String, NodeManager> entry : this.nodeMgrs_.entrySet ())
      {
        // Invoke the preparePlan () method on each NodeManager.
        String hostName = entry.getKey ();
        NodeManager nodeManager = entry.getValue ();

        this.logger_.debug ("sending plan to node manager on " + hostName);
        NodeApplicationManager nam = nodeManager.preparePlan (plan);

        // Store the node application manager into the domain 
        // application manager object.
        if (nam != null)
        {
          this.logger_.debug ("saving node application manager from <" + 
                              hostName + ">");

          damImpl.insertManager (nam);

          // Store the child and parent in a mapping.
          this.namParentMap_.put (nam, nodeManager);
        }
      }

      // Activate the domain application manager.
      manager = damImpl._this (this.orb_);
      Item item = new Item (manager, damImpl);

      // Store the domain application manager.
      this.managers_.put (plan.UUID, item);
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

    this.logger_.debug (
      "destroying domain application manager for plan <" +
      plan.UUID + ">");

    if (!this.managers_.containsKey (plan.UUID))
      return;

    // Clear the applications from the domain application manager.
    Item item = this.managers_.get (plan.UUID);

    // Clear the domain application manager.
    this.logger_.debug ("getting the node application manager(s) from the " +
                        "domain application manager");

    DomainApplicationManagerImpl damImpl = item.getDAMImpl ();
    NodeApplicationManager [] nodeAppMgrs = null;

    if (damImpl != null)
      nodeAppMgrs = damImpl.getManagers ();
    else
      this.logger_.error ("this should NEVER happen");

    if (nodeAppMgrs != null)
    {
      // We need to contact node manager and have it destroy
      // the node application manager.
      this.logger_.debug ("destroying each of the application managers");

      for (NodeApplicationManager nam : nodeAppMgrs)
      {
        // Locate the parent of this node application manager.
        this.logger_.debug ("locating node manager that owns node application manager");
        NodeManager nodeManager = this.namParentMap_.get (nam);

        if (nodeManager != null)
        {
          // Destroy the node application manager.
          this.logger_.debug ("destroying node application manager");
          nodeManager.destroyManager (nam);

          // Remove the node application manager from the mapping.
          this.logger_.debug ("removing node appication manager object");        
          this.namParentMap_.remove (nam);
        }
      }
    }

    // We can clear sub-managers of this domain application.
    this.logger_.debug ("removing the submanager(s) and this manager");
    damImpl.clear ();
    this.managers_.remove (manager);
  }

  /**
   * Get the domain application managers owned by this execution
   * manager.
   */
  public DomainApplicationManager [] getManagers ()
  {
    return this.managers_.keySet ().
      toArray (new DomainApplicationManager [0]);
  }

  /**
   * Helper method for locating the appropriate node manager. If 
   * the node manager is not cached, then the execution manager 
   * will try to resolve its location using the name service.
   */
  private NodeManager getNodeManager (String hostName, String kindName)
    throws org.omg.CosNaming.NamingContextPackage.NotFound,
           org.omg.CosNaming.NamingContextPackage.InvalidName,
           org.omg.CosNaming.NamingContextPackage.CannotProceed
  {
    String keyName = hostName + "/" + kindName;
    NodeManager nodeManager = null;

    if (this.nodeMgrs_.containsKey (keyName))
    {
      nodeManager = this.nodeMgrs_.get (keyName);
    }
    else
    {
      // Break the hostname based on the '.' character.
      String bindingName = new String ();
      String [] nameParts = hostName.split ("\\.");

      if (nameParts.length > 0)
      {
        // Reverse the contents of the array.
        for (int left = 0, right = nameParts.length - 1;
             left < right;
             left++, right--)
        {
          String temp = nameParts [left];

          nameParts [left] = nameParts [right];
          nameParts [right] = temp;
        }

        // Construct the final binding name, for later usage.
        bindingName += nameParts [0];

        for (int i = 1; i < nameParts.length; ++i)
          bindingName += "/" + nameParts [i];
      }
      else
      {
        nameParts = new String [1];
        nameParts [0] = hostName;

        // Save the binding name for later usage.
        bindingName = hostName;
      }

      // There is a good chance the target context does not exist. So, we
      // need to try and ensure it exists.
      bindingName += "/NodeManager." + kindName;

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
