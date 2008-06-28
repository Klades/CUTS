/**
 * @file        JbiClientApp.java
 *
 * $Id$
 *
 * @author      James H. Hill
 */

package cuts.java.jbi.client;

import cuts.java.jbi.JbiShutdownThread;
import cuts.java.jbi.JbiShutdownInterface;
import mil.af.rl.im.capi.client.impl.ConnectionManager;
import org.springframework.beans.factory.BeanFactory;
import org.springframework.context.support.FileSystemXmlApplicationContext;
import org.apache.log4j.Logger;
import org.apache.log4j.BasicConfigurator;
import java.util.ArrayList;

/**
 * @class JbiClientApp
 */
public class JbiClientApp
  implements JbiShutdownInterface
{
  private static ConnectionManager connManager_ = new ConnectionManager ();

  // Collection of JBI client's managed by this process. 
  private final ArrayList <JbiClient> jbiClients_ = 
      new ArrayList <JbiClient> ();

    // Collection of bean names managed by this process.
  private final ArrayList <String> beanNames_ =
      new ArrayList <String> ();

    private final Logger logger_ = Logger.getLogger ("JbiClientApp");

    /**
     * Default constructor.
     */
  public JbiClientApp ()
  {

  }

  public void run (String [] args)
  {
    // Parse the command-line arguments.
    this.parseArgs (args);

    // Register the shutdown hook for the client. This will
    // ensure the client releases all it's resources.
    Runtime.getRuntime ().addShutdownHook (new JbiShutdownThread (this));

    // Load each of the clients (or beans).
    this.logger_.info ("loading " + this.beanNames_.size () + " client(s)");
    for (String beanName : this.beanNames_)
        this.loadBean (beanName);

    // Run each of the clients.
    this.logger_.info ("running " + this.jbiClients_.size () + " clients(s)");
    for (JbiClient jbiClient : this.jbiClients_)
        jbiClient.run ();
  }

  /**
   * Parse the command-line arguments. This method needs to be
   * enhanced to do more complex command-line argument parsing.
   *
   * @param[in]       args        The command-line arguments.
   */
  private void parseArgs (String [] args)
  {
      for (String beanName : args)
          this.beanNames_.add (beanName);
  }

  /**
   * Shutdown the client application.
   */
  public void shutdownApp ()
  {
      // Shutdown each of the clients (we should deactivate each client, then
      // call the fini () method).
      for (JbiClient jbiClient : this.jbiClients_)
          jbiClient.shutdown ();

      // Remove all the clients from our listing.
      this.jbiClients_.clear ();
  }

    /**
     * Deploy the beans specified in the command-line.
     */
    private void loadBean (String beanName)
    {
        try
            {
                // Convert the name of the bean to its location on disk.
                String beanFile = beanName.replace ('.', '/');
                beanFile += ".qic";
                
                // Load the factory for the specified bean.
                BeanFactory beanFactory = new FileSystemXmlApplicationContext (beanFile);
                
                // Load the JBI client using the factory.
                JbiClient jbiClient =
                    (JbiClient) beanFactory.getBean (beanName);
                
                // Initialize the client.
                jbiClient.initializeClient (beanName, this.connManager_);
                
                // Save the client.
                this.jbiClients_.add (jbiClient);
            }
        catch (Exception e)
            {
                this.logger_.error ("exception", e);
            }
   }

  /**
   * Main entry point for the application.
   *
   * @param[in]     args        Command-line arguments.
   */
  public static void main (String [] args)
  {
      // Set up a simple configuration that logs on the console.
      BasicConfigurator.configure ();
      
      // Get the ExecutionManager logger.
      Logger logger = Logger.getLogger ("JbiClientApp");

    try
    {
      JbiClientApp jbiClientApp = new JbiClientApp ();
      jbiClientApp.run (args);
    }
    catch (Exception e)
    {
      e.printStackTrace ();
    }
  }
}
