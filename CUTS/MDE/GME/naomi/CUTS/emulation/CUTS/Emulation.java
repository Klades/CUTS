// -*- Java -*-

//=============================================================================
/**
 * @file        Emulation.java
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

package CUTS;

import java.util.*;
import java.util.regex.*;
import java.io.*;
import org.fireant.isislab.*;

/**
 * @class Emulation
 *
 * Run an CUTS emulation is ISISLab.
 */
public class Emulation
{
  /**
   * Default constructor.
   */
  public Emulation ()
  {
    this.exp_.put ("swapin", false);
  }

  /**
   * Run the emulation.
   *
   * @param[in]         args        Command-line arguments.
   */
  public void run (String [] args)
  {
    // Parse the command-line arguments.
    this.parseArgs (args);

    // First, - the attributes in the model.
    if (this.listAttributes_)
      this.listAttributes ();

    if (this.updateAttributes_)
    {
      // Generate a UUID for the experiment.
      this.readTestUUID ();

      if (this.testUUID_ != null)
      {
        // Create the experiment.
        //ISISLabUtil.createExperiment (this.isislab_, this.exp_);

        // Swapin the experiment.
        //if (this.swapin_)
        //  ISISLabUtil.swapinExperiment (this.isislab_, this.exp_);

        // Write the UUID to the CUTS.test.uuid attribute file.
        this.writeTestUUID ();
      }
    }

    // Lastly, generate the interface file for the model.
    this.writeIntefaceFile ();
  }

