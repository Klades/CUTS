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
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileNotFoundException;
import java.io.IOException;

/**
 * @interface DataModelFile
 */
public class DataModelFile
{
  public static DataModel readFile (String fileName)
  throws FileNotFoundException, IOException
  {
    String line = null;
    BufferedReader f = new BufferedReader (new FileReader (fileName));
    DataModel dm = new DataModel ();
       
    while ((line = f.readLine ()) != null)
    {
      // Split the line into tokens by whitespace.
      String [] value = line.split ("\\s", 0);
      
      if (value.length == 2)
      {
        try
        {
          // Create a new instance of the data generator.
          Class <DataGenerator> c = (Class <DataGenerator>) Class.forName (value[1]);
          DataGenerator dg = c.newInstance ();
          
          // Store the data generator in the datamodel.
          dm.put (value[0], dg);
        }
        catch (InstantiationException ex)
        {
          ex.printStackTrace ();
        }
        catch (IllegalAccessException ex)
        {
          ex.printStackTrace ();
        }
        catch (ClassNotFoundException ex)
        {
          ex.printStackTrace ();
        }
      }
      else
        System.err.println ("invalid line (" + line + ")");   
    }
    
    // Close the file and stream.
    f.close ();
    
    
    return dm;
  }
}
