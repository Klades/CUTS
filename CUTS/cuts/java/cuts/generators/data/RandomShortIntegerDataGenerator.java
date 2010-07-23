// -*- Java -*-

//=============================================================================
/**
 * @file      RandomShortIntegerDataGenerator.java
 * 
 * $Id$
 * 
 * @author    James H. Hill
 */
//=============================================================================

package cuts.generators.data;
import java.util.Random;

/**
 * @class RandomShortIntegerDataGenerator
 * 
 * Data generator that generates random boolean values. This
 * class is simply a wrapper around the java.util.Random and
 * invokes its nextBoolean () method.
 */
public class RandomShortIntegerDataGenerator 
implements DataGenerator
{
  /**
   * Default constructor. This will seed the random generator based
   * on the system time.
   */
  public RandomShortIntegerDataGenerator ()
  {
    this.random_ = new Random (System.nanoTime ());
  }
  
  /**
   * Initializing constructor
   * 
   * @param[in]         seed        Value to seed generator.
   */
  public RandomShortIntegerDataGenerator (long seed)
  {
    this.random_ = new Random (seed);
  }
  
  /**
   * Get the next boolean value in the random sequence.
   */
  public Object getNext ()
  {
    return this.getNextShortInteger ();
  }
  
  /**
   * Get the next boolean value in the random sequence.
   */
  public short getNextShortInteger ()
  {
    return (short) this.random_.nextInt (16);
  }
  
  /**
   * Get the singleton version of the data generator.
   * 
   * @return      The data generator
   */
  static RandomShortIntegerDataGenerator getSingleton ()
  {
    return RandomShortIntegerDataGenerator.singleton_;
  }
  
  /// The contained random generator.
  private Random random_;
  
  /// Declare a singleton version of the data generator.
  private static RandomShortIntegerDataGenerator singleton_ = new RandomShortIntegerDataGenerator ();
}