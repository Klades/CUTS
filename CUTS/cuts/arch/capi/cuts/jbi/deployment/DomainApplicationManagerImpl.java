// -*- java -*-

//=============================================================================
/**
 * @file        DomainApplicationManagerImpl.java
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

package cuts.jbi.deployment;
import java.util.*;
import org.apache.log4j.Logger;

/**
 * @class DomainApplicationManagerImpl
 */
public class DomainApplicationManagerImpl
  extends DomainApplicationManagerPOA
{
  private class Item
  {
    private NodeApplicationManager nam_;

    private NodeManager nodeManager_;

    public Item(NodeApplicationManager nam,
                NodeManager nodeManager)
    {
      this.nam_ = nam;
      this.nodeManager_ = nodeManager;
    }

    public NodeApplicationManager getNodeApplicationManager()
    {
      return this.nam_;
    }

    public NodeManager getNodeManager()
    {
      return this.nodeManager_;
    }
  }

  /// The ORB associated with this object.
  private org.omg.CORBA.ORB orb_ = null;

  /// The deployment plan associated with this manager.
  private DeploymentPlan deploymentPlan_ = null;

  private final HashMap <DomainApplication, DomainApplicationImpl> domainApps_ =
    new HashMap <DomainApplication, DomainApplicationImpl> ();

  private final Logger logger_ =
    Logger.getLogger(DomainApplicationManagerImpl.class);

  private final ArrayList <Item> subManagers_ = new ArrayList <Item> ();

  /**
   * Initializing constructor.
   */
  public DomainApplicationManagerImpl (org.omg.CORBA.ORB orb,
                                       DeploymentPlan plan)
  {
    // Save the deployment plan for this manager.
    this.deploymentPlan_ = plan;
    this.orb_ = orb;
  }

  /**
   * Get the deployment plan for this domain application manager.
   */
  public DeploymentPlan getPlan ()
  {
    return this.deploymentPlan_;
  }

  /**
   * Destroy an application. This method makes the assumption the
   * application is already in a *shutdown* state.
   */
  public void destroyApplication (Application app)
  {
    try
    {
      this.logger_.debug("destroying an application");
      DomainApplication domainApp = DomainApplicationHelper.narrow (app);
      DomainApplicationImpl daImpl = this.domainApps_.get(domainApp);

      if (daImpl != null)
      {
        // Finish destroying the domain application.
        daImpl.destroy();

        // Remove the domain application from this manager.
        this.domainApps_.remove(domainApp);
      }
      else
      {
        this.logger_.error("application not owned by domain application manager");
      }
    }
    catch (Exception e)
    {
      e.printStackTrace ();
    }
  }

  /**
   * Start the launch sequence. This invokes the startLaunch ()
   * method on each of the sub-managers.
   */
  public Application startLaunch ()
  {
    // Create an activate a new domain application.
    DomainApplicationImpl domainAppImpl = new DomainApplicationImpl();
    DomainApplication domainApp = domainAppImpl._this(this.orb_);

    // Invoke the startLaunch () on each node application manager, and
    // install the returned NodeApplication in the domain application.

    for (Item item : this.subManagers_)
    {
      NodeApplicationManager nam = item.getNodeApplicationManager ();
      NodeApplication nodeApp = NodeApplicationHelper.narrow (nam.startLaunch ());

      // Register the application with the domain. We need to also
      // pass along the factory that created the application. This will
      // become useful when destroyApplication () is invoked.
      this.logger_.debug ("adding new node application to domain application");
      domainAppImpl.registerApplication (nodeApp, nam);
    }

    // Cache the domain application.
    this.domainApps_.put (domainApp, domainAppImpl);
    return domainApp;
  }

  /**
   * Insert a new node application manager into the domain application
   * manager. The node application manager is a sub-manager of the domain
   * application manager.
   */
  public void registerManager (NodeApplicationManager nam,
                               NodeManager nodeManager)
  {
    final Item item = new Item(nam, nodeManager);
    this.subManagers_.add(item);
  }

  /**
   * Destory the domain application manager. This will destroy all the
   * registered node application managers.
   */
  public void destroy()
  {
    // Destroy each of the node application managers.
    for (Item item : this.subManagers_)
    {
      NodeManager nodeManager = item.getNodeManager ();
      nodeManager.destroyManager (item.getNodeApplicationManager ());
    }

    // Clear the collection of registered node application managers.
    this.subManagers_.clear ();
  }
}
