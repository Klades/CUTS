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
import org.exolab.castor.mapping.*;
import org.exolab.castor.mapping.xml.*;
import org.exolab.castor.xml.Marshaller;
import org.exolab.castor.xml.MarshalException;
import org.exolab.castor.xml.ValidationException;
import cuts.java.jbi.client.JbiEvent;
import java.io.StringWriter;
import java.io.IOException;

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

    private Mapping mapping_ = new Mapping ();

    private Marshaller marshaller_ = new Marshaller ();

  /**
   * Initializining constructor. In order to create a source object
   * for a client, you have to provide it will a parent connection.
   */
  public JbiSource (Connection connection, String type, String version)
      throws PermissionDeniedException, UnsupportedVersionException,
             MappingException, IOException
  {
    // Store the information about the publisher source.
    this.jbiConn_ = connection;
    this.typeName_ = type;
    this.typeVersion_ = version;

    // Construct the name of the mapping file. This is necessary
    // since Castor likes to construct *bad* tags. ;-)
    String mappingFile = type.replace ('.', '/');
    mappingFile += "/mapping.xml";

    // Load the mapping file for the type.
    this.mapping_.loadMapping (getClass ().getClassLoader ().getResource (mappingFile));

    // Initialize the mashaller.
    this.marshaller_.setMapping (this.mapping_);
    this.marshaller_.setValidation (false);

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
           MarshalException, ValidationException, IOException,
           InstantiationException, IllegalAccessException
  {
      String metadata;

      // Marshall the object to a XML string.
      if (event.getMetadataString () == null)
          {
              StringWriter writer = new StringWriter ();
              this.marshaller_.setWriter (writer);
              this.marshaller_.marshal (event.getMetadata ());
              metadata = writer.toString ();
          }
      else
          {
              metadata = event.getMetadataString ();
          }

      // Publish the event, which creates an MIO.
      InfoObject io = 
          this.publishData (metadata, event.getPayload ());

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

