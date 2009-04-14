/**
 * @file       JbiClient.java
 *
 * $Id$
 *
 * @author       James H. Hill
 */

package cuts.jbi.client;
import mil.af.rl.im.capi.client.impl.ConnectionManager;
import org.infospherics.jbi.client.Connection;
import org.infospherics.jbi.client.exception.*;
import java.util.Timer;
import java.util.ArrayList;

/**
 * @class JbiClient
 *
 * Base class that all JbiClients in CUTS inherit. It defines the
 * required interface necessary for integrating with the CUTS testing
 * environment.
 */
public abstract class JbiClient
{
  /// Single connection manager owned by the client.
  private ConnectionManager jbiConnMgr;

  /// The default connection for the client.
  private Connection jbiConn = null;

  /// The timer for the client's periodic task.
  private Timer timer_ = new Timer ();

  /// Address of the server.
  private String serverAddress;

  /// Username for the client.
  private String username;

  /// Password for the client.
  private String password;

  /// The client has begun the shutdown process.
  private boolean shutdown_ = false;

  /// The instance name of the client.
  private String instanceName_ = null;

  /**
   * Collection of sinks for the client.
   */
  private ArrayList <JbiSink> sinks_ = new ArrayList <JbiSink> ();

  /**
   * Collection of sources for the client.
   */
  private ArrayList <JbiSource> sources_ = new ArrayList <JbiSource> ();

  protected abstract void jbi_init ()
    throws PermissionDeniedException, UnsupportedVersionException;

  protected abstract void jbi_activate ();

  protected abstract void jbi_deactivate ();

  protected abstract void jbi_fini ();

  /**
   * Get the contained JBI connection. This is accessible only to
   * the subclasses of the client.
   *
   * @return        The JBI connection for the client.
   */
  public Connection getJbiConnection ()
  {
    return this.jbiConn;
  }

    /**
     * Initialize the client. This is invoked by the underlying
     * framework to set the instance name of the client, and its
     * connection manager. Both of this values are accessible to
     * to subclass via the appropriate accessor methods.
     *
     * @param       instanceName       Instance name for the client.
     * @param       manager            Target JBI connection manager.
     */
    public void initializeClient (String instanceName,
                                  ConnectionManager manager)
    {
        this.instanceName_ = instanceName;
        this.jbiConnMgr = manager;
    }

    public String getInstanceName ()
    {
        return this.instanceName_;
    }

  /**
   * Set the server address for the client. This is the IP address
   * or hostname where the client will establish is connection.
   *
   * @param[in]       addr      Server address
   */
  public void setServerAddress (String addr)
  {
    this.serverAddress = addr;
  }

  /**
   * Set the username for the client. This will be used when the
   * client authenticates itself with the server.
   *
   * @param[in]       user      The new username.
   */
  public void setUsername (String user)
  {
    this.username = user;
  }

  /**
   * Set the password for the client. This will be used when the
   * client authenticates itself with the server.
   *
   * @param[in]       user      The new password.
   */
  public void setPassword (String passwd)
  {
    this.password = passwd;
  }

  /**
   * Get the timer for the client. This allows the subclass to
   * add new periodic tasks to the timer.
   */
  protected Timer getTimer ()
  {
    return this.timer_;
  }

  protected void registerInfoSequence (JbiSource source)
  {
    this.sources_.add (source);
  }

  protected void registerInfoSequence (JbiSink sink)
  {
    this.sinks_.add (sink);
  }

  /**
   * Main entry point for the JBI client. This will execute the
   * test sequence for the client.
   */
    public void run ()
    {
  try
      {
    // Create the default connection for the client. Before we
    // can connect, we have to authenticate the client with the
    // server.
    this.jbiConn =
        this.jbiConnMgr.createConnection (
                  "connection:" + this.getInstanceName (),
                  this.createConnectionDescriptor (this.serverAddress));

    this.jbiConn.authenticate (
             this.createUserCredentials(this.username, this.password));

    this.jbiConn.connect ();

    // Initialize the application. This is where the actual
    // client will create all its publisher/subscriber sequences.
    this.jbi_init ();

      // Activate all the sinks in this client.
      for (JbiSink sink : this.sinks_)
        sink.open ();

      // Activate all the sources in this client.
      for (JbiSource source : this.sources_)
        source.open ();

      // Signal the client to activate itself.
      this.jbi_activate ();
    }
    catch (Exception e)
    {
      e.printStackTrace ();
    }
  }

  /**
   * Shutdown the client. This will cause the client to go through
   * its deactivate
   */
  public void shutdown ()
  {
    // Make sure we are not already performing a shutdown.
    if (this.shutdown_)
      return;

    this.shutdown_ = true;

    try
    {
      // Signal the client to deactivate itself.
      this.jbi_deactivate ();

      // Deactivate all the sources in this client.
      for (JbiSource source : this.sources_)
        source.close ();

      // Deactivate all the sinks in this client.
      for (JbiSink sink : this.sinks_)
        sink.close ();

      // This is where the client will destroy all its publisher/
      // subscriber sequences.
      this.jbi_fini ();
    }
    catch (Exception e)
    {
      e.printStackTrace ();
    }
    finally
    {
      // Close the connection and destroy it.
      try
      {
    if (this.jbiConn != null)
        {
      this.jbiConn.disconnect();
      this.jbiConnMgr.destroyConnection (this.jbiConn);

      // Reset the connection just in case. :)
      this.jbiConn = null;
        }
      }
      catch (Exception e)
      {
        e.printStackTrace ();
      }
    }
  }

  /**
   * Helper method for generating the user credentials. Given the
   * \a username and \a password, it will return a valid XML document,
   * or string, that can be passed to the Apollo server for validation.
   *
   * @param         username          Username to validate
   * @param         password          Password associated with \a username
   * @return        XML descriptor of the user credentials
   */
  private static String createUserCredentials (String username, String password)
  {
      String userCredentials =
    new String ("<credentials>" +
          "<username>"+ username + "</username>" +
          "<password>"+ password +"</password>" +
          "</credentials>");

      return userCredentials;
  }

  /**
   * Helper methods to create a connection deescriptor. Given the
   * \a ipAddress of the server, this method will return a valid XML
   * document, or string, that can be used to create an Apollo
   * connection.
   *
   * @param         ipAddress         Ip address of the Apollo server.
   * @return        XML descriptor of the connection.
   */
  private static String createConnectionDescriptor (String ipAddress)
  {
      String connString =
    new String ("<ConnectionDescriptor>" +
          "<PlatformDescriptor>" +
          "<platformIP>" + ipAddress + "</platformIP>" +
          "</PlatformDescriptor>" +
          "</ConnectionDescriptor>");


      return connString;
  }
}
