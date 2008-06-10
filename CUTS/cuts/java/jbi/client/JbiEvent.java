/**
 * @file      JbiSource.java
 *
 * $Id$
 *
 * @author      James H. Hill
 */

package cuts.java.jbi.client;

import org.infospherics.jbi.client.InfoObject;
import org.infospherics.jbi.client.exception.*;
import org.exolab.castor.xml.Unmarshaller;
import org.exolab.castor.xml.MarshalException;
import org.exolab.castor.xml.ValidationException;
import java.io.StringWriter;
import java.io.StringReader;
import java.util.Random;

/**
 * Base class for all JBI events generated using CUTS. This object
 * of abstraction simplifies reading/writing MIOs.
 */
public class JbiEvent <T>
{
  /// Metadata for the JBI event.
  private T metadata_ = null;

  /// Payload associated with the event.
  private byte [] payload_ = null;

  /// Information object for the event.
  private InfoObject infoObject_ = null;

  /// Random number generator that determines event payload size.
  private static Random random_ = new Random ();

  /// The class type for the event.
  private Class <T> classType_;

  /// String version of the metadata.
  private String metadataString_ = null;

  /**
   * Initializing constructor.
   *
   * @param[in]       metadata        Source metadata.
   */
  public JbiEvent (Class <T> classType)
  {
    this.classType_ = classType;
  }

  public JbiEvent (Class <T> classType, T metadata)
  {
      this.classType_ = classType;
      this.metadata_ = metadata;
  }

  /**
   * Initialize the event.
   *
   * @param       metadata      XML header for the event.
   * @param       payload       Payload associated with event.
   */
  public JbiEvent (Class <T> classType, T metadata, byte [] payload)
  {
    this.classType_ = classType;
    this.metadata_ = metadata;
    this.payload_ = payload;
  }

  /**
   * Get the metadata for the payload in object format.
   *
   * @return      XML header in string format.
   */
  public T getMetadata ()
    throws ObjectUnavailableException, TimeoutException,
           InstantiationException, IllegalAccessException
  {
    if (this.metadata_ == null)
      this.metadata_ = (T) this.classType_.newInstance ();

    return this.metadata_;
  }

  /**
    * Set the metadata for the object.
    *
    * @param[in]       metadata      The new metadata.
    */
  public void setMetadata (T metadata)
      throws ObjectUnavailableException, TimeoutException,
              MarshalException, ValidationException
  {
    this.metadata_ = metadata;
    this.metadataString_ = null;

    if (this.infoObject_ != null)
        this.infoObject_ = null;
  }

  public void setMetadata (String metadata)
  {
    this.metadataString_ = metadata;

    if (this.metadata_ != null)
      this.metadata_ = null;
  }

  /**
   * Get the metadata for the payload in string format. This
   * will be an XML string.
   */
  public String getMetadataString ()
    throws ObjectUnavailableException, TimeoutException,
           MarshalException, ValidationException
  {
      if (this.infoObject_ != null)
          return this.infoObject_.getMetadata ();
      else
          return this.metadataString_;
  }

  /**
   * Get the payload associated with the event.
   *
   * @return      The event's payload.
   */
  public byte [] getPayload ()
    throws ObjectUnavailableException, TimeoutException
  {
    if (this.infoObject_ != null)
      return this.infoObject_.getPayload ();
    else
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

    if (this.infoObject_ != null)
      this.infoObject_ = null;
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
   *
   */
  public InfoObject getInfoObject ()
  {
    return this.infoObject_;
  }
}
