// -*- Java -*-

//=============================================================================
/**
 * @file      DataModel.java
 * 
 * $Id$
 * 
 * @author    James H. Hill
 */
//=============================================================================

package cuts.datamodel;
import java.util.HashMap;
import java.util.Map;

/**
 * @interface DataGenerator
 * 
 * The interface that all data generators must implement. This will
 * provide a consistent look and fell to all data generators.
 */
public class DataModel
{
  /**
   * Default constructor
   */
  public DataModel ()
  {
    
  }
  
  /**
   * Insert a new data generator into the data model.
   */
  public void put (String key, DataGenerator g)
  {
    this.generators_.put (key, g);
  }
  
  /**
   * Get the data generator for the specified key.
   */
  public DataGenerator get (String key)
  {
    return this.generators_.get (key);
  }
  
  /**
   * Remove data generator from the data model. The specified key
   * determines what data generator to remove.
   * 
   * @param[in]       key         Key for data generator to remove
   */
  public void remove (String key)
  {
    this.generators_.remove (key);
  }
  
  public int size ()
  {
    return this.generators_.size ();
  }
  
  /**
   * Reset the data model. This means reseting all the data generators
   * in this container object.
   */
  public void reset ()
  {
    for (DataGenerator g : this.generators_.values ())
      g.reset ();
  }
  
  public String toString ()
  {
    String str = "";
    
    for (Map.Entry <String, DataGenerator> e : this.generators_.entrySet ())
      str += "[" + e.getKey () + "]=" + e.getValue ().getClass ().getName () + "\n";
    
    return str;
  }

  /// Collection of data generators for this data model.
  private HashMap <String, DataGenerator> generators_ = new HashMap <String, DataGenerator> ();
}