// -*- Java -*-

//=============================================================================
/**
 * @file      JbiSource.java
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

package cuts.jbi.client;
import org.infospherics.jbi.client.InfoObject;
import org.infospherics.jbi.client.exception.*;
import org.exolab.castor.xml.MarshalException;
import org.exolab.castor.xml.ValidationException;
import java.io.IOException;

/**
 * Base class for all JBI events generated using CUTS. This object
 * of abstraction simplifies reading/writing MIOs.
 */
public abstract class JbiEvent <T> extends JbiEventBase
{
  /// Metadata for the JBI event.
  protected T metadata_ = null;

  /**
   * Initializing constructor.
   *
   * @param[in]       metadata        Source metadata.
   */
  public JbiEvent ()
  {

  }

  public JbiEvent (T metadata)
  {
    this.metadata_ = metadata;
  }

  /**
   * Initialize the event.
   *
   * @param[in]       metadata      XML header for the event.
   * @param[in]       payload       Payload associated with event.
   */
  public JbiEvent (T metadata, byte [] payload)
  {
    super (null, payload);
    this.metadata_ = metadata;
  }

  /**
   * Initializing constructor.
   *
   * @param[in]       mio         The source MIO.
   */
  public JbiEvent (InfoObject mio)
  {
    super (mio);
  }

  /**
   * Get the metadata for the payload in object format.
   *
   * @return      XML header in string format.
   */
  public abstract T getMetadata ()
    throws ObjectUnavailableException, TimeoutException,
           InstantiationException, IllegalAccessException,
           MarshalException, ValidationException;

  /**
    * Set the metadata for the object.
    *
    * @param[in]       metadata      The new metadata.
    */
  public void setMetadata (T metadata)
  {
    this.metadata_ = metadata;

    if (this.metadataString_ != null)
      this.metadataString_ = null;
  }

  /**
   * Set the string metadata for the event
   *
   * @param[in]       metadata      The new metadata
   */
  public void setMetadata (String metadata)
  {
    super.setMetadata (metadata);

    if (this.metadata_ != null)
      this.metadata_ = null;
  }

  /**
   * Set the info object for the event. This can either be assigned
   * when the event is constructed by a sequence, or assigned by the
   * the underlying framework when it receives a new event.
   */
  public void setInfoObject (InfoObject io)
  {
    // Set the info object.
    super.setInfoObject (io);

    // This will delete the existing metadata.
    if (this.metadata_ != null)
      this.metadata_ = null;
  }
}
