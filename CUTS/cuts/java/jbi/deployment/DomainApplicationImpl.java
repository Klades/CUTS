// -*- java -*-

//=============================================================================
/**
 * @file        DomainApplicationImpl.java
 * 
 * $Id$
 * 
 * @author      James H. Hill
 */
//=============================================================================

package cuts.java.jbi.deployment;

import org.apache.log4j.Logger;
import java.util.*;

/**
 * @class DomainApplicationImpl
 * 
 * Implementation of the DomainApplication interface.
 */
public class DomainApplicationImpl 
  extends DomainApplicationPOA
{
  /**
   * Item type stored in the domain application. Each item contains the
   * node application, and it's parent, that has been registered with
   * the domain application.
   */
  private class Item
  {
    private NodeApplication app_;

    private NodeApplicationManager manager_;
    
    public Item(NodeApplication app, NodeApplicationManager manager)
    {
      this.app_ = app;
      this.manager_ = manager;
    }

    public NodeApplication getApplication()
    {
      return this.app_;
    }

    public NodeApplicationManager getManager()
    {
      return this.manager_;
    }
  }

  /// Collection of node applications in this domain.
  private final ArrayList <Item> nodeApps_ = new ArrayList <Item> ();

  private final Logger logger_ =
    Logger.getLogger(DomainApplicationImpl.class);

  /**
   * Initializing constructor.
   * 
   * @param       groupName         Name of the domain.
   */
  public DomainApplicationImpl ()
  {

  }

  /**
   * Start the domain application. This will start all its sub-applications,
   * which are essentially NodeApplication objects.
   */
  public void start ()
  {
    this.logger_.debug ("starting each of the node applications");

    // Start all the node applications.
    for (Item item : this.nodeApps_)
      item.getApplication ().start ();
  }

  /**
   * Start the domain application. This will start all its sub-applications,
   * which are essentially NodeApplication objects.
   */
  public void finishLaunch()
  {
    this.logger_.debug ("finish launching each of the node applications");

    // Start all the node applications.
    for (Item item : this.nodeApps_)
      item.getApplication ().finishLaunch ();
  }

  /**
   * Insert a node application into this domain application.
   */
  public void registerApplication (NodeApplication nodeApp, 
                                   NodeApplicationManager manager)
  {
    final Item item = new Item(nodeApp, manager);
    this.nodeApps_.add(item);
  }

  /**
   * Destroy the application. This will in-turn destroy all the 
   * sub-applications contained in the domain application.
   */
  public void destroy()
  {
    // Destroy all the sub-applications (i.e., each of the registered 
    // node applications) of this domain application.
    this.logger_.debug ("destroying all node applications");

    for (Item item : this.nodeApps_)
    {
      NodeApplicationManager manager = item.getManager ();
      manager.destroyApplication (item.getApplication ());
    }

    // Clear the collection of node applications.

    this.logger_.debug ("releasing references to all node applications");
    this.nodeApps_.clear ();
  }
}
