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
import java.util.Random;

/**
 * Base class for all JBI events generated using CUTS. This object
 * of abstraction simplifies reading/writing MIOs.
 */
public class JbiEvent
{
  /// XML header associated with the event.
  private String header_ = null;
  
  /// Payload associated with the event.
  private byte [] payload_ = null;
  
  /// Information object for the event.
  private InfoObject infoObject_ = null;
  
  private Random random_ = new Random ();
  
  /**
   * Default constructor.
   */
  public JbiEvent ()
  {
   
  }
  
  /**
   * Initialize the event.
   * 
   * @param       header        XML header for the event.
   * @param       payload       Payload associated with event.
   */
  public JbiEvent (String header, byte [] payload)
  {
    this.header_ = header;
    this.payload_ = payload;
    
    if (this.infoObject_ != null)
      this.infoObject_ = null;
  }
  
  /**
   * Get the XML header for the event.
   * 
   * @return      XML header in string format.
   */
  public String getHeader ()
    throws ObjectUnavailableException, TimeoutException
  {
    if (this.infoObject_ != null)
      return this.infoObject_.getMetadata ();
    else
      return this.header_;
  }
  
  /**
   * Set the XML header for the event.
   * 
   * @param       XML header in string format.
   */
  public void setHeader (String header)
    throws ObjectUnavailableException, TimeoutException
  {
    this.header_ = header;
    
    if (this.infoObject_ != null)
      this.infoObject_ = null;
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
   * 
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
