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
  private final ArrayList <JbiClient> jbiClients_ =
      new ArrayList <JbiClient>();

  /// The connection manager shared by all clients.
  private static ConnectionManager connManager_ = new ConnectionManager();

  private final Logger logger_ = Logger.getLogger(ApplicationProcessImpl.class);

  private org.omg.CORBA.ORB orb_ = null;

  /// Name assigned to this application process.
  private String name_;

  public ApplicationProcessImpl(org.omg.CORBA.ORB orb,
                                String name)
  {
    this.orb_ = orb;
    this.name_ = name;
  }

  /**
   * Install a new client into this application process.
   */
  public void installClient(String instanceName)
  {
    try
    {
      // Convert the name of the bean to its location on disk.
      String beanFile = instanceName.replace('.', '/');
      beanFile += ".qic";

      // Load the factory for the specified bean.
      BeanFactory beanFactory = new FileSystemXmlApplicationContext(beanFile);

      // Load the JBI client using the factory.
      JbiClient jbiClient =
          (JbiClient)beanFactory.getBean(instanceName);

      // Initialize the client.
      jbiClient.initializeClient(instanceName, this.connManager_);

      // Save the client.
      this.jbiClients_.add(jbiClient);
    }
    catch (Exception e)
    {
      this.logger_.error("exception", e);
    }
  }

  /**
   * Get the name of this application process.
   */
  public String name()
  {
    return this.name_;
  }

  /**
   * Uninstall an existing client from the application process.
   */
  public void uninstallClient(String instanceName)
  {

  }

  /**
   * Start the application process. This will run each of its clients.
   */
  public void start()
  {
    // Shutdown each of the clients (we should deactivate each client, then
    // call the fini () method).
    for (JbiClient jbiClient : this.jbiClients_)
        jbiClient.run ();
  }

  public void stop()
  {
    // Shutdown each of the clients (we should deactivate each client, then
    // call the fini () method).
    for (JbiClient jbiClient : this.jbiClients_)
        jbiClient.shutdown ();
  }

  /**
   * Shutdown the application process. This will actually end the
   * ORB's event loop.
   */
  public void shutdown()
  {
    // Shutdown the ORB.
    this.stop ();
    this.orb_.shutdown(true);
  }
}
