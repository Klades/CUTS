/**
 * @file 			JbiClient.java
 * 
 * $Id$
 * 
 * @author 			James H. Hill
 */

package cuts.java.jbi.client;
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
public abstract class JbiClient implements Runnable
{
	/// Single connection manager owned by the client.
	private static ConnectionManager jbiConnMgr = new ConnectionManager();

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
	
  /**
   * Collection of sinks for the client.
   */
  private ArrayList <JbiSink> sinks_ = new ArrayList <JbiSink> ();
  
  /**
   * Collection of sources for the client.
   */
  private ArrayList <JbiSource> sources_ = new ArrayList <JbiSource> ();
  
	public abstract void init ()
    throws PermissionDeniedException, UnsupportedVersionException;
	
	public abstract void activate ();
	
	public abstract void deactivate ();
	
	public abstract void fini ();
	
  public Connection getJbiConnection ()
  {
    return this.jbiConn;
  }
  
	/**
	 * 
	 */
	public void setServerAddress (String addr)
	{
		this.serverAddress = addr;
	}
	
	/**
	 * 
	 */
	public void setUserCredentials (String user, String passwd)
	{
		this.username = user;
		this.password = passwd;
	}
	
  /**
   * Get the timer for the client. This allows the subclass to 
   * add new periodic tasks to the timer. 
   */
  public Timer getTimer ()
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
						"connection:" + this.serverAddress,
						this.createConnectionDescriptor (this.serverAddress)); 

			this.jbiConn.authenticate (
					this.createUserCredentials(this.username, this.password));
			
			this.jbiConn.connect ();
			
			// Initialize the application. This is where the actual
			// client will create all its publisher/subscriber sequences.
			this.init ();

      // Activate all the sources in this client.
      for (JbiSource source : this.sources_)
        source.open ();
      
      // Activate all the sinks in this client.
      for (JbiSink sink : this.sinks_)
        sink.open ();
      
			// Signal the client to activate itself.
			this.activate ();
				
			// Wait for the client thread to be notified.
			this.wait ();

      // Signal the client to deactivate itself.
      this.timer_.cancel ();
			this.deactivate ();		

      // Activate all the sources in this client.
      for (JbiSource source : this.sources_)
        source.close ();
      
      // Activate all the sinks in this client.
      for (JbiSink sink : this.sinks_)
        sink.close ();
       
      // This is where the client will destroy all its publisher/
			// subscriber sequences.
			this.fini ();
		}
		catch (InterruptedException e)
		{
			e.printStackTrace ();
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
  			this.jbiConn.disconnect();			
  			this.jbiConnMgr.destroyConnection(this.jbiConn);
  
  			// Reset the connection just in case. :)
  			this.jbiConn = null;
      }
      catch (Exception e)
      {
        e.printStackTrace ();
      }
		}
	}
	
	private static String createUserCredentials(String username, String password) 
	{
		return new String("<?xml version=\"1.0\" encoding=\"UTF-8\"?>" +
				  	          "<credentials>" + 
				                "<username>"+ username + "</username>" +
				                "<password>"+ password +"</password>" +
				              "</credentials>");
	}
	
	private static String createConnectionDescriptor (String ipAddress)
	{
		return new String ("<?xml version=\"1.0\" encoding=\"UTF-8\"?>" +
						           "<ConnectionDescriptor>" + 
			                   "<PlatformDescriptor>" +
			                     "<platformIP>" + ipAddress + "</platformIP>" +
			                   "</PlatformDescriptor>" +
				               "</ConnectionDescriptor>");
	}
}

