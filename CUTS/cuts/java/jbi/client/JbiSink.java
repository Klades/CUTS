/**
 * @file      JbiSource.java
 * 
 * $Id$
 * 
 * @author      James H. Hill
 */

package cuts.java.jbi.client;
import org.infospherics.jbi.client.Connection;
import org.infospherics.jbi.client.InfoObject;
import org.infospherics.jbi.client.SubscriberSequence;
import org.infospherics.jbi.client.exception.*;
import cuts.java.jbi.client.JbiEvent;

/**
 * @class JbiSink
 */
public class JbiSink
{
  /// The connection for the source.
  private Connection jbiConn_ = null;

  /// Publisher sequence for the source.
  private SubscriberSequence jbiSink_ = null;
  
  /// The information object's type.
  private String typeName_;
  
  /// The information object's version.
  private String typeVersion_;

  /// The name of the predicate.
  private String predicateName_ = null;
  
  /// Predicate, if any, assocated with sink.
  private String predicateValue_ = null;
  
  /**
   * Initializining constructor. In order to create a source object
   * for a client, you have to provide it will a parent connection.
   */
  public JbiSink (Connection connection, String type, String version)
    throws PermissionDeniedException, UnsupportedVersionException
  {
    // Store the information about the publisher source.
    this.jbiConn_ = connection;
    this.typeName_ = type;
    this.typeVersion_ = version;
    
    // Create the publisher sequence for the source.
    this.jbiSink_ = 
      this.jbiConn_.createSubscriberSequence (
          this.typeName_, this.typeVersion_);
  }
  
  /**
   * Open the source. This method must be called before
   * the client can send any data using this source.
   */
  public void open ()
    throws PermissionDeniedException, SequenceStateException
  {
    this.jbiSink_.activateSequence ();    
  }
  
  /**
   * Close the information source object. This will release
   * its allocated resource. Once the object is closed, it
   * is no longer usable.
   */
  public void close ()
    throws PermissionDeniedException
  {
    this.jbiConn_.destroySequence (this.jbiSink_);
    this.jbiSink_ = null;
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
    // Save the name and value of the predicate.
    this.predicateName_ = predicateName;
    this.predicateValue_ = predicateValue;
    
    // Create the XML string for setting the predicate.
    String xpathPredicate =
      this.createXpathPredicate (this.predicateName_, this.predicateValue_);
    
    // Set the predicate on the sink.
    this.jbiSink_.setSequencePredicate (xpathPredicate);
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

