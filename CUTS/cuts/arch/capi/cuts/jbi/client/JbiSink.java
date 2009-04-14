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
import org.infospherics.jbi.client.ObjectAvailableCallback;
import org.infospherics.jbi.client.Connection;
import org.infospherics.jbi.client.InfoObject;
import org.infospherics.jbi.client.SubscriberSequence;
import org.infospherics.jbi.client.exception.*;
import java.io.StringReader;
import java.io.IOException;

/**
 * @class JbiSink
 */
public class JbiSink extends JbiPort
{
  /// Publisher sequence for the source.
  private SubscriberSequence jbiSink_ = null;

  /// The name of the predicate.
  private String predicateName_ = null;

  /// Predicate, if any, assocated with sink.
  private String predicateValue_ = null;

  /**
   * Initializing constructor.
   *
   * @param[in]     connection          The parent connection.
   */
  public JbiSink (Connection connection)
  {
    super (connection);
  }

  /**
   * Initializing constructor.
   *
   * @param[in]       connection        Target connection for source
   * @param[in]       type              Typename of the event for source
   * @param[in]       version           Version of the event for source
   */
  public JbiSink (Connection connection, String type, String version)
      throws PermissionDeniedException, UnsupportedVersionException,
             SequenceStateException
  {
    super (connection);
    this.create (type, version, false);
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

    if (this.jbiSink_ != null)
    {
      // First, make sure we destroy the existing sequence.
      this.close_i ();

      // Save the active state of the port.
      active = true;
    }

    // Create the publisher sequence for the source.
    this.jbiSink_ = this.jbiConn_.createSubscriberSequence (type, version);

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
    if (this.jbiSink_ != null)
      this.jbiSink_.activateSequence ();
  }

  /**
   * Close the port.
   */
  public void close ()
    throws PermissionDeniedException
  {
    if (this.jbiSink_ != null)
      this.close_i ();
  }

  /**
   * Implementation of the close () method.
   */
  protected void close_i ()
    throws PermissionDeniedException
  {
    this.jbiConn_.destroySequence (this.jbiSink_);
    this.jbiSink_ = null;
  }

  /**
   * Set the callback handler for the sink.
   *
   * @param[in]         callback          Callback handler
   */
  public void setCallback (ObjectAvailableCallback callback)
    throws UnrecognizedObjectTypeException, PermissionDeniedException,
           SequenceStateException
  {
    this.jbiSink_.setSequenceCallback (callback);
  }

  /**
   * Set the predicate for the sink. The predicate is a regular
   * XPath expression. The sink will handle formatting it correctly
   * before sending it to the server.
   *
   * @param           predicate       Predicate for the sink.
   */
  public void setPredicate (String predicateName, String predicateValue)
    throws InvalidPredicateException, PredicateLanguageException,
           PermissionDeniedException, SequenceStateException
  {
    // Create the XML string for setting the predicate.
    String xpathPredicate =
      this.createXpathPredicate (this.predicateName_, this.predicateValue_);

    // Make sure sequence is not active before setting the predicate.
    int state = this.jbiSink_.getSequenceState ();

    if (state == 1)
      this.jbiSink_.pauseSequence ();

    // Set the predicate on the sink.
    this.jbiSink_.setSequencePredicate (xpathPredicate);

    // Reactivate the sequence if necessary.
    if (state == 1)
      this.jbiSink_.resumeSequence ();

    // Save the name and value of the predicate.
    this.predicateName_ = predicateName;
    this.predicateValue_ = predicateValue;
  }

  /**
   * Determine if the sequence has a predicate defined.
   *
   * @retval        true        Predicate is defined.
   * @retval        false       Predicate is not defined.
   */
  public boolean hasPredicate ()
  {
    return this.predicateName_ != null;
  }

  /**
   * Get the assigned predicate. If there is no predicate, then the
   * return value will be null.
   *
   * @return          The predicate for the sink.
   */
  public String getPredicateValue ()
  {
    return this.predicateValue_;
  }

  /**
   * Get the name of the predicate. If the predicate does not exist,
   * then the name will be null.
   */
  public String getPredicateName ()
  {
    return this.predicateName_;
  }

  /**
   * Helper method for creating the XML document for setting the
   * the predicate on a sequence.
   *
   * @param           predicate
   */
  private static String createXpathPredicate (String name, String predicate)
  {
    return new String ("<predicate>" +
                         "<predicateName>" + name + "</predicateName>" +
                         "<predicateType>XPath</predicateType>" +
                         "<predicateInstance>" + predicate + "</predicateInstance>" +
                       "</predicate>");
  }
}

