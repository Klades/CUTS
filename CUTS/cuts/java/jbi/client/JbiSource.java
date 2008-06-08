/**
 * @file       JbiSource.java
 *
 * $Id$
 *
 * @author       James H. Hill
 */

package cuts.java.jbi.client;
import org.infospherics.jbi.client.Connection;
import org.infospherics.jbi.client.InfoObject;
import org.infospherics.jbi.client.PublisherSequence;
import org.infospherics.jbi.client.exception.*;
import org.exolab.castor.xml.MarshalException;
import org.exolab.castor.xml.ValidationException;
import cuts.java.jbi.client.JbiEvent;

/**
 * @class JbiSource
 *
 * Base class that all JbiClients in CUTS inherit. It defines the
 * required interface necessary for integrating with the CUTS testing
 * environment.
 */
public class JbiSource
{
  /// The connection for the source.
  private Connection jbiConn_ = null;

  /// Publisher sequence for the source.
  private PublisherSequence jbiSrc_ = null;

  /// The information object's type.
  private String typeName_;

  /// The information object's version.
  private String typeVersion_;

  /**
   * Initializining constructor. In order to create a source object
   * for a client, you have to provide it will a parent connection.
   */
  public JbiSource (Connection connection, String type, String version)
    throws PermissionDeniedException, UnsupportedVersionException
  {
    // Store the information about the publisher source.
    this.jbiConn_ = connection;
    this.typeName_ = type;
    this.typeVersion_ = version;

    // Create the publisher sequence for the source.
    this.jbiSrc_ =
      this.jbiConn_.createPublisherSequence (
          this.typeName_, this.typeVersion_);
  }

  /**
   * Publish data to the environment.
   *
   * @param       event         Event object to publish.
   */
  public InfoObject publishData (JbiEvent <?> event)
    throws UnsupportedVersionException, PermissionDeniedException,
           InvalidPayloadException, InvalidMetadataException,
           ObjectSizeException, VersionNumberException,
           PausedSequenceException, SequenceStateException,
           ObjectUnavailableException, TimeoutException,
           MarshalException, ValidationException
  {
    // Publish the data, which creates the info object.
    InfoObject io =
      this.publishData (event.getMetadataString (), event.getPayload ());

    // Store the information object in the event.
    event.setInfoObject (io);
    return io;
  }

  /**
   * Publish data to the environment. This will return the published
   * information object for the client's reference.
   */
  public InfoObject publishData (String header, byte [] payload)
    throws UnsupportedVersionException, PermissionDeniedException,
           InvalidPayloadException, InvalidMetadataException,
           ObjectSizeException, VersionNumberException,
           PausedSequenceException, SequenceStateException
  {
    InfoObject io =
      this.jbiConn_.createInfoObject (
          this.typeName_, this.typeVersion_, payload, header);

    this.jbiSrc_.publishInfoObject (io);
    return io;
  }

  /**
   * Open the source. This method must be called before
   * the client can send any data using this source.
   */
  public void open ()
    throws PermissionDeniedException, SequenceStateException
  {
    this.jbiSrc_.activateSequence ();
  }

  /**
   * Close the information source object. This will release
   * its allocated resource. Once the object is closed, it
   * is no longer usable.
   */
  public void close ()
    throws PermissionDeniedException
  {
    this.jbiConn_.destroySequence (this.jbiSrc_);
    this.jbiSrc_ = null;
  }
}

