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

package cuts.generators.data;

/**
 * @interface DataGenerator
 * 
 * The interface that all data generators must implement. This will
 * provide a consistent look and fell to all data generators.
 */
public interface DataGenerator
{
  public Object getNext ();
}