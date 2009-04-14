/**
 * @file       JbiSource.java
 *
 * $Id$
 *
 * @author       James H. Hill
 */

package cuts.jbi.client;
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
  /// The publisher sequence for the port.
  private PublisherSequence jbiSrc_ = null;

  /**
   * Initializing contructor. This will not set the type infomration
   * for the source. It must be set using the update () method.
   *
   * @param[in]       connection        Target connection for source
   */
  public JbiSource (Connection connection)
  {
    super (connection);
  }

  /**
   * Initializining constructor. In order to create a source object
   * for a client, you have to provide it will a parent connection.
   *
   * @param[in]       connection        Target connection for source
   * @param[in]       type              Typename of the event for source
   * @param[in]       version           Version of the event for source
   */
  public JbiSource (Connection connection, String type, String version)
      throws PermissionDeniedException, UnsupportedVersionException,
             SequenceStateException
  {
    super (connection);
    this.create (type, version, false);
  }

  /**
   * Publish data to the environment.
   *
   * @param       event         Event object to publish.
   */
  public void publishData (JbiEventBase event)
    throws UnsupportedVersionException, PermissionDeniedException,
           InvalidPayloadException, InvalidMetadataException,
           ObjectSizeException, VersionNumberException,
           PausedSequenceException, SequenceStateException,
           ObjectUnavailableException, TimeoutException,
           MarshalException, ValidationException, IOException,
           InstantiationException, IllegalAccessException
  {
    // Publish the event, which creates an MIO.
    InfoObject io = this.jbiConn_.createInfoObject (this.typeName_,
                                                    this.typeVersion_,
                                                    event.getPayload (),
                                                    event.getMetadataString ());

    // Store the information object in the event.
    event.setInfoObject (io);
  }

  /**
   * Create a new publisher sequence. This can also be used to update
   * the type/version of the sequence, i.e., dynamically change it at
   * runtime.
   */
  public void create (String type, String version)
    throws PermissionDeniedException, UnsupportedVersionException,
           SequenceStateException
  {
    this.create (type, version, true);
  }

  /**
   * Create a new publisher sequence. This can also be used to update
   * the type/version of the sequence, i.e., dynamically change it at
   * runtime.
   */
  public void create (String type, String version, boolean reactivate)
    throws PermissionDeniedException, UnsupportedVersionException,
           SequenceStateException
  {
    boolean active = false;

    if (this.jbiSrc_ != null)
    {
      // First, make sure we destroy the existing sequence.
      this.close_i ();

      // Save the active state of the port.
      active = true;
    }

    // Create the publisher sequence for the source.
    this.jbiSrc_ = this.jbiConn_.createPublisherSequence (type, version);

    // Save the type information about the source.
    this.typeName_ = type;
    this.typeVersion_ = version;

    // Make sure we reactivate the sequence, if necessary.
    if (active && reactivate)
      this.open ();
  }

  /**
   * Open the source. This method must be called before
   * the client can send any data using this source.
   */
  public void open ()
    throws PermissionDeniedException, SequenceStateException
  {
    if (this.jbiSrc_ != null)
      this.jbiSrc_.activateSequence ();
  }

  /**
   * Close the port.
   */
  public void close ()
    throws PermissionDeniedException
  {
    if (this.jbiSrc_ != null)
      this.close_i ();
  }

  /**
   * Implementation of the close () method.
   */
  protected void close_i ()
    throws PermissionDeniedException
  {
    this.jbiConn_.destroySequence (this.jbiSrc_);
    this.jbiSrc_ = null;
  }
}

