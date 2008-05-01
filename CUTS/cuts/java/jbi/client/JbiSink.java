/**
 * @file      JbiSource.java
 * 
 * $Id$
 * 
 * @author      James H. Hill
 */

package cuts.java.jbi.client;
import org.infospherics.jbi.client.Connection;
import org.infospherics.jbi.client.InfoObject;
import org.infospherics.jbi.client.SubscriberSequence;
import org.infospherics.jbi.client.exception.*;
import cuts.java.jbi.client.JbiEvent;

/**
 * @class JbiSink
 */
public class JbiSink
{
  /// The connection for the source.
  private Connection jbiConn_ = null;

  /// Publisher sequence for the source.
  private SubscriberSequence jbiSink_ = null;
  
  /// The information object's type.
  private String typeName_;
  
  /// The information object's version.
  private String typeVersion_;
  
  /**
   * Initializining constructor. In order to create a source object
   * for a client, you have to provide it will a parent connection.
   */
  public JbiSink (Connection connection, String type, String version)
    throws PermissionDeniedException, UnsupportedVersionException
  {
    // Store the information about the publisher source.
    this.jbiConn_ = connection;
    this.typeName_ = type;
    this.typeVersion_ = version;
    
    // Create the publisher sequence for the source.
    this.jbiSink_ = 
      this.jbiConn_.createSubscriberSequence (
          this.typeName_, this.typeVersion_);
  }
  
  /**
   * Open the source. This method must be called before
   * the client can send any data using this source.
   */
  public void open ()
    throws PermissionDeniedException, SequenceStateException
  {
    this.jbiSink_.activateSequence ();    
  }
  
  /**
   * Close the information source object. This will release
   * its allocated resource. Once the object is closed, it
   * is no longer usable.
   */
  public void close ()
    throws PermissionDeniedException
  {
    this.jbiConn_.destroySequence (this.jbiSink_);
    this.jbiSink_ = null;
  }
}

