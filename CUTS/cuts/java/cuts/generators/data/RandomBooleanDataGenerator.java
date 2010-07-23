// -*- Java -*-

//=============================================================================
/**
 * @file      RandomBooleanDataGenerator.java
 * 
 * $Id$
 * 
 * @author    James H. Hill
 */
//=============================================================================

package cuts.generators.data;
import java.util.Random;

/**
 * @class RandomBooleanDataGenerator
 * 
 * Data generator that generates random boolean values. This
 * class is simply a wrapper around the java.util.Random and
 * invokes its nextBoolean () method.
 */
public class RandomBooleanDataGenerator 
implements DataGenerator
{
  /**
   * Default constructor. This will seed the random generator based
   * on the system time.
   */
  public RandomBooleanDataGenerator ()
  {
    this.random_ = new Random (System.nanoTime ());
  }
  
  /**
   * Initializing constructor
   * 
   * @param[in]         seed        Value to seed generator.
   */
  public RandomBooleanDataGenerator (long seed)
  {
    this.random_ = new Random (seed);
  }
  
  /**
   * Get the next boolean value in the random sequence.
   */
  public Object getNext ()
  {
    return this.getNextBoolean ();
  }
  
  /**
   * Get the next boolean value in the random sequence.
   */
  public boolean getNextBoolean ()
  {
    return this.random_.nextBoolean ();
  }
  
  /**
   * Get the singleton version of the data generator.
   * 
   * @return      The data generator
   */
  static RandomBooleanDataGenerator getSingleton ()
  {
    return RandomBooleanDataGenerator.singleton_;
  }
  
  /// The contained random generator.
  private Random random_;
  
  /// Declare a singleton version of the data generator.
  private static RandomBooleanDataGenerator singleton_ = new RandomBooleanDataGenerator ();
}