// -*- Java -*-

//=============================================================================
/**
 * @file        JbiAnyEvent.java
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
 * @class JbiAnyEvent
 */
public class JbiAnyEvent extends JbiEventBase
{
  /**
   * Default constructor.
   */
  public JbiAnyEvent ()
  {

  }

  /**
   * Initializing constructor.
   *
   * @param[in]       metadata        Metadata for the event
   * @param[in]       payload         Payload for the event
   */
  public JbiAnyEvent (String metadata, byte [] payload)
  {
    super (metadata, payload);
  }

  /**
   * Initializing constructor
   *
   * @param[in]       mio             Set the mio for the event.
   */
  public JbiAnyEvent (InfoObject mio)
  {
    super (mio);
  }

  /**
   * Get the metadata for the payload in string format. This
   * will be an XML string.
   */
  public String getMetadataString ()
    throws ObjectUnavailableException, TimeoutException,
           MarshalException, ValidationException, IOException
  {
    return this.metadataString_;
  }
}
