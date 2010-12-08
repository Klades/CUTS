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

package cuts.datamodel.generators;
import cuts.datamodel.DataGenerator;
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
    this.seed_ = System.nanoTime ();
    this.random_ = new Random (this.seed_);
  }
  
  /**
   * Initializing constructor
   * 
   * @param[in]         seed        Value to seed generator.
   */
  public RandomLongIntegerDataGenerator (long seed)
  {
    this.seed_ = seed;
    this.random_ = new Random (this.seed_);
  }
  
  /**
   * Get the next boolean value in the random sequence.
   */
  public Object getNextValue ()
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
  
  public void reset ()
  {
    this.random_.setSeed (this.seed_);
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
  
  private long seed_;
  
  /// The contained random generator.
  private Random random_;
  
  /// Declare a singleton version of the data generator.
  private static RandomLongIntegerDataGenerator singleton_ = new RandomLongIntegerDataGenerator ();
}