  /**
   * Generate the interface file for the model.
   */
  private void writeIntefaceFile ()
  {
    try
    {
      // Open the interface file for writing.
      String interfaceFileName = this.interfaceBaseName_ + "_interface.xml";
      System.out.println ("Generating interface file: " + interfaceFileName);

      PrintWriter out = new PrintWriter (new FileWriter (interfaceFileName));

      out.println ("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>");
      out.println ("<interface xmlns=\"http://www.atl.lmco.com/naomi/interfaces\"");
      out.println ("           xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"");
      out.println ("           xsi:schemaLocation=\"http://www.atl.lmco.com/naomi/interfaces interface.xsd\">");
      out.println ("  <name>" + this.owner_ + "</name>");
      out.println ("  <type>CUTS.emulation</type>");
      out.println ();
      out.println ("  <!-- input attributes -->");
      out.println ("  <input>CUTS.deployment</input>");
      out.println ("  <input>CUTS.emulation</input>");
      out.println ();
      out.println ("  <!-- output attributes -->");
      out.println ("  <output>CUTS.test.uuid</output>");
      out.println ("</interface>");

      out.close ();
    }
    catch (Exception e)
    {
      e.printStackTrace ();
    }
  }

  /**
   *
   */
  private void readTestUUID ()
  {
    try
    {
      String nsfile = (String) this.exp_.get ("nsfile");
      System.out.println ("Searching for test UUID in " + nsfile);

      FileReader reader = new FileReader (nsfile);
      BufferedReader buffer = new BufferedReader (reader);

      String regex = new String ("([\\p{Alnum}]{8}-[\\p{Alnum}]{4}-[\\p{Alnum}]{4}-[\\p{Alnum}]{4}-[\\p{Alnum}]{12})");
      Pattern pattern = Pattern.compile (regex);

      String line;

      while ((line = buffer.readLine ()) != null)
      {
        // Run the patter against the current line.
        Matcher matcher = pattern.matcher (line);

        if (matcher.find ())
        {
          // We found the UUID for the test.
          this.testUUID_ = UUID.fromString (matcher.group (0));
          break;
        }
      }

      // Close the reader.
      buffer.close ();
    }
    catch (Exception e)
    {
      e.printStackTrace ();
    }
  }

  /**
   * Writes the test UUID to CUTS.test.uuid NAOMI attribute file.
   */
  private void writeTestUUID ()
  {
    try
    {
      String attributeFileName = this.attributePath_ + "/CUTS.test.uuid";
      System.out.println ("Writing attribute: " + attributeFileName);

      // Open the attribute file for writing.
      PrintWriter out = new PrintWriter (new FileWriter (attributeFileName));

      out.println ("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>");
      out.println ("<attribute xmlns=\"http://www.atl.lmco.com/naomi/attributes\"");
      out.println ("           xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"");
      out.println ("           xsi:schemaLocation=\"http://www.atl.lmco.com/naomi/attributes attribute.xsd\">");
      out.println ("  <owner>" + this.owner_ + "</owner>");
      out.println ("  <value>" + this.testUUID_.toString ().toUpperCase () + "</value>");
      out.println ("  <documentation>Test UUID for the latest CUTS emulation</documentation>");
      out.println ("</attribute>");

      // Close the attribute file.
      out.close ();
    }
    catch (Exception e)
    {
      e.printStackTrace ();
    }
  }

  /**
   * List the attributes managed by this connector. This is an 'internal'
   * connector for CUTS, and therefore, it has a predefined set of attributes
   * that it manages.
   */
  private void listAttributes ()
  {
    StringBuffer buffer = new StringBuffer ();

    buffer.append ("Input Attributes:\n");
    buffer.append ("----------------------------------\n");
    buffer.append ("  * CUTS.deployment\n");
    buffer.append ("  * CUTS.emulation\n");
    buffer.append ("\n");
    buffer.append ("Output Attributes:\n");
    buffer.append ("----------------------------------\n");
    buffer.append ("  * CUTS.test.uuid\n");

    System.out.println (buffer.toString ());
  }

  /**
   * Parse the command line arguments for the program.
   *
   * @param[in]         args          Command-line arguments
   */
  private void parseArgs (String [] args)
  {
    for (int i = 0; i < args.length; ++ i)
    {
      String arg = args[i];

      if (arg.equals ("-username"))
      {
        this.isislab_.put ("user", args[++ i]);
      }
      else if (arg.equals ("-password"))
      {
        this.isislab_.put ("pass", args[++ i]);
      }
      else if (arg.equals ("-url"))
      {
        this.isislab_.put ("url", args[++ i]);
      }
      else if (arg.equals ("-project"))
      {
        this.exp_.put ("project", args[++ i]);
      }
      else if (arg.equals ("-experiment"))
      {
        this.exp_.put ("name", args[++ i]);
      }
      else if (arg.equals ("-description"))
      {
        this.exp_.put ("description", args[++ i]);
      }
      else if (arg.equals ("-nsfile"))
      {
        this.exp_.put ("nsfile", args[++ i]);
      }
      else if (arg.equals ("-swapin"))
      {
        this.exp_.put ("swapin", true);
      }
      else if (arg.equals ("-update-attributes"))
      {
        this.updateAttributes_ = true;
      }
      else if (arg.equals ("-list-attributes"))
      {
        this.listAttributes_ = true;
      }
      else if (arg.equals ("-attribute-path"))
      {
        this.attributePath_ = args [++i];
      }
      else if (arg.equals ("-interface-basename"))
      {
        this.interfaceBaseName_ = args [++i];
      }
      else if (arg.equals ("-owner"))
      {
        this.owner_ = args [++i];
      }
    }
  }

  /// Username for running the experiment.
  private HashMap exp_ = new HashMap ();

  /// Password for running the experiment.
  private HashMap isislab_ = new HashMap ();

  /// Swapin the experiment.
  private boolean swapin_ = false;

  /// List the attributes managed by this connector.
  private boolean listAttributes_ = false;

  private boolean updateAttributes_ = false;

  private String attributePath_;

  private String interfaceBaseName_;

  private String owner_;

  private UUID testUUID_ = null;

  /////////////////////////////////////////////////////////////////////////////
  // entry point

  public static void main (String [] args)
  {
    try
    {
      // Create a new emulation object.
      Emulation exp = new Emulation ();

      // Run the emulation.
      exp.run (args);
    }
    catch (Exception e)
    {
      e.printStackTrace ();
    }
  }
}
