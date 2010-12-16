// -*- Java -*-

//=============================================================================
/**
 * @file      DataGenerator.java
 * 
 * $Id$
 * 
 * @author    James H. Hill
 */
//=============================================================================

package cuts.datamodel;

/**
 * @interface DataGenerator
 * 
 * The interface that all data generators must implement. This will
 * provide a consistent look and fell to all data generators.
 */
public interface DataGenerator
{
  /**
   * Get the next value in the data generator.
   * 
   * @return        The next value.
   */
  public Object getNextValue ();
  
  /**
   * Reset the data generator to its initial state.
   */
  public void reset ();
  
  /**
   * Test if the data generator has more data. 
   */
  public boolean hasMoreData ();
}