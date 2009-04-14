// -*- Java -*-

//=============================================================================
/**
 * @file        JbiEventBase.java
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
import java.util.Random;
import java.io.IOException;

/**
 * Base class for all JBI events generated using CUTS. This object
 * of abstraction simplifies reading/writing MIOs.
 */
public abstract class JbiEventBase
{
  /// String version of the metadata.
  protected String metadataString_ = null;

  /// Payload associated with the event.
  protected byte [] payload_ = null;

  /// Information object for the event.
  protected InfoObject infoObject_ = null;

  /// Random number generator that determines event payload size.
  private static Random random_ = new Random ();

  /**
   * Default constructor
   */
  public JbiEventBase ()
  {

  }

  /**
   * Initializing constructor.
   *
   * @param[in]       metadata        Metadata for the event
   * @param[in]       payload         Payload for the event
   */
  public JbiEventBase (String metadata, byte [] payload)
  {
    this.metadataString_ = metadata;
    this.payload_ = payload;
  }

  /**
   * Initializing constructor.
   *
   * @param[in]       mio         The source MIO.
   */
  public JbiEventBase (InfoObject mio)
  {
    this.infoObject_ = mio;
  }

  /**
   * Get the metadata for the payload in string format. This
   * will be an XML string.
   */
  public abstract String getMetadataString ()
    throws ObjectUnavailableException, TimeoutException,
           MarshalException, ValidationException, IOException;

  /**
   * Set the metadata for the info object.
   *
   * @param[in]     metadata        The new metadata
   */
  public void setMetadata (String metadata)
  {
    this.metadataString_ = metadata;
  }

  /**
   * Get the payload associated with the event.
   *
   * @return      The event's payload.
   */
  public byte [] getPayload ()
    throws ObjectUnavailableException, TimeoutException
  {
    return this.payload_;
  }

  /**
   * Set the payload associated with the event.
   *
   * @return      The event's payload.
   */
  public void setPayload (byte [] payload)
  {
    this.payload_ = payload;
  }

  /**
   * Set the payload associated with the event. This will allocate
   * a payload of the specified size.
   *
   * @param       payloadSize       Size of the payload.
   */
  public void setPayload (int payloadSize)
  {
    byte [] payload = new byte [payloadSize];
    this.setPayload (payload);
  }

  /**
   * Set the info object for the event. This can either be assigned
   * when the event is constructed by a sequence, or assigned by the
   * the underlying framework when it receives a new event.
   */
  public void setInfoObject (InfoObject io)
  {
    this.infoObject_ = io;
  }

  /**
   * Get the info object for the event. If one has not been set, then
   * the info object will be NULL.
   *
   * @return      The info object for the event.
   */
  public InfoObject getInfoObject ()
  {
    return this.infoObject_;
  }
}
