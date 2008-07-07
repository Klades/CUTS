// -*- java -*-

package cuts.java.jbi.deployment;

import cuts.java.jbi.client.JbiClient;
import mil.af.rl.im.capi.client.impl.ConnectionManager;
import org.springframework.beans.factory.BeanFactory;
import org.springframework.context.support.FileSystemXmlApplicationContext;
import org.apache.log4j.Logger;
import java.util.ArrayList;

/**
 * @class ApplicationProcessImpl
 * 
 * Implementation of the ApplicationProcess interface.
 */
public class ApplicationProcessImpl
  extends ApplicationProcessPOA
{
  // Collection of JBI client's managed by this process. 
  private final ArrayList<JbiClient> jbiClients_ =
      new ArrayList<JbiClient> ();

  /// The connection manager shared by all clients.
  private static
    final ConnectionManager connManager_ = new ConnectionManager ();

  private final Logger logger_ =
    Logger.getLogger (ApplicationProcessImpl.class);

  private JbiClientApp parent_ = null;

  /**
   * Default constructor.
   */
  public ApplicationProcessImpl ()
  {

  }

  /**
   * Initializing constructor
   */
  public ApplicationProcessImpl (JbiClientApp parent)
  {
    this.parent_ = parent;
  }

  /**
   * Install a new client into this application process.
   */
  public boolean installClient (String instanceName)
  {
    try
    {
      this.logger_.debug ("installing " + instanceName);

      // Convert the name of the bean to its location on disk.
      String beanFile = instanceName.replace ('.', '/');
      beanFile += ".qic";

      // Load the factory for the specified bean.
      BeanFactory beanFactory = new FileSystemXmlApplicationContext (beanFile);

      // Load the JBI client using the factory.
      JbiClient jbiClient =
          (JbiClient) beanFactory.getBean (instanceName);

      // Initialize the client.
      this.logger_.debug ("initializing " + instanceName);
      jbiClient.initializeClient (instanceName, this.connManager_);

      // Save the client.
      this.jbiClients_.add (jbiClient);
      return true;
    }
    catch (Exception e)
    {
      this.logger_.error (e.getMessage (), e);
    }

    return false;
  }

  /**
   * Get the name of this application process.
   */
  public String name ()
  {
    return this.parent_.getName ();
  }

  /**
   * Uninstall an existing client from the application process.
   */
  public boolean uninstallClient (String instanceName)
  {
    return true;
  }

  /**
   * Start the application process. This will run each of its clients.
   */
  public void start ()
  {
    // Shutdown each of the clients (we should deactivate each client, then
    // call the fini () method).
    for (JbiClient jbiClient : this.jbiClients_)
      jbiClient.run ();
  }

  public void stop ()
  {
    // Shutdown each of the clients (we should deactivate each client, then
    // call the fini () method).
    this.logger_.debug ("shutting down " + this.jbiClients_.size () + " client(s)");

    for (JbiClient jbiClient : this.jbiClients_)
      jbiClient.shutdown ();
  }

  /**
   * Shutdown the application process. This will actually end the
   * ORB's event loop.
   */
  public void shutdown ()
  {
    this.parent_.shutdownApp ();
  }
}
