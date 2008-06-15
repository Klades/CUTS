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

/**
 * @class JbiNodeManager
 *
 * Default implemenation of the NodeManager interface. This class also
 * serves as the main entry point for the node manager in the JBI deployment
 * framework.
 */
public class NodeManagerImpl
  extends NodeManagerPOA
{
  private org.omg.CORBA.ORB orb_ = null;

  /// Callback handle for the node manager. This is passed to the
  /// node application so it can keep the node manager up-to-date
  /// with its status.
  private NodeManagerCallbackImpl nmCallback_ = null;

  /**
   * Default constructor.
   */
  public NodeManagerImpl (org.omg.CORBA.ORB orb)
  {
    // Save the ORB.
    this.orb_ = orb;

    // Create a callback, which will be passed to the node application.
    NodeManagerCallbackImpl nmcImpl = new NodeManagerCallbackImpl (this.orb_);
  }

  /**
   * Install the specified component. This will take the use the
   * provided information to instantiate the specified instance
   * in the correct node application.
   *
   * @param         cid           Component instance description.
   */
  public void installComponent (ComponentInstanceDescriptor cid)
  {
    this.nmCallback_.installComponent (cid.collocationGroup,
                                       cid.instanceName);
  }

  /**
   * Activate all the component. This will invoke the corresponding
   * method in each node application.
   */
  public void activateComponents ( )
  {
    this.nmCallback_.activateComponents ();
  }

  /**
   * Deactivate all the components. This will invoke the corresponding
   * method in each node application.
   */
  public void deactivateComponents ( )
  {
    this.nmCallback_.deactivateComponents ();
  }

  /**
   * Remove all the components from the node manager. This will
   * invoke the corresponding method on each node application.
   */
  public void removeComponents ( )
  {
    this.nmCallback_.removeComponents ();
  }
}
