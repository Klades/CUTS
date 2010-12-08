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
public class RandomBooleanDataGenerator 
implements DataGenerator
{
  /**
   * Default constructor. This will seed the random generator based
   * on the system time.
   */
  public RandomBooleanDataGenerator ()
  {
    this.seed_ = System.nanoTime ();
    this.random_ = new Random (this.seed_);
  }
  
  /**
   * Initializing constructor
   * 
   * @param[in]         seed        Value to seed generator.
   */
  public RandomBooleanDataGenerator (long seed)
  {
    this.seed_ = seed;
    this.random_ = new Random (this.seed_);
  }
  
  /**
   * Get the next boolean value in the random sequence.
   */
  public Object getNextValue ()
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
  
  public void reset ()
  {
    this.random_.setSeed (this.seed_);
  }
  
  /**
   * Get the singleton version of the data generator.
   * 
   * @return      The data generator
   */
  public static RandomBooleanDataGenerator getSingleton ()
  {
    return RandomBooleanDataGenerator.singleton_;
  }
  
  private long seed_;
  
  /// The contained random generator.
  private Random random_;
  
  /// Declare a singleton version of the data generator.
  private static RandomBooleanDataGenerator singleton_ = new RandomBooleanDataGenerator ();
}