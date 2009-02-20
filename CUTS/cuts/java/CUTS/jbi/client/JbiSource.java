/**
 * @file       JbiSource.java
 *
 * $Id$
 *
 * @author       James H. Hill
 */

package CUTS.jbi.client;
import org.infospherics.jbi.client.Connection;
import org.infospherics.jbi.client.InfoObject;
import org.infospherics.jbi.client.PublisherSequence;
import org.infospherics.jbi.client.exception.*;
import org.exolab.castor.mapping.*;
import org.exolab.castor.mapping.xml.*;
import org.exolab.castor.xml.Marshaller;
import org.exolab.castor.xml.MarshalException;
import org.exolab.castor.xml.ValidationException;
import java.io.StringWriter;
import java.io.IOException;

/**
 * @class JbiSource
 *
 * Base class that all JbiClients in CUTS inherit. It defines the
 * required interface necessary for integrating with the CUTS testing
 * environment.
 */
public class JbiSource extends JbiPort
{
  /// Publisher sequence for the source.
  private PublisherSequence jbiSrc_ = null;

  /**
   * Initializining constructor. In order to create a source object
   * for a client, you have to provide it will a parent connection.
   */
  public JbiSource (Connection connection, String type, String version)
      throws PermissionDeniedException, UnsupportedVersionException
  {
    super (connection, type, version);

    // Create the publisher sequence for the source.
    this.jbiSrc_ =
      this.getConnection ().createPublisherSequence (this.getTypeName (),
                                                     this.getVersion ());
  }

  /**
   * Publish data to the environment.
   *
   * @param       event         Event object to publish.
   */
  public void publishData (JbiEvent <?> event)
    throws UnsupportedVersionException, PermissionDeniedException,
           InvalidPayloadException, InvalidMetadataException,
           ObjectSizeException, VersionNumberException,
           PausedSequenceException, SequenceStateException,
           ObjectUnavailableException, TimeoutException,
           MarshalException, ValidationException, IOException,
           InstantiationException, IllegalAccessException
  {
    // Publish the event, which creates an MIO.
    InfoObject io =
      this.getConnection ().createInfoObject (this.getTypeName (),
                                              this.getVersion (),
                                              event.getPayload (),
                                              event.getMetadataString ());

    // Store the information object in the event.
    event.setInfoObject (io);
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
    if (this.jbiSrc_ != null)
    {
        //this.jbiConn_.destroySequence (this.jbiSrc_);
        //this.jbiSrc_ = null;
    }
  }
}

