// -*- java -*-

//=============================================================================
/**
 * @file          NodeApplicationImpl.java
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

package cuts.java.jbi.deployment;

import cuts.java.jbi.client.*;
import org.apache.log4j.Logger;
import java.util.*;

/**
 * @class NodeApplicationImpl
 *
 * Implementation of the NodeApplication interface.
 */
public class NodeApplicationImpl
  extends NodeApplicationPOA
{
  /// The ORB for this node application.
  org.omg.CORBA.ORB orb_ = null;

  /// The location of the configuration. This can be a relative
  /// location, or an absolute location. In the case of an absolute
  /// location, the directory must be prefixed with file:
  private String configPath_ = ".";

  private final Logger logger_ =
    Logger.getLogger(NodeApplicationImpl.class);

  private NodeApplicationCallbackImpl callback_ = null;

  /**
   * Initializing constructor.
   *
   * @param       processGroup        Name of the process group.
   * @param       confiDirectory      Directory containing configurations.
   */
  public NodeApplicationImpl (org.omg.CORBA.ORB orb)
  {
    this.orb_ = orb;
    
    // Create a callback object and activate it. This is what we will
    // pass to each of the spawn application processes.
    this.callback_ = new NodeApplicationCallbackImpl();
    this.callback_._this(this.orb_);
  }

  public void finishLaunch()
  {
    // Do nothing!!
  }

  public void start()
  {
    // Start each of the application processes that we spawned.
  }

  public void installInstance(String groupName, String instanceName)
  {
    // Locate the process group. If it does not exist, then we need to 
    // spawn a new process.

    // Install the instance into the process group.
  }

  /**
   * Destroy the application. This should remove all the installed
   * instances and destroy all the spawned processes.
   */
  public void destroy()
  {

  }
}
