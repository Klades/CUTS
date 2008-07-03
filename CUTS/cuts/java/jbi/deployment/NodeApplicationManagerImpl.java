// -*- java -*-

//=============================================================================
/**
 * @file        NodeApplicationManagerImpl
 * 
 * $Id$
 * 
 * @author      James H. Hill
 */
//=============================================================================

package cuts.java.jbi.deployment;

import java.util.*;
import java.io.*;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.*;
import java.util.concurrent.atomic.*;
import org.apache.log4j.Logger;

/**
 * @class NodeApplicationManagerImpl
 * 
 * Default implementation of the NodeApplicationManager interface. This
 * object is responsible for managing NodeApplication objects.
 */
public class NodeApplicationManagerImpl
  extends NodeApplicationManagerPOA
{
  /// ORB associate with this object.
  private org.omg.CORBA.ORB orb_ = null;

  /// Collection of known node applications managed by this object.
  private final HashMap <NodeApplication, NodeApplicationImpl> nodeApps_ =
    new HashMap <NodeApplication, NodeApplicationImpl>();

  /// The location of the instance configurations.
  private String configPath_ = ".";

  private final Logger logger_ =
    Logger.getLogger(NodeApplicationManagerImpl.class);

  /// Maps instances to be deployed to their process group.
  private final HashMap<String, ArrayList<String>> processMap_ =
    new HashMap<String, ArrayList<String>>();

  /**
   * Initailizing constructor.
   * 
   * @param           orb       Parent ORB for the object.
   */
  public NodeApplicationManagerImpl (org.omg.CORBA.ORB orb)
  {
    this.orb_ = orb;
  }

  /**
   * Destroy the specified application.
   */
  public void destroyApplication (Application app)
  {
    try
    {
      NodeApplication nodeApp = NodeApplicationHelper.narrow (app);
      NodeApplicationImpl nodeAppImpl = this.nodeApps_.get(nodeApp);

      if (nodeAppImpl != null)
      {
        // Destroy the node application.
        this.logger_.debug("destroying a existing node application");
        nodeAppImpl.destroy();

        // Remove the node application.
        this.logger_.debug("removing reference to the node application");
        this.nodeApps_.remove(nodeApp);
      }
    }
    catch (Exception e)
    {
      this.logger_.error ("exception", e);
    }
  }

  /**
   * Start the launch seqeunce for the node application manager. 
   */
  public Application startLaunch ()
  {
    // Create a new node application and activate it.
    this.logger_.debug("creating a new node application");
    NodeApplicationImpl nodeAppImpl = new NodeApplicationImpl (this.orb_);
    NodeApplication nodeApp = nodeAppImpl._this (this.orb_);
    
    // Install each of the instances into the node application. This will
    // in turn create process for the appropriate groups.
    for (Map.Entry <String, ArrayList <String>> entry :
         this.processMap_.entrySet ())
    {
      // Create the process group.
      String processGroup = entry.getKey ();
 
      // Install the instance into the process group.
      for (String instanceName : entry.getValue ())
        nodeAppImpl.installInstance (processGroup, instanceName);
    }

    // Clear the listing.
    this.processMap_.clear ();

    return nodeApp;
  }

  //
  // prepareInstance
  //
  public void prepareInstance (String processGroup, String instanceName)
  {
    // Get the listing of instances for the process group.
    ArrayList<String> instances = this.processMap_.get(processGroup);

    if (instances == null)
      instances = new ArrayList<String>();

    // Insert the instance and save the list back to the map.
    instances.add(instanceName);
    this.processMap_.put(processGroup, instances);
  }
}
