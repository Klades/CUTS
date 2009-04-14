// -*- Java -*-

//=============================================================================
/**
 * @file      JbiPort.java
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

package cuts.jbi.client;
import org.infospherics.jbi.client.ObjectAvailableCallback;
import org.infospherics.jbi.client.Connection;
import org.infospherics.jbi.client.InfoObject;
import org.infospherics.jbi.client.SubscriberSequence;
import org.infospherics.jbi.client.exception.*;
import java.io.StringReader;
import java.io.IOException;

/**
 * Base class for all ports in the CUTS CAPI clients.
 */
public class JbiPort
{
  /**
   * Initialzing constructor
   *
   * @param[in]           jbiConn         Target connection for port
   * @param[in]           typeName        MIO typename for port
   * @param[in]           typeVersion     MIO version for port
   */
  public JbiPort (Connection jbiConn)
  {
    this.jbiConn_ = jbiConn;
  }

  /**
   * Get the connection for the port.
   *
   * @return      Connection object for the port.
   */
  public Connection getConnection ()
  {
    return this.jbiConn_;
  }

  /**
   * Get the MIO type name for the port.
   *
   * @return      MIO's type name for the port.
   */
  public String getTypeName ()
  {
    return this.typeName_;
  }

  /**
   * Get the version number of the MIO type.
   *
   * @return      The version number of the MIO type.
   */
  public String getVersion ()
  {
    return this.typeVersion_;
  }

  /// The connection for the source.
  protected Connection jbiConn_ = null;

  /// The information object's type.
  protected String typeName_;

  /// The information object's version.
  protected String typeVersion_;
}
