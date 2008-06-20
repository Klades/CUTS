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

import java.util.*;

public class DomainApplicationImpl 
  extends DomainApplicationPOA
{
  private String groupName_ = null;

  private final HashMap <String, NodeApplication> subApps_ =
    new HashMap <String, NodeApplication> ();

  /**
   * Initializing constructor.
   * 
   * @param       groupName         Name of the domain.
   */
  public DomainApplicationImpl (String groupName)
  {
    this.groupName_ = groupName;
  }

  /**
   * Start the domain application. This will start all its sub-applications,
   * which are essentially NodeApplication objects.
   */
  public void start ()
  {
    // Start all the node applications.
    for (Map.Entry <String, NodeApplication> entry : this.subApps_.entrySet ())
      entry.getValue ().start ();
  }

  /**
   * Shutdown the domain application. This will shutdown all its sub-applications,
   * which are essentially NodeApplication objects.
   */
  public void shutdown ()
  {
    // Shutdown all the node applications.
    for (Map.Entry <String, NodeApplication> entry : this.subApps_.entrySet ())
      entry.getValue ().shutdown ();
  }

  /**
   * Get the name of this domain.
   * 
   * @return        Name of the domain.
   */
  public String groupName ()
  {
    return this.groupName_; 
  }

  /**
   * Remove all the sub-applications.
   */
  public void clear ()
  {
    this.subApps_.clear ();
  }

  /**
   * Insert an application into to domain.
   */
  public void joinDomain (NodeApplication nodeApp)
  {
    this.subApps_.put (nodeApp.groupName (), nodeApp);
  }

  /**
   * Insert a collection of applications into to domain.
   * 
   * @param       apps        Collection of node applications.
   */
  public void joinDomain (Application [] apps)
  {
    for (Application app : apps)
    {
      try
      {
        NodeApplication nodeApp = NodeApplicationHelper.narrow (app);
        this.joinDomain (nodeApp);
      }
      catch (Exception e)
      {
        e.printStackTrace ();
      }
    }
  }
}
