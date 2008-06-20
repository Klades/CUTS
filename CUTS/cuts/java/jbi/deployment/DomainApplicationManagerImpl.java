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

package cuts.java.jbi.deployment;

import java.util.*;
import org.apache.log4j.Logger;

/**
 * @class DomainApplicationManagerImpl
 */
public class DomainApplicationManagerImpl
  extends DomainApplicationManagerPOA
{
  class Item
  {
    public DomainApplication domainApp_;

    public DomainApplicationImpl domainAppImpl_;

    public Item (DomainApplication domainApp,
                 DomainApplicationImpl domainAppImpl)
    {
      this.domainApp_ = domainApp;
      this.domainAppImpl_ = domainAppImpl;
    }
  }

  private org.omg.CORBA.ORB orb_ = null;

  private DeploymentPlan deploymentPlan_ = null;

  private final ArrayList <NodeApplicationManager> subManagers_ =
    new ArrayList <NodeApplicationManager> ();

  private final HashMap <String, Item> domainApps_ =
    new HashMap <String, Item> ();

  private final DomainApplicationImpl defaultDomainApp_ =
    new DomainApplicationImpl ("domain.default");

  private final Logger logger_ =
    Logger.getLogger ("ExecutionManager.DomainApplicationManagerImpl");

  /**
   * Initializing constructor.
   */
  public DomainApplicationManagerImpl (org.omg.CORBA.ORB orb,
                                       DeploymentPlan plan)
  {
    // Save the deployment plan for this manager.
    this.deploymentPlan_ = plan;
    this.orb_ = orb;

    // Store the default domain application in the manager.
    Item item = new Item (this.defaultDomainApp_._this (this.orb_), 
                          defaultDomainApp_);

    this.domainApps_.put ("domain.default", item);
  }

  /**
   * Get the deployment plan for this domain application manager.
   */
  public DeploymentPlan getPlan ()
  {
    return this.deploymentPlan_;
  }

  /**
   * Get the applications in this manager. This returns a listing
   * of domain applications to the client.
   */
  public Application [] getApplications ()
  {
    return this.domainApps_.keySet().toArray (new DomainApplication[0]);
  }

  /**
   * Destroy an application. This method makes the assumption the 
   * application is already in a *shutdown* state. 
   */
  public void destroyApplication (Application app)
  {
    try
    {
      DomainApplication domainApp = DomainApplicationHelper.narrow (app);
      String appName = domainApp.groupName ();

      if (this.domainApps_.containsKey (appName))
      {
        // Get the domain application and shut it down.
        Item item = this.domainApps_.get (appName);

        // Remove all the sub-applications.
        item.domainAppImpl_.clear ();
        
        // Remove the application from the manager.
        this.domainApps_.remove (appName);
      }        
    }
    catch (Exception e)
    {
      e.printStackTrace (); 
    }
  }

  /**
   * Remove all the node application managers.
   */
  public void clear ()
  {
    this.subManagers_.clear ();
  }

  /**
   * Insert a node application manager into this domain application
   * manager.
   */
  public void insertManager (NodeApplicationManager manager)
  {
    // Save the manager to the listing.
    this.subManagers_.add (manager);

    try
    {
      // Get all the managers applications.
      this.logger_.debug ("getting applications form node application manager");
      Application [] apps = manager.getApplications ();

      // Insert applications into the default domain.
      if (apps == null)
      {
        this.logger_.debug ("adding application(s) to default domain application manager");
        this.defaultDomainApp_.joinDomain (apps);
      }
    }
    catch (Exception ex)
    {
      this.logger_.error (ex.getMessage (), ex);
    }
  }

  /**
   * Get the node application managers in this domain application
   * manager object.
   */
  public NodeApplicationManager [] getManagers()
  {
    return this.subManagers_.toArray (new NodeApplicationManager[0]);
  }

  /**
   * Start the launch sequence. This invokes the startLaunch () 
   * method on each of the sub-managers.
   */
  public Application [] startLaunch ()
  {
    for (NodeApplicationManager nam : this.subManagers_)
      nam.startLaunch ();

    return this.getApplications ();
  }
}
