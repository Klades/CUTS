// -*- Java -*-

//=============================================================================
/**
 * @file      RandomLongIntegerDataGenerator.java
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
public class RandomLongIntegerDataGenerator 
implements DataGenerator
{
  /**
   * Default constructor. This will seed the random generator based
   * on the system time.
   */
  public RandomLongIntegerDataGenerator ()
  {
    this.random_ = new Random (System.nanoTime ());
  }
  
  /**
   * Initializing constructor
   * 
   * @param[in]         seed        Value to seed generator.
   */
  public RandomLongIntegerDataGenerator (long seed)
  {
    this.random_ = new Random (seed);
  }
  
  /**
   * Get the next boolean value in the random sequence.
   */
  public Object getNext ()
  {
    return this.getNextLongInteger ();
  }
  
  /**
   * Get the next boolean value in the random sequence.
   */
  public long getNextLongInteger ()
  {
    return (long) this.random_.nextInt (32);
  }
  
  /**
   * Get the singleton version of the data generator.
   * 
   * @return      The data generator
   */
  public static RandomLongIntegerDataGenerator getSingleton ()
  {
    return RandomLongIntegerDataGenerator.singleton_;
  }
  
  /// The contained random generator.
  private Random random_;
  
  /// Declare a singleton version of the data generator.
  private static RandomLongIntegerDataGenerator singleton_ = new RandomLongIntegerDataGenerator ();
}