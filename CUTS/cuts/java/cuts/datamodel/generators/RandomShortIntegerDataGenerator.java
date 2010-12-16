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

package cuts.datamodel.generators;
import cuts.datamodel.DataGenerator;
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
    this.seed_ = System.nanoTime ();
    this.random_ = new Random (this.seed_);
  }
  
  /**
   * Initializing constructor
   * 
   * @param[in]         seed        Value to seed generator.
   */
  public RandomShortIntegerDataGenerator (long seed)
  {
    this.seed_ = seed;
    this.random_ = new Random (this.seed_);
  }
  
  /**
   * Get the next boolean value in the random sequence.
   */
  public Object getNextValue ()
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
  public static RandomShortIntegerDataGenerator getSingleton ()
  {
    return RandomShortIntegerDataGenerator.singleton_;
  }
  
  /**
   * Reset the random number generator.
   */
  public void reset ()
  {
    this.random_.setSeed (this.seed_);
  }
  
  public boolean hasMoreData ()
  {
    return true;
  }
  
  private long seed_;

  /// The contained random generator.
  private Random random_;
  
  /// Declare a singleton version of the data generator.
  private static RandomShortIntegerDataGenerator singleton_ = new RandomShortIntegerDataGenerator ();
}