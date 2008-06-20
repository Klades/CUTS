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
import mil.af.rl.im.capi.client.impl.ConnectionManager;
import org.springframework.beans.factory.BeanFactory;
import org.springframework.context.support.FileSystemXmlApplicationContext;
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

  /// The name of the process group for this application.
  private String processGroup_ = null;

  /// The CAPI connection manager for this application.
  private static ConnectionManager connManager_ = null;

  /// Collection of client's deployed in this node application.
  private Hashtable <String, JbiClient> jbiClients_ =
    new Hashtable <String, JbiClient> ();

  /// The location of the configuration. This can be a relative
  /// location, or an absolute location. In the case of an absolute
  /// location, the directory must be prefixed with file:
  private String configPath_ = null;

  private final Logger logger_ = 
    Logger.getLogger ("NodeApplication.NodeApplicationImpl");

  /**
   * Initializing constructor.
   *
   * @param       processGroup        Name of the process group.
   * @param       confiDirectory      Directory containing configurations.
   */
  public NodeApplicationImpl (org.omg.CORBA.ORB orb,
                              String processGroup, 
                              String deploymentPath)
  {
    this.orb_ = orb;
    this.processGroup_ = processGroup;
    this.configPath_ = deploymentPath;
  }

  /**
   * Install the specified component instance. The name should be
   * standard Java format, i.e., scoped using periods (.).
   *
   * @param       instanceName        Name of the instance.
   */
  public void installInstance (String instanceName)
  {
    this.logger_.debug ("request to install instance " + instanceName);

    if (this.connManager_ == null)
      this.connManager_ = new ConnectionManager ();

    // Convert the name of the bean to its location on disk.
    String beanFile =
      this.configPath_ + "/" + instanceName.replace ('.', '/') + ".qic";

    // Load the factory for the specified bean.
    BeanFactory beanFactory = new FileSystemXmlApplicationContext (beanFile);

    // Load the JBI client using the factory.
    JbiClient jbiClient =
      (JbiClient) beanFactory.getBean (instanceName);

    // Initialize the client and invoke its run () loop.
    jbiClient.initializeClient (instanceName, this.connManager_);

    // Save the client object.
    this.jbiClients_.put (instanceName, jbiClient);
  }

  /**
   * Install the specified component instance. The name should be
   * standard Java format, i.e., scoped using periods (.).
   *
   * @param       instanceName        Name of the instance.
   */
  public void uninstallInstance (String instanceName)
  {
    if (this.jbiClients_.containsKey (instanceName))
    {
      // Locate the client and shut it down.
      JbiClient client = this.jbiClients_.get (instanceName);
      client.shutdown ();

      // Remove the client from the collection.
      this.jbiClients_.remove (instanceName);
    }
  }

  /**
   * Get the process group name for this node application.
   *
   * @return        The name of the process group.
   */
  public String groupName()
  {
    return this.processGroup_;
  }

  /**
   * Start the application.
   */
  public void start ()
  {
    this.logger_.debug ("starting the node application");

    for (Map.Entry <String, JbiClient> entry : this.jbiClients_.entrySet ())
      entry.getValue ().run ();
  }

  /**
   * Shutdown the node application. The shutdown process is comprised
   * of the following operations:
   * 
   * -# Shutdown all the client objects.
   * -# Remove all the client objects.
   * -# Stop the ORBs main event loop.
   */
  public void shutdown ()
  {
    this.logger_.debug ("shutting down the node application");

    // First, shutdown all the components we are hosting in this
    // node applcation.
    for (Map.Entry <String, JbiClient> entry : this.jbiClients_.entrySet ())
      entry.getValue ().shutdown ();

    // Clear the list of JBI clients.
    this.jbiClients_.clear ();

    // Now, we can shutdown our ORB. This will stop the main
    // event loop and allow the process to exit gracefully.
    this.orb_.shutdown (true);
  }
}
