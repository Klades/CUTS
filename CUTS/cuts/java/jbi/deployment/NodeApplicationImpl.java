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
import java.util.*;

/**
 * @class NodeApplicationImpl
 *
 * Implementation of the NodeApplication interface.
 */
public class NodeApplicationImpl
  extends NodeApplicationPOA
{
  /// The name of the process group for this application.
  private String processGroup_ = null;

  /// The CAPI connection manager for this application.
  private static ConnectionManager connManager_ = new ConnectionManager ();

  /// Collection of client's deployed in this node application.
  private Hashtable <String, JbiClient> jbiClients_ =
    new Hashtable <String, JbiClient> ();

  /// The location of the configuration. This can be a relative
  /// location, or an absolute location. In the case of an absolute
  /// location, the directory must be prefixed with file:
  private String deploymentPath_ = null;

  /**
   * Initializing constructor.
   *
   * @param       processGroup        Name of the process group.
   * @param       confiDirectory      Directory containing configurations.
   */
  public NodeApplicationImpl (String processGroup, String deploymentPath)
  {
    this.processGroup_ = processGroup;
    this.deploymentPath_ = deploymentPath;
  }

  /**
   * Get the process group name for this node application.
   *
   * @return        The name of the process group.
   */
  public String getProcessGroup ()
  {
    return this.processGroup_;
  }

  /**
   * Install the specified component instance. The name should be
   * standard Java format, i.e., scoped using periods (.).
   *
   * @param       instanceName        Name of the instance.
   */
  public void installComponent (String instanceName)
  {
    // Convert the name of the bean to its location on disk.
    String beanFile =
      this.deploymentPath_ + "/" + instanceName.replace ('.', '/') + ".qic";

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
   * Activate all the components in the node application. This will
   * invoke the run () method on each client.
   */
  public void activateComponents ()
  {
    for (Map.Entry <String, JbiClient> entry :
         this.jbiClients_.entrySet ())
    {
      entry.getValue ().run ();
    }
  }

  /**
   * Deactivate all the components in this node application. This
   * will force each component to go through its shutdown sequence.
   */
  public void deactivateComponents ()
  {
    for (Map.Entry <String, JbiClient> entry :
         this.jbiClients_.entrySet ())
    {
      entry.getValue ().shutdown ();
    }
  }

  /**
   * Remove the components from this node application. This will clear
   * the hash table, and perform any other cleanup operations.
   */
  public void removeComponents ()
  {
    this.jbiClients_.clear ();
  }
}